#ifndef __SIMSYS_SERVERLIST_H_
#define __SIMSYS_SERVERLIST_H_

#include <omnetpp.h>
#include "Server.h"
#include <vector>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class ServerList : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    const char* Number_to_Char(int num);
    const char* Number_to_Char(double num);
    const char* Number_to_Char(float num);
    std::vector<queueing::Server> *server_list;

    void CheckPolicy(cMsgPar);

};

#endif
