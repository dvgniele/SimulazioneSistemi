#include "Dispatcher.h"
#include "DispatcherMessage.h"


Define_Module(Dispatcher);

void Dispatcher::initialize()
{
    std::cout<<std::endl<< "\t############\t[ "<< this->getClassName() <<" ]\t############\t" <<std::endl;

    sid_label = "server_id";

    int n_server = par("n_servers");
    std::vector<int> server_list;

    std::cout << "n_server: " << n_server << std::endl;

    for(int i = 0; i < n_server; i++)
        server_list.push_back(i);

    std::cout << "server_list size: " << server_list.size()<< std::endl;


}

void Dispatcher::handleMessage(cMessage *msg)
{
    //auto dmsg = new DispatcherMessage(1);
    auto mpar = new cMsgPar();


    mpar->setDoubleValue(777);
    mpar->setName(sid_label);


    //msg->addObject(dmsg);
    msg->addPar(mpar);


    send(msg,"out");
}
