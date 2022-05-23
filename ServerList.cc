#include "ServerList.h"
#include "cstring"

using std::to_string;
using namespace std;

Define_Module(ServerList);

list<queueing::Server> *server_list;

void ServerList::initialize()
{
    std::cout<<std::endl<< "\t############\t[ "<< this->getClassName() <<" ]\t############\t" <<std::endl;

    // TODO - INIZIALIZZARE LISTA CON SERVER
    // TODO - modificare msgpar per contenere status IsIdle del server che effettua il job

    int n_server = par("n_servers");
    server_list = new std::vector<queueing::Server>(n_server);

    cout << "n_server: " << n_server << endl;
    cout << "server_list size: " << server_list->size() << endl;

    //  creazione connessioni tra ServerList ed i Server
    for (int i = 0; i < server_list->size(); i++)
    {
        string out_port_name = "sv_out" + to_string(i);
        string in_port_name = "sv_in" + to_string(i);

        addGate(out_port_name.c_str(), cGate::OUTPUT)->connectTo(server_list->at(i).addGate("in",cGate::INPUT));
        server_list->at(i).addGate("out",cGate::OUTPUT)->connectTo(addGate(in_port_name.c_str(), cGate::INPUT));
    }
}

void ServerList::handleMessage(cMessage *msg)
{
    //  TODO - i server utilizzano i gates server_in e server_out

    cGate *arrivalGate = msg->getArrivalGate();

    //  #####   MESSAGGIO IN ARRIVO DALL'ESTERNO
    if(arrivalGate == gate("ext_in")){

    }
    //  #####   MESSAGGIO IN ARRIVO DA UN SERVER
    else
    {

    }


    auto name = "server_id";

    auto mpar = msg->par(name);
    auto number = mpar.doubleValue();

    auto blblbl = Number_to_Char(number);

    cMessage *nmsg = new cMessage(blblbl);


    send(nmsg, "out");
}





const char* ServerList::Number_to_Char(int num)
{
    std::string tmp = std::to_string(num);
    char const *num_char = tmp.c_str();

    return num_char;
}

const char* ServerList::Number_to_Char(float num)
{
    std::string tmp = std::to_string(num);
    char const *num_char = tmp.c_str();

    return num_char;
}

const char* ServerList::Number_to_Char(double num)
{
    std::string tmp = std::to_string(num);
    char const *num_char = tmp.c_str();

    return num_char;
}
