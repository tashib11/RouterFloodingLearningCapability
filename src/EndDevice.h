#ifndef ENDDEVICE_H
#define ENDDEVICE_H

#include <omnetpp.h>
<<<<<<< HEAD
#include <map>
=======
>>>>>>> origin/main
#include "Packet_m_m.h"

using namespace omnetpp;

class EndDevice : public cSimpleModule {
private:
    int deviceId;
<<<<<<< HEAD
    int dnsServerAddr;
    std::map<int, std::string> pendingDNSQueries;  // queryId -> hostname
    std::map<std::string, int> dnsCache;  // hostname -> resolved IP
    int nextQueryId;
=======
>>>>>>> origin/main

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void sendTestPacket();
<<<<<<< HEAD
    void sendDNSQuery(const char* hostname);
    void handleDNSResponse(DNSResponse *resp);
    void sendDataToServer(int serverAddr, const char* hostname);
=======
>>>>>>> origin/main
};

#endif
