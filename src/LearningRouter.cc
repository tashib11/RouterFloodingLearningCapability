#include "LearningRouter.h"
#include <sstream>

Define_Module(LearningRouter);//connects the C++ class LearningRouter with the .ned definition

void LearningRouter::initialize() {
    routerId = par("routerId");
    dnsServerAddr = 101;
    nextQueryId = 1;
    seenPackets.clear();

    EV << "========================================" << endl;
    EV << "Learning Router " << routerId << " initialized" << endl;
    EV << "========================================" << endl;

    scheduleAt(simTime() + 5.0, new cMessage("printTable"));
}

void LearningRouter::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        if (strcmp(msg->getName(), "printTable") == 0) {
            printRoutingTable();
            scheduleAt(simTime() + 5.0, msg);
        }
        return;
    }

    // Handle DNS Response
    DNSResponse *dnsResp = dynamic_cast<DNSResponse *>(msg);
    if (dnsResp) {
        int destRouter = dnsResp->getDestAddr();

        if (destRouter == routerId) {
            handleDNSResponse(dnsResp);
            delete dnsResp;
        } else {
            EV << "Router " << routerId << " forwarding DNS response to Router "
               << destRouter << endl;

            auto it = routingTable.find(destRouter);
            if (it != routingTable.end()) {
                send(dnsResp, "gate$o", it->second);
            } else {
                EV << " Router " << routerId << " doesn't know route to Router "
                   << destRouter << ", dropping DNS response" << endl;
                delete dnsResp;
            }
        }
        return;
    }

    // Handle route information packets
    RouteInfoPacket *routeInfo = dynamic_cast<RouteInfoPacket *>(msg);
    if (routeInfo) {
        handleRouteInfo(routeInfo);
        delete routeInfo;
        return;
    }

    // Handle data packets
    BasicPacket *pkt = dynamic_cast<BasicPacket *>(msg);
    if (!pkt) {
        delete msg;
        return;
    }

    // **UPDATED: Check if we've already seen this packet using unique key**
    std::string packetKey = getPacketKey(pkt);
    if (hasSeenPacket(packetKey)) {
        EV << " Router " << routerId << " already processed packet [" << packetKey
           << "] - DROPPING duplicate to prevent loop" << endl;
        delete pkt;
        return;
    }

    //  Mark this packet as seen using unique key
    markPacketAsSeen(packetKey);
    EV << " Router " << routerId << " processing packet [" << packetKey << "]" << endl;

    int arrivalGate = pkt->getArrivalGate()->getIndex();
    int sourceAddr = pkt->getSourceAddr();
    int destAddr = pkt->getDestAddr();

    // Learn source route
    if (routingTable.find(sourceAddr) == routingTable.end()) {
        learnRoute(sourceAddr, arrivalGate);
        EV << " Router " << routerId << " learned: Destination " << sourceAddr
           << " → Gate " << arrivalGate << " [Source learning]" << endl;
    }

    // Check if packet needs DNS resolution
    if (pkt->getNeedsDNSResolution() && strlen(pkt->getDestHostname()) > 0) {
        EV << " Router " << routerId << " detected hostname: "
           << pkt->getDestHostname() << " - Querying DNS..." << endl;
        queryDNS(pkt);
        return;
    }

    // Check if destination is directly connected
    int destGate = -1;
    if (isDirectlyConnected(destAddr, destGate)) {
        if (routingTable.find(destAddr) == routingTable.end()) {
            learnRoute(destAddr, destGate);
            EV << " Router " << routerId << " FOUND destination " << destAddr
               << " → Gate " << destGate << " [DIRECTLY CONNECTED!]" << endl;
            sendRouteInfo(destAddr, destGate, arrivalGate);
        }

        EV << "→ Router " << routerId << " delivering to destination " << destAddr
           << " via Gate " << destGate << endl;
        send(pkt, "gate$o", destGate);
        return;
    }

    forwardPacket(pkt);
}

// NEW FUNCTION: Generate unique key for a packet
std::string LearningRouter::getPacketKey(BasicPacket *pkt) {
    // Create unique key: "source-dest-name-treeid"
    // TreeId is OMNeT++'s internal identifier
    std::ostringstream key;
    key << pkt->getSourceAddr() << "-"
        << pkt->getDestAddr() << "-"
        << pkt->getName() << "-"
        << pkt->getTreeId();
    return key.str();//as a packet key
}

//  Check if packet has been seen
bool LearningRouter::hasSeenPacket(std::string packetKey) {
    return seenPackets.find(packetKey) != seenPackets.end();//set<string>seenPackets
}

// **UPDATED FUNCTION: Mark packet as seen**
void LearningRouter::markPacketAsSeen(std::string packetKey) {
    seenPackets.insert(packetKey);

    // Optional: Limit memory usage
    if (seenPackets.size() > 1000) {
        seenPackets.clear();
    }
}

bool LearningRouter::isDirectlyConnected(int addr, int &gateIndex) {
    int numGates = gateSize("gate");
    for (int i = 0; i < numGates; i++) {
        if (!gate("gate$i", i)->isConnected()) continue;

        cGate *connectedGate = gate("gate$o", i)->getNextGate();
        if (!connectedGate) continue;

        cModule *connectedModule = connectedGate->getOwnerModule();
        if (!connectedModule) continue;

        if (connectedModule->hasPar("deviceId")) {
            int deviceId = connectedModule->par("deviceId");
            if (deviceId == addr) {
                gateIndex = i;
                return true;
            }
        }
        if (connectedModule->hasPar("serverId")) {
            int serverId = connectedModule->par("serverId");
            if (serverId == addr) {
                gateIndex = i;
                return true;
            }
        }
    }
    gateIndex = -1;
    return false;
}

void LearningRouter::forwardPacket(BasicPacket *pkt) {
    int destAddr = pkt->getDestAddr();
    int sourceAddr = pkt->getSourceAddr();

    auto it = routingTable.find(destAddr);
    if (it != routingTable.end()) {
        EV << "→ Router " << routerId << " forwarding packet (Src:" << sourceAddr
           << " → Dest:" << destAddr << ") via Gate " << it->second
           << " Using Routing table" << endl;

        send(pkt, "gate$o", it->second);
    } else {
        EV << " Router " << routerId << " FLOODING packet (Src:" << sourceAddr
           << " → Dest:" << destAddr << ") [DESTINATION UNKNOWN]" << endl;

        pkt->setIsFlooded(true);
        int arrivalGate = pkt->getArrivalGate()->getIndex();
        floodPacket(pkt, arrivalGate);
    }
}

void LearningRouter::floodPacket(BasicPacket *pkt, int arrivalGate) {
    pkt->setHopCount(pkt->getHopCount() + 1);

    if (pkt->getHopCount() > 10) {
        EV << " Packet hop count exceeded, dropping" << endl;
        delete pkt;
        return;
    }

    int numGates = gateSize("gate");
    int floodedCount = 0;

    for (int i = 0; i < numGates; i++) {
        if (i != arrivalGate && gate("gate$o", i)->isConnected()) {
            BasicPacket *copy = pkt->dup();//a copy of the packet for each gate,Because OMNeT++ messages can’t be reused once sent.
            send(copy, "gate$o", i);
            floodedCount++;
            EV << "  Flooding copy via Gate " << i << endl;
        }
    }

    EV << " Total flooded: " << floodedCount << " gate(s) (excluded arrival gate "
       << arrivalGate << ")" << endl;

    delete pkt;
}

void LearningRouter::learnRoute(int destAddr, int gateIndex) {
    routingTable[destAddr] = gateIndex;
}

//ACK
void LearningRouter::sendRouteInfo(int destAddr, int gateToDestination, int backGate) {
    EV << " Router " << routerId << " sending ACK back: Found Destination "
       << destAddr << " on my Gate " << gateToDestination << endl;

    RouteInfoPacket *info = new RouteInfoPacket("routeACK");
    info->setDestAddr(destAddr);
    info->setReporterAddr(routerId);
    info->setGateToDestination(gateToDestination);

    send(info, "gate$o", backGate);

    // Broadcast to other gates
    int numGates = gateSize("gate");
    for (int i = 0; i < numGates; i++) {
        if (i == gateToDestination || i == backGate) continue;
        if (!gate("gate$o", i)->isConnected()) continue;

        RouteInfoPacket *broadcastInfo = new RouteInfoPacket("routeACK_broadcast");
        broadcastInfo->setDestAddr(destAddr);
        broadcastInfo->setReporterAddr(routerId);
        broadcastInfo->setGateToDestination(gateToDestination);

        send(broadcastInfo, "gate$o", i);
        EV << "  Broadcasting to Gate " << i << endl;
    }
}

void LearningRouter::handleRouteInfo(RouteInfoPacket *routeInfo) {
    int destAddr = routeInfo->getDestAddr();
    int reporterAddr = routeInfo->getReporterAddr();
    int arrivalGate = routeInfo->getArrivalGate()->getIndex();

    if (routingTable.find(destAddr) == routingTable.end()) {
        learnRoute(destAddr, arrivalGate);
        EV << "Router " << routerId << " learned from ACK: Destination "
           << destAddr << " → Gate " << arrivalGate
           << " (via Router " << reporterAddr << ")" << endl;

        // Forward ACK to other routers
        int numGates = gateSize("gate");
        for (int i = 0; i < numGates; i++) {
            if (i == arrivalGate) continue;
            if (!gate("gate$o", i)->isConnected()) continue;

            RouteInfoPacket *forwardInfo = new RouteInfoPacket("routeACK_forward");
            forwardInfo->setDestAddr(destAddr);
            forwardInfo->setReporterAddr(routerId);
            forwardInfo->setGateToDestination(arrivalGate);

            send(forwardInfo, "gate$o", i);
            EV << "   Forwarding ACK to Gate " << i << endl;
        }
    }
}

void LearningRouter::queryDNS(BasicPacket *pkt) {
    int queryId = nextQueryId++;
    int packetId = pkt->getId();

    // Store the original packet
    pendingPackets[packetId] = pkt->dup();

    EV << "========================================" << endl;
    EV << " Router " << routerId << " querying DNS for hostname: "
       << pkt->getDestHostname() << endl;
    EV << "  Storing original packet (ID: " << packetId << ") for later forwarding" << endl;
    EV << "========================================" << endl;

    // Create DNS query
    DNSQuery *query = new DNSQuery("dnsQuery");
    query->setHostname(pkt->getDestHostname());
    query->setSourceAddr(routerId);
    query->setQueryId(queryId);
    query->setOriginalPacketId(packetId);

    // Check if we know route to DNS server
    auto it = routingTable.find(dnsServerAddr);
    if (it != routingTable.end()) {
        EV << "Router " << routerId << " sending DNS query to DNS Server "
           << dnsServerAddr << " via Gate " << it->second << endl;
        send(query, "gate$o", it->second);
    } else {
        EV << " Router " << routerId << " flooding DNS query to find DNS Server" << endl;

        // Wrap in BasicPacket for flooding
        BasicPacket *dnsQueryPkt = new BasicPacket("dnsQueryPacket");
        dnsQueryPkt->setSourceAddr(routerId);
        dnsQueryPkt->setDestAddr(dnsServerAddr);
        dnsQueryPkt->setData("DNS_QUERY");
        dnsQueryPkt->encapsulate(query);

        int arrivalGate = pkt->getArrivalGate()->getIndex();
        floodPacket(dnsQueryPkt, arrivalGate);
    }

    delete pkt;
}

void LearningRouter::handleDNSResponse(DNSResponse *resp) {
    int resolvedAddr = resp->getResolvedAddr();
    std::string hostname = resp->getHostname();
    int packetId = resp->getOriginalPacketId();


    int arrivalGate = resp->getArrivalGate()->getIndex();
    if (routingTable.find(101) == routingTable.end()) {
        learnRoute(101, arrivalGate);
        EV << " Router " << routerId << " learned DNS Server route: Destination 101 → Gate "
           << arrivalGate << endl;
    }

    EV << "========================================" << endl;
    EV << "Router " << routerId << " received DNS response" << endl;
    EV << "  Hostname: " << hostname << " → IP: " << resolvedAddr << endl;
    EV << "  Original packet ID: " << packetId << endl;
    EV << "========================================" << endl;

    // Find the original packet
    auto it = pendingPackets.find(packetId);
    if (it != pendingPackets.end()) {
        BasicPacket *originalPkt = it->second;

        // Update packet with resolved IP address
        originalPkt->setDestAddr(resolvedAddr);
        originalPkt->setNeedsDNSResolution(false);
        originalPkt->setDestHostname("");

        EV << "Router " << routerId << " NOW forwarding packet to YouTube (IP: "
           << resolvedAddr << ")" << endl;

        // Remove from pending
        pendingPackets.erase(it);

        auto routeIt = routingTable.find(resolvedAddr);
        if (routeIt == routingTable.end()) {
            EV << " Router " << routerId << " doesn't know route to " << resolvedAddr
               << " - FLOODING to find YouTube server!" << endl;
        }

        // forwarding with the resolved IP
        forwardPacket(originalPkt);
    } else {
        EV << " Router " << routerId << " couldn't find original packet ID: "
           << packetId << endl;
    }
}

void LearningRouter::printRoutingTable() {
    EV << endl;
    EV << "==========================================" << endl;
    EV << "|| ROUTING TABLE - Router " << routerId << "            ||" << endl;
    EV << "==========================================" << endl;

    if (routingTable.empty()) {
        EV << "||  (Empty - No routes learned yet)       ||" << endl;
    } else {
        for (const auto& entry : routingTable) {
            EV << "|  Destination " << entry.first << " → Gate " << entry.second;
            int spaces = 18 - (int)std::to_string(entry.first).length() -
                        (int)std::to_string(entry.second).length();
            for (int i = 0; i < spaces; i++) EV << " ";
            EV << "|" << endl;
        }
    }


}
