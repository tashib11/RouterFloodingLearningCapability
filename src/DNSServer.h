#ifndef DNSSERVER_H
#define DNSSERVER_H

#include <omnetpp.h>
#include <map>
#include <string>
#include "Packet_m_m.h"

using namespace omnetpp;

class DNSServer : public cSimpleModule {
private:
    int serverId;
    std::map<std::string, int> dnsTable;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void handleDNSQuery(DNSQuery *query);
    void initializeDNSTable();
};

#endif
