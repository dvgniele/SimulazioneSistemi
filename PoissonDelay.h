#ifndef __SIMSYS_POISSONDELAY_H_
#define __SIMSYS_POISSONDELAY_H_

#include <omnetpp.h>
#include "Job.h"

#include "QueueingDefs.h"

using namespace omnetpp;

class PoissonDelay : public cSimpleModule
{
private:
    /** @brief lambda parameter for the Poisson process  */
    double lambda;

    simsignal_t busySignal;
    
    int currentlyStored;

    /**
     * @brief Calculates a delay through a Poisson process with lambda parameter
     *
     * @return double Delay for the incoming job
     */
    double poissonTime();

protected:
    /**
     * @brief Initialized the PoissonDelay module
     *
     */
    virtual void initialize();

    /**
     * @brief Adds a delay through a Poisson process with lambda parameter and sends it
     *
     * @param job
     */
    virtual void handleMessage(cMessage *job);
};
#endif
