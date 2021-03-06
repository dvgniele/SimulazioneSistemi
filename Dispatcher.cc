#include "Dispatcher.h"

using std::find;
using namespace std;

Define_Module(Dispatcher);

int *jobs_per_server = new int[0];
vector<int> idle_servers;
int n_server = 0;
int k_limit = 0;
int d_limit = 0;
double serviceTime = 0;

void Dispatcher::initialize()
{
    cout << endl
         << "\t############\t[ " << this->getClassName() << " ]\t############\t" << endl;

    currentlyStored = 0;
    busySignal = registerSignal("busy");
    idle_list_length_Signal = registerSignal("idle_length");
    emit(busySignal, false);
    emit(idle_list_length_Signal, 0);
    WATCH(currentlyStored);

    sid_label = "server_id";

    cModule *parent = getParentModule();

    n_server = parent->par("n_servers");
    k_limit = par("k_limit");
    d_limit = par("d_limit");
    hasMemory = par("hasMemory");
    serviceTime = par("serviceTime");

    // int *jobs_per_server = new int[n_server];
    memset(jobs_per_server, 0, n_server * sizeof(*jobs_per_server)); // sets the array size to the server count

    for (int i = 0; i < k_limit; i++)
        idle_servers.push_back(i);

#pragma region log_variabili
    cout << "n_server: " << n_server << endl;
    cout << "k_limit: " << k_limit << endl;
    cout << "d_limit: " << d_limit << endl;
    cout << "hasMemory: " << hasMemory << endl;
    // cout << "server_list size: " << server_list.size() << endl;
#pragma endregion log_variabili
}

void Dispatcher::handleMessage(cMessage *msg)
{
    if (hasMemory)
        emit(idle_list_length_Signal, (int)idle_servers.size());

    cGate *arrivalGate = msg->getArrivalGate();

    if (arrivalGate == gate("ext_in"))
    {
        auto sid_par_name = "server_id";
        auto sid_par = msg->par(sid_par_name);
        auto sid = (int)sid_par.doubleValue();

        serverUpdate(msg, sid);

        send(msg, "sink_out");
    }
    else
    {
        queueing::Job *job = check_and_cast<queueing::Job *>(msg);

        if (!job->isSelfMessage())
        {
            currentlyStored++;

            emit(busySignal, true);

            scheduleAt(simTime() + serviceTime, job);
        }
        else
        {
            job->setDelayCount(job->getDelayCount() + 1);
            simtime_t d = simTime() - job->getSendingTime();
            job->setTotalDelayTime(job->getTotalDelayTime() + d);

            currentlyStored--;

            emit(busySignal, false);

            int sid;
            sid = hasMemory ? MemSQ_policy() : SQ_policy();

            sendJob(job, sid);
        }
    }

    if (hasMemory)
        emit(idle_list_length_Signal, (int)idle_servers.size());
}

void Dispatcher::sendJob(queueing::Job *job, int sid)
{
    removeFromIdleList(sid); //  removing the server id from the idle list
    jobs_per_server[sid]++;  //  increasing the number of jobs of server sid

    /*  message parameters setting  */
    // setting parameter: server_id
    job->par("server_id").setDoubleValue(sid);

    //  setting parameter: is_idle
    job->par("is_idle").setBoolValue(false);

    //  setting parameter: n_jobs
    job->par("n_jobs").setDoubleValue(jobs_per_server[sid]);

    //  sending the job
    send(job, "out");
}

void Dispatcher::serverUpdate(cMessage *job, int sid)
{
    jobs_per_server[sid]--;

    auto idle_par_name = "is_idle";
    auto idle_par = job->par(idle_par_name);
    auto isIdle = (int)idle_par.doubleValue();

    if (isIdle && idle_servers.size() < k_limit)
        idle_servers.push_back(sid);
}

void Dispatcher::removeFromIdleList(int value)
{
    vector<int> tmp;

    //  populate cache vector
    for (auto it : idle_servers)
        if (it != value)
            tmp.push_back(it);

    idle_servers.clear(); //  clear idle vector

    //  populate idle vector
    for (auto it : tmp)
        idle_servers.push_back(it);
}

int Dispatcher::SQ_policy()
{
    vector<int> tmp;
    tmp.clear();

    for (int i = 0; i < n_server; i++)
        tmp.push_back(i);

    int cache[d_limit];

    for (int i = 0; i < d_limit; i++)
    {
        int rnd = rand() % tmp.size();
        cache[i] = tmp.at(rnd);
        tmp.erase(tmp.begin() + rnd);
    }

    int min = jobs_per_server[cache[0]];
    int min_index = cache[0];

    for (int i = 0; i < d_limit; i++)
    {
        int check = jobs_per_server[cache[i]];

        if (check < min)
        {
            min = check;
            min_index = cache[i];
        }
    }

    return min_index;
}

int Dispatcher::MemSQ_policy()
{
    if (!idle_servers.size())
        return SQ_policy();

    return idle_servers[rand() % idle_servers.size()];
}

Dispatcher::~Dispatcher()
{
    //jobs_per_server = new int;
    delete[] jobs_per_server;
    jobs_per_server = NULL;
}
