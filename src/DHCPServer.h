#ifndef DHCPSERVER_H
#define DHCPSERVER_H

#include <omnetpp.h>
#include <map>
#include "Packet_m_m.h"

using namespace omnetpp;

class DHCPServer : public cSimpleModule {
private:
    int serverId;
    std::map<std::string, int> assignedAddresses;
    int nextAddress;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void handleDHCPRequest(DHCPRequest *req);
};

#endif
