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
    int lambda;

    simsignal_t delayedJobsSignal;
    int currentlyStored;

    /**
     * @brief Calculates a delay through a Poisson process with lambda parameter
     *
     * @return int Delay for the incoming job
     */
    int poissonTime();

protected:
    /**
     * @brief Initialized the PoissonDelay module
     * 
     */
    virtual void initialize();

    /**
     * @brief Sets the parameters for each message received coming from the source port
     *  Adds a delay through a Poisson process with lambda parameter and sends it
     * 
     * @param job 
     */
    virtual void handleMessage(cMessage *job);
};
#endif
