#include "Dispatcher.h"

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
    hasMemory = par("hasMemory");

    // int *jobs_per_server = new int[n_server];
    memset(jobs_per_server, 0, n_server * sizeof(*jobs_per_server)); // imposta la dimensione della lista di jobs possibili per ogni server

    for (int i = 0; i < k_limit; i++)
        idle_servers.push_back(i);

#pragma region log_variabili
    cout << "n_server: " << n_server << endl;
    cout << "k_limit: " << k_limit << endl;
    cout << "server_list size: " << server_list.size() << endl;
#pragma endregion log_variabili
}

void Dispatcher::handleMessage(cMessage *msg)
{
    cGate *arrivalGate = msg->getArrivalGate();

    if (arrivalGate == gate("source_in"))
    {
        //  selezione del derver in base alla politica selezionata
        int sid;
        if (hasMemory)
            sid = MemSQ_policy();
        else
            sid = SQ_policy();

        sendJob(msg, sid);
    }
    else
    {
        auto sid_par_name = "server_id";
        auto sid_par = msg->par(sid_par_name);
        auto sid = (int)sid_par.doubleValue();

        serverUpdate(msg, sid);

        send(msg, "sink_out");
    }
}

// invia il job alla lista di server, e rimuove il server dalla lista di idle
void Dispatcher::sendJob(cMessage *msg, int sid)
{
    removeFromIdleList(sid);
    jobs_per_server[sid]++;

    //  impostazione dei parametri del messaggio    //
    //  set del parametro: server_id
    msg->par("server_id").setDoubleValue(sid);
    // msg->addPar(mpar);

    //  set del parametro: is_idle
    msg->par("is_idle").setBoolValue(false);

    //  set del parametro: n_jobs
    msg->par("n_jobs").setDoubleValue(jobs_per_server[sid]);

    //  il job viene inviato
    send(msg, "out");
}

//  vengono letti i parametri del messaggi, e viene decrementato il numero di job del server mittente
void Dispatcher::serverUpdate(cMessage *msg, int sid)
{
    jobs_per_server[sid]--;

    auto idle_par_name = "is_idle";
    auto idle_par = msg->par(idle_par_name);
    auto isIdle = (int)idle_par.doubleValue();

    if (isIdle && idle_servers.size() < k_limit)
        idle_servers.push_back(sid);
}

void Dispatcher::removeFromIdleList(int value)
{
    vector<int> tmp;

    for (auto it : idle_servers)
        if (it != value)
            tmp.push_back(it);

    idle_servers.clear();

    for (auto it : tmp)
        idle_servers.push_back(it);
}

int Dispatcher::SQ_policy()
{
    return 1;
}

int Dispatcher::MemSQ_policy()
{
    return 1;
}

Dispatcher::~Dispatcher()
{
    jobs_per_server = new int;
    delete[] jobs_per_server;
    jobs_per_server = NULL;
}
