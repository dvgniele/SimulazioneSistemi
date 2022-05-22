#ifndef DISPATCHERMESSAGE_H_
#define DISPATCHERMESSAGE_H_

#include <omnetpp/cobject.h>

class DispatcherMessage{
public:
    int serverId { 0 };

    DispatcherMessage();
    DispatcherMessage(int sid);
    virtual ~DispatcherMessage();
};

#endif /* DISPATCHERMESSAGE_H_ */
