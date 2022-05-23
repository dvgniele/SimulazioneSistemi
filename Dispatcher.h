#ifndef __SIMSYS_DISPATCHER_H_
#define __SIMSYS_DISPATCHER_H_

#include <omnetpp.h>
#include <vector>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Dispatcher : public cSimpleModule
{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    const char *sid_label;
    std::vector<int> server_list;

};

#endif
