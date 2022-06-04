#ifndef __SIMSYS_DISPATCHER_H_
#define __SIMSYS_DISPATCHER_H_

#include <omnetpp.h>
#include <vector>
#include <string.h>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Dispatcher : public cSimpleModule
{
public:
    virtual ~Dispatcher();

protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

private:
    const char *sid_label;
    int k_limit;
    int n_server;
    std::vector<int> server_list;
    void sendJob(cMessage *msg, int sid);
    void serverUpdate(cMessage *msg);

    void SQ_policy();
    void MemSQ_policy();
};

#endif
