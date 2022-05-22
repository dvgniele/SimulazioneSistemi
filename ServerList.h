#ifndef __SIMSYS_SERVERLIST_H_
#define __SIMSYS_SERVERLIST_H_

#include <omnetpp.h>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class ServerList : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  public:
    char* Number_to_Char(int num);
    const char* Number_to_Char(double num);
    char* Number_to_Char(float num);

};

#endif
