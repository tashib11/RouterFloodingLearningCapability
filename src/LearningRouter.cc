#include "LearningRouter.h"

Define_Module(LearningRouter);

void LearningRouter::initialize() {
    routerId = par("routerId");
    EV << "========================================" << endl;
    EV << "Learning Router " << routerId << " initialized" << endl;
    EV << "========================================" << endl;

    // Schedule periodic routing table display
    scheduleAt(simTime() + 5.0, new cMessage("printTable"));
}

void LearningRouter::handleMessage(cMessage *msg) {
    // Handle self messages (periodic table printing)
    if (msg->isSelfMessage()) {
        if (strcmp(msg->getName(), "printTable") == 0) {
            printRoutingTable();
            scheduleAt(simTime() + 5.0, msg);
        }
        return;
    }

    // Handle route information packets (ACK from other routers)
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

    int arrivalGate = pkt->getArrivalGate()->getIndex();
    int sourceAddr = pkt->getSourceAddr();
    int destAddr = pkt->getDestAddr();

    // STEP 1: Learn the SOURCE route (where packet came from)
    if (routingTable.find(sourceAddr) == routingTable.end()) {
        learnRoute(sourceAddr, arrivalGate);
        EV << "✓ Router " << routerId << " learned: Destination " << sourceAddr
           << " → Gate " << arrivalGate << " [Source learning]" << endl;
    }

    // STEP 2: Check if destination is DIRECTLY connected to THIS router
    int destGate = -1;
    if (isDirectlyConnected(destAddr, destGate)) {
        // Destination is directly connected!
        if (routingTable.find(destAddr) == routingTable.end()) {
            learnRoute(destAddr, destGate);
            EV << "✓✓ Router " << routerId << " FOUND destination " << destAddr
               << " → Gate " << destGate << " [DIRECTLY CONNECTED!]" << endl;

            // Send ACK back to inform other routers
            sendRouteInfo(destAddr, destGate, arrivalGate);
        }

        // Forward packet to destination
        EV << "→ Router " << routerId << " delivering to destination " << destAddr
           << " via Gate " << destGate << endl;
        send(pkt, "gate$o", destGate);
        return;
    }

    // STEP 3: Forward the packet (flood if unknown, or use learned route)
    forwardPacket(pkt);
}

bool LearningRouter::isDirectlyConnected(int addr, int &gateIndex) {
    // Check all gates to see if the device is directly connected
    int numGates = gateSize("gate");
    for (int i = 0; i < numGates; i++) {
        if (!gate("gate$i", i)->isConnected()) continue;

        cGate *connectedGate = gate("gate$o", i)->getNextGate();
        if (!connectedGate) continue;

        cModule *connectedModule = connectedGate->getOwnerModule();
        if (!connectedModule) continue;

        // Check if connected module has matching address
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

    // Check if we know the route to destination
    auto it = routingTable.find(destAddr);
    if (it != routingTable.end()) {
        // We know the route - forward directly
        EV << "→ Router " << routerId << " forwarding packet (Src:" << sourceAddr
           << " → Dest:" << destAddr << ") via Gate " << it->second
           << " [USING LEARNED ROUTE]" << endl;

        send(pkt, "gate$o", it->second);
    } else {
        // Unknown destination - flood the packet
        EV << "⚡ Router " << routerId << " FLOODING packet (Src:" << sourceAddr
           << " → Dest:" << destAddr << ") [DESTINATION UNKNOWN]" << endl;

        pkt->setIsFlooded(true);
        int arrivalGate = pkt->getArrivalGate()->getIndex();
        floodPacket(pkt, arrivalGate);
    }
}

void LearningRouter::floodPacket(BasicPacket *pkt, int arrivalGate) {
    pkt->setHopCount(pkt->getHopCount() + 1);

    // Prevent infinite loops
    if (pkt->getHopCount() > 10) {
        EV << "⚠ Packet hop count exceeded, dropping" << endl;
        delete pkt;
        return;
    }

    // Send copy to all gates except the arrival gate
    int numGates = gateSize("gate");
    int sentCount = 0;

    for (int i = 0; i < numGates; i++) {
        if (i != arrivalGate && gate("gate$o", i)->isConnected()) {
            BasicPacket *copy = pkt->dup();
            send(copy, "gate$o", i);
            sentCount++;
            EV << "  ⤷ Flooding copy via Gate " << i << endl;
        }
    }

    delete pkt; // Delete original after sending copies
}

void LearningRouter::learnRoute(int destAddr, int gateIndex) {
    routingTable[destAddr] = gateIndex;
}

void LearningRouter::sendRouteInfo(int destAddr, int gateToDestination, int backGate) {
    // Send ACK back through the path the packet came from
    EV << "📢 Router " << routerId << " sending ACK back: Found Destination "
       << destAddr << " on my Gate " << gateToDestination << endl;

    RouteInfoPacket *info = new RouteInfoPacket("routeACK");
    info->setDestAddr(destAddr);
    info->setReporterAddr(routerId);
    info->setGateToDestination(gateToDestination);

    // Send ACK back through the gate packet came from
    send(info, "gate$o", backGate);
}

void LearningRouter::handleRouteInfo(RouteInfoPacket *routeInfo) {
    int destAddr = routeInfo->getDestAddr();
    int reporterAddr = routeInfo->getReporterAddr();
    int arrivalGate = routeInfo->getArrivalGate()->getIndex();

    // Learn: To reach destAddr, go through the gate this ACK came from
    if (routingTable.find(destAddr) == routingTable.end()) {
        learnRoute(destAddr, arrivalGate);
        EV << "📚 Router " << routerId << " learned from ACK: Destination "
           << destAddr << " → Gate " << arrivalGate
           << " (via Router " << reporterAddr << ")" << endl;
    }
}

void LearningRouter::printRoutingTable() {
    EV << endl;
    EV << "╔════════════════════════════════════════╗" << endl;
    EV << "║  ROUTING TABLE - Router " << routerId << "            ║" << endl;
    EV << "╠════════════════════════════════════════╣" << endl;

    if (routingTable.empty()) {
        EV << "║  (Empty - No routes learned yet)       ║" << endl;
    } else {
        for (const auto& entry : routingTable) {
            EV << "║  Destination " << entry.first << " → Gate " << entry.second;
            // Add padding for alignment
            int spaces = 18 - (int)std::to_string(entry.first).length() -
                        (int)std::to_string(entry.second).length();
            for (int i = 0; i < spaces; i++) EV << " ";
            EV << "║" << endl;
        }
    }

    EV << "╚════════════════════════════════════════╝" << endl;
    EV << endl;
}
