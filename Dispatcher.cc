#include "Dispatcher.h"
#include "DispatcherMessage.h"


Define_Module(Dispatcher);

void Dispatcher::initialize()
{

}

void Dispatcher::handleMessage(cMessage *msg)
{
    //auto dmsg = new DispatcherMessage(1);

    auto sid = "server_id";

    auto mpar = new cMsgPar();
    mpar->setDoubleValue(777);
    mpar->setName(sid);


    //msg->addObject(dmsg);
    msg->addPar(mpar);


    send(msg,"out");
}
