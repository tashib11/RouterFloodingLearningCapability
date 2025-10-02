#include "DHCPServer.h"

Define_Module(DHCPServer);

void DHCPServer::initialize() {
    serverId = par("serverId");
    nextAddress = 1; // Start assigning from address 1
    EV << "DHCP Server " << serverId << " initialized" << endl;
}

void DHCPServer::handleMessage(cMessage *msg) {
    DHCPRequest *req = dynamic_cast<DHCPRequest *>(msg);
    if (req) {
        handleDHCPRequest(req);
        delete req;
        return;
    }

    BasicPacket *pkt = dynamic_cast<BasicPacket *>(msg);
    if (pkt && pkt->getDestAddr() == serverId) {
        EV << "DHCP Server received packet: " << pkt->getData() << endl;
    }

    delete msg;
}

void DHCPServer::handleDHCPRequest(DHCPRequest *req) {
    std::string clientMAC = req->getClientMAC();

    // Check if address already assigned
    auto it = assignedAddresses.find(clientMAC);
    int assignedAddr;

    if (it != assignedAddresses.end()) {
        assignedAddr = it->second;
    } else {
        assignedAddr = nextAddress++;
        assignedAddresses[clientMAC] = assignedAddr;
    }

    EV << "DHCP Server assigning address " << assignedAddr
       << " to client " << clientMAC << endl;

    // Send response (in real implementation, would route back to client)
    DHCPResponse *resp = new DHCPResponse("DHCPResponse");
    resp->setClientMAC(clientMAC.c_str());
    resp->setAssignedAddr(assignedAddr);

    // For simulation, just log the assignment
    delete resp;
}
