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

    
    cModule* parent = getParentModule();
    if(!parent) error("Parent Module not found.");

    int n_server = parent->par("n_servers");
    //server_list = new std::vector<cModule*>(n_server);

    auto serverListModuleType = cModuleType::get(parent->par("moduleType").stdstringValue().c_str());
    auto serverListModuleName = parent->par("moduleName").stdstringValue();

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
        cModule* module = serverListModuleType->create(sv_name.c_str(), parent);

        double stime = parent->par("sTime").doubleValue();
        cout << stime << endl;
        module->par("serviceTime") = stime;
        module->finalizeParameters();
        module->buildInside();
        module->scheduleStart(simTime());

        server_list[i] = module;
     }

    cout << "n_server: " << n_server << endl;

    //  creating connections with ServerList foreach server
    for (int i = 0; i < n_server; i++)
    {
        gate(sv_outGate.c_str(),i)->connectTo(server_list[i]->addGate("in", cGate::INPUT));
        server_list[i]->addGate("out", cGate::OUTPUT)->connectTo(gate(sv_inGate.c_str(),i));
    }
}

void ServerList::handleMessage(cMessage *msg)
{
    cGate *arrivalGate = msg->getArrivalGate();

    //  #####   MESSAGE INCOMING FROM EXTERNAL PORT
    if (arrivalGate == gate("ext_in"))
    {
        auto name = "server_id";
        auto mpar = msg->par(name);
        auto id = (int)mpar.doubleValue();

        send(msg, sv_outGate.c_str(), id);
    }
    else    //  #####   MESSAGE INCOMING FROM A SERVER
    {
        send(msg, "out");
    }
}

#pragma region NumberToChar

const char *ServerList::NumberToChar(int num)
{
    std::string tmp = std::to_string(num);
    char const *num_char = tmp.c_str();

    return num_char;
}

const char *ServerList::NumberToChar(float num)
{
    std::string tmp = std::to_string(num);
    char const *num_char = tmp.c_str();

    return num_char;
}

const char *ServerList::NumberToChar(double num)
{
    std::string tmp = std::to_string(num);
    char const *num_char = tmp.c_str();

    return num_char;
}

#pragma endregion

ServerList::~ServerList()
{

}
