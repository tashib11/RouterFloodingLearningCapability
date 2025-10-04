#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <omnetpp.h>
#include "Packet_m_m.h"

using namespace omnetpp;

class WebServer : public cSimpleModule {
private:
    int serverId;
    std::string hostname;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif
