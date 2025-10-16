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
    std::map<int, BasicPacket*> pendingPackets;
    std::set<long> seenPackets;  // NEW: Track packet IDs we've already processed
    int routerId;
    int dnsServerAddr;
    int nextQueryId;

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
    void queryDNS(BasicPacket *pkt);
    void handleDNSResponse(DNSResponse *resp);
    bool hasSeenPacket(long packetId);  // NEW
    void markPacketAsSeen(long packetId);  // NEW
};

#endif
