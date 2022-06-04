#include "ServerList.h"
#include "cstring"

using std::to_string;
using namespace std;

Define_Module(ServerList);

//list<queueing::Queue> *server_list;

string sv_inGate = "sv_in";
string sv_outGate = "sv_out";

cModule* server_list[0];

void ServerList::initialize()
{
    std::cout << std::endl
              << "\t############\t[ " << this->getClassName() << " ]\t############\t" << std::endl;

    // TODO - INIZIALIZZARE LISTA CON SERVER
    // TODO - modificare msgpar per contenere status IsIdle del server che effettua il job

    //int n_server = par("n_servers");

    int n_server = getParentModule()->par("n_servers");
    //server_list = new std::vector<cModule*>(n_server);
    
    cModule* parent = getParentModule();
    if(!parent) error("Parent Module not found.");

    //auto queuina = new queueing::Queue[n_server];
    
    auto listellaModuleType = cModuleType::get(parent->par("moduleType").stdstringValue().c_str());
    auto listellaModuleName = parent->par("moduleName").stdstringValue();

    cModule* server_list[n_server];
    memset(server_list, 0, n_server * sizeof(*server_list));


    addGate(sv_inGate.c_str(), cGate::INPUT, true);
    setGateSize(sv_inGate.c_str(), n_server);
    addGate(sv_outGate.c_str(), cGate::OUTPUT, true);
    setGateSize(sv_outGate.c_str(), n_server);

    int cnt = 0;
    for(int i = 0; i < n_server; i++)
    {

        string sv_name = "server_" + to_string(i);
        cModule* module = listellaModuleType->create(sv_name.c_str(), parent);

        double stime = parent->par("sTime").doubleValue();
        cout << stime << endl;
        module->par("serviceTime") = stime;
        module->finalizeParameters();
        module->buildInside();
        module->scheduleStart(simTime());

        //module->callInitialize();

        server_list[i] = module;
     }


    cout << "n_server: " << n_server << endl;

    //  creazione connessioni tra ServerList ed i Server
    for (int i = 0; i < n_server; i++)
    {
        //server_list->at(i).setCapacity(5);
        //cout << "capacity: " << to_string(server_list->at(i).getCapacity()) << endl;
        gate(sv_outGate.c_str(),i)->connectTo(server_list[i]->addGate("in", cGate::INPUT));
        server_list[i]->addGate("out", cGate::OUTPUT)->connectTo(gate(sv_inGate.c_str(),i));
    }
}

void ServerList::handleMessage(cMessage *msg)
{
    //  TODO - i server utilizzano i gates server_in e server_out

    cGate *arrivalGate = msg->getArrivalGate();


    //  #####   MESSAGGIO IN ARRIVO DALL'ESTERNO
    if (arrivalGate == gate("ext_in"))
    {

        auto name = "server_id";
        auto mpar = msg->par(name);
        auto id = (int)mpar.doubleValue();


        send(msg, sv_outGate.c_str(), id);
    }
    else
    {
        //int sid = arrivalGate->getIndex();

        //auto name = "server_id";
        //auto mpar = msg->par(name);
        //auto id = (int)mpar.doubleValue();


        send(msg, "out");
    }


    /*
    auto name = "server_id";

    auto mpar = msg->par(name);
    auto number = mpar.doubleValue();

    auto blblbl = Number_to_Char(number);

    cMessage *nmsg = new cMessage(blblbl);

    send(nmsg, "out");
    */
}

const char *ServerList::Number_to_Char(int num)
{
    std::string tmp = std::to_string(num);
    char const *num_char = tmp.c_str();

    return num_char;
}

const char *ServerList::Number_to_Char(float num)
{
    std::string tmp = std::to_string(num);
    char const *num_char = tmp.c_str();

    return num_char;
}

const char *ServerList::Number_to_Char(double num)
{
    std::string tmp = std::to_string(num);
    char const *num_char = tmp.c_str();

    return num_char;
}


ServerList::~ServerList()
{

}
