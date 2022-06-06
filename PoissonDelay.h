#ifndef __SIMSYS_POISSONDELAY_H_
#define __SIMSYS_POISSONDELAY_H_

#include <omnetpp.h>

using namespace omnetpp;

class PoissonDelay : public cSimpleModule
{   
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

};
#endif