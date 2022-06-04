#include "Dispatcher.h"
#include "DispatcherMessage.h"

using namespace std;

Define_Module(Dispatcher);

int *jobs_per_server = new int[0];
vector<int> idle_servers;

void Dispatcher::initialize()
{
    cout << endl
         << "\t############\t[ " << this->getClassName() << " ]\t############\t" << endl;

    sid_label = "server_id";

    const int n_server = par("n_servers");
    const int k_limit = par("k_limit");

    // int *jobs_per_server = new int[n_server];
    memset(jobs_per_server, 0, n_server * sizeof(*jobs_per_server)); // imposta la dimensione della lista di jobs possibili per ogni server
    jobs_per_server[3] = 2;

    for (int i = 0; i < n_server; i++)
    {
        idle_servers.push_back(i);
        // cout<< "jobs: "<< jobs_per_server[i] << endl;
    }

#pragma region log_variabili
    cout << "n_server: " << n_server << endl;
    cout << "k_limit: " << k_limit << endl;
    cout << "server_list size: " << server_list.size() << endl;
#pragma endregion log_variabili
}

void Dispatcher::handleMessage(cMessage *msg)
{

    cGate *arrivalGate = msg->getArrivalGate();
    cout << "in arrivo da: " << arrivalGate->getName() << endl;

    int sid = 2;

    // auto dmsg = new DispatcherMessage(1);

    //  se il messaggio non ha il parametro riguardante il server di servizio, lo si aggiunge
    auto mpar = new cMsgPar();
    if (!msg->hasPar(sid_label))
    {
        mpar->setDoubleValue(sid);
        mpar->setName(sid_label);
        msg->addPar(mpar);
    }

    //  se il messaggio non ha il parametro is_idle, viene creato ed impostato
    //  a false dato che il server verr� considerato impegnato da tale job
    mpar = new cMsgPar();
    if (!msg->hasPar("is_idle"))
    {
        mpar->setBoolValue(false);
        mpar->setName("is_idle");
        msg->addPar(mpar);
    }

    //  se il messaggio non ha il parametro is_idle, viene creato ed impostato ad 1
    mpar = new cMsgPar();
    if (!msg->hasPar("n_jobs"))
    {
        mpar->setDoubleValue(1);
        mpar->setName("n_jobs");
        msg->addPar(mpar);
    }

    auto id = (int)mpar->doubleValue();
    sendJob(msg, id);
}

// invia il job alla lista di server, e rimuove il server dalla lista di idle
void Dispatcher::sendJob(cMessage *msg, int sid)
{
    jobs_per_server[sid]++;

    //  viene creato un nuovo vettore contenente tutti i server in idle
    //  escluso il server a cui si sta per inviare il job
    vector<int> tmp;
    for (auto id : idle_servers)
        if (id != sid)
            tmp.push_back(id);

    //  si sovrascrive la lista di server in idle, corretta
    idle_servers.clear();
    for (auto item : tmp)
        idle_servers.push_back(item);

    //  il job viene inviato
    send(msg, "out");
}

//  vengono letti i parametri del messaggi, e viene decrementato il numero di job del server mittente
void Dispatcher::serverUpdate(cMessage *msg)
{
    auto sid_par_name = "server_id";
    auto idle_par_name = "server_idle";
    auto sid_par = msg->par(sid_par_name);
    auto idle_par = msg->par(idle_par_name);
    auto sid = (int)sid_par.doubleValue();
    auto isIdle = (int)idle_par.doubleValue();

    jobs_per_server[sid]--;
}

void Dispatcher::SQ_policy()
{
}

void Dispatcher::MemSQ_policy()
{
}

Dispatcher::~Dispatcher()
{
    jobs_per_server = new int;
    delete[] jobs_per_server;
    jobs_per_server = NULL;
}
