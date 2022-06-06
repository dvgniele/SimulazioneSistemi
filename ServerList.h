#ifndef __SIMSYS_SERVERLIST_H_
#define __SIMSYS_SERVERLIST_H_

#include <omnetpp.h>
#include "Queue.h"
#include <vector>

using namespace omnetpp;

class ServerList : public cSimpleModule
{

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    ~ServerList();

private:
    const char *NumberToChar(int num);
    const char *NumberToChar(double num);
    const char *NumberToChar(float num);
    // std::vector<queueing::Queue> *server_list;
};

#endif
