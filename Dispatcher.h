#ifndef __SIMSYS_DISPATCHER_H_
#define __SIMSYS_DISPATCHER_H_

#include <omnetpp.h>
#include <vector>
#include <string.h>
#include "Job.h"

#include "QueueingDefs.h"

using namespace omnetpp;

class Dispatcher : public cSimpleModule
{
public:
    /**
     * @brief Destroy the Dispatcher:: Dispatcher object
     *
     */
    virtual ~Dispatcher();

protected:
    /**
     * @brief Initializes the Dispatcher
     *
     */
    virtual void initialize();

    /**
     * @brief Handles the incoming message
     *
     * @param msg incoming message
     */
    virtual void handleMessage(cMessage *msg);

private:
    /** @brief server_id label */
    const char *sid_label;
    /** @brief Limit k for the idle servers list size*/
    int k_limit;
    /** @brief Number of available servers */
    int n_server;
    /** @brief Limit d for the randomly choosen servers list size*/
    int d_limit;
    /** @brief True if using MemSQ_policy, false instead */
    bool hasMemory;
    /** @brief Server list */
    std::vector<int> server_list;

    simsignal_t delayedJobsSignal;
    int currentlyStored;

    /**
     * @brief sends the job to the server list and removes it from the idle list
     *
     * @param msg message to send
     * @param sid server id which is going to use the job
     */
    void sendJob(queueing::Job *job, int sid);

    /**
     * @brief The message parameters are read and the server jobs count is decreased
     *
     * @param msg incoming message
     * @param sid server id
     */
    void serverUpdate(cMessage *job, int sid);

    /**
     * @brief Removes the id of the server from the idle servers list
     *
     * @param value the id of the server no longer in idle state
     */
    void removeFromIdleList(int value);

    /**
     * @brief Randomly chooses d servers between the n available servers.
     *  Returns the id of the server with the shortest queue
     *
     * @return int the server id
     */
    int SQ_policy();

    /**
     * @brief Randomly chooses a server from the idle server list.
     *  If the list is empty, the server id is selected with the SQ_policy
     *
     * @return int the server id
     */
    int MemSQ_policy();
};

#endif
