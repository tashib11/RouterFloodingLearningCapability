#ifndef ENDDEVICE_H
#define ENDDEVICE_H

#include <omnetpp.h>
#include <map>
#include "Packet_m_m.h"

using namespace omnetpp;

class EndDevice : public cSimpleModule {
private:
    int deviceId;
    int dnsServerAddr;
    std::map<int, std::string> pendingDNSQueries;  // queryId -> hostname
    std::map<std::string, int> dnsCache;  // hostname -> resolved IP
    int nextQueryId;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void sendTestPacket();
    void sendDNSQuery(const char* hostname);
    void handleDNSResponse(DNSResponse *resp);
    void sendDataToServer(int serverAddr, const char* hostname);
};

#endif
