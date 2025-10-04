#ifndef LEARNINGROUTER_H
#define LEARNINGROUTER_H

#include <omnetpp.h>
#include <map>
#include <set>
#include "Packet_m_m.h"

using namespace omnetpp;

class LearningRouter : public cSimpleModule {
private:
    std::map<int, int> routingTable;  // destination -> gate index
    int routerId;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void forwardPacket(BasicPacket *pkt);
    void floodPacket(BasicPacket *pkt, int arrivalGate);
    void learnRoute(int destAddr, int gateIndex);
    void sendRouteInfo(int destAddr, int gateToDestination, int backGate);  // ← Added backGate parameter
    void handleRouteInfo(RouteInfoPacket *routeInfo);
    void printRoutingTable();
    bool isDirectlyConnected(int addr, int &gateIndex);  // ← Added gateIndex reference parameter
};

#endif
