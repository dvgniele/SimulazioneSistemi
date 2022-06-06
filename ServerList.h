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

    /**
     * @brief Destroy the Dispatcher:: Dispatcher object
     *
     */
    ~ServerList();

private:
    /**
     * @brief Converting integer to char
     * 
     * @param num integer value to convert
     * @return const char* 
     */
    const char *NumberToChar(int num);
    /**
     * @brief Converting double to char
     * 
     * @param num double value to convert
     * @return const char* 
     */
    const char *NumberToChar(double num);
    /**
     * @brief Converting float to char
     * 
     * @param num float value to convert
     * @return const char* 
     */
    const char *NumberToChar(float num);
    // std::vector<queueing::Queue> *server_list;
};

#endif
