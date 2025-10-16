#ifndef LEARNINGROUTER_H
#define LEARNINGROUTER_H

#include <omnetpp.h>
#include <map>
#include <set>
#include "Packet_m_m.h"

using namespace omnetpp;

class LearningRouter : public cSimpleModule {
private:
    std::map<int, int> routingTable;
    std::map<int, BasicPacket*> pendingPackets;  // NEW: Store packets waiting for DNS
    int routerId;
    int dnsServerAddr;  // NEW
    int nextQueryId;    // NEW

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void forwardPacket(BasicPacket *pkt);
    void floodPacket(BasicPacket *pkt, int arrivalGate);
    void learnRoute(int destAddr, int gateIndex);
    void sendRouteInfo(int destAddr, int gateToDestination, int backGate);
    void handleRouteInfo(RouteInfoPacket *routeInfo);
    void printRoutingTable();
    bool isDirectlyConnected(int addr, int &gateIndex);
    void queryDNS(BasicPacket *pkt);           // NEW
    void handleDNSResponse(DNSResponse *resp); // NEW
};

#endif
