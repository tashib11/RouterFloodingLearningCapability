#include "DNSServer.h"

Define_Module(DNSServer);

void DNSServer::initialize() {
    serverId = par("serverId");
    initializeDNSTable();
    EV << "========================================" << endl;
    EV << " DNS Server " << serverId << " initialized" << endl;
    EV << "DNS Records loaded:" << endl;
    for (const auto& entry : dnsTable) {
        EV << "  " << entry.first << " → " << entry.second << endl;
    }
    EV << "========================================" << endl;
}

void DNSServer::initializeDNSTable() {
    dnsTable["pc1.local"] = 1;
    dnsTable["pc2.local"] = 2;
    dnsTable["pc3.local"] = 3;
    dnsTable["router1.local"] = 10;
    dnsTable["router2.local"] = 11;
    dnsTable["router3.local"] = 12;
    dnsTable["router4.local"] = 13;
    dnsTable["dhcp.local"] = 100;
    dnsTable["dns.local"] = 101;
    dnsTable["youtube.com"] = 200;
    dnsTable["youtube"] = 200;
    dnsTable["www.youtube.com"] = 200;
}

void DNSServer::handleMessage(cMessage *msg) {
    // Check if it's a BasicPacket containing DNSQuery
    BasicPacket *pkt = dynamic_cast<BasicPacket *>(msg);
    if (pkt) {
        cPacket *encapsulated = pkt->getEncapsulatedPacket();
        if (encapsulated) {
            DNSQuery *query = dynamic_cast<DNSQuery *>(encapsulated);
            if (query) {
                handleDNSQuery(query);
                delete msg;
                return;
            }
        }
    }

    DNSQuery *query = dynamic_cast<DNSQuery *>(msg);
    if (query) {
        handleDNSQuery(query);
        delete query;
        return;
    }

    if (pkt && pkt->getDestAddr() == serverId) {
        EV << " DNS Server received packet: " << pkt->getData() << endl;
    }

    delete msg;
}

void DNSServer::handleDNSQuery(DNSQuery *query) {
    std::string hostname = query->getHostname();
    int sourceAddr = query->getSourceAddr();  // This is the ROUTER that asked
    int queryId = query->getQueryId();
    int originalPacketId = query->getOriginalPacketId();

    EV << "========================================" << endl;
    EV << " DNS Query Received" << endl;
    EV << "  From: Main source Router " << sourceAddr << endl;
    EV << "  Looking for: " << hostname << endl;
    EV << "  Query ID: " << queryId << endl;

    auto it = dnsTable.find(hostname);

    if (it != dnsTable.end()) {
        int resolvedAddr = it->second;
        EV << " DNS Resolution SUCCESS" << endl;
        EV << "  " << hostname << " → " << resolvedAddr << endl;
        EV << "========================================" << endl;

        // Create DNS Response
        DNSResponse *resp = new DNSResponse("dnsResponse");
        resp->setHostname(hostname.c_str());
        resp->setResolvedAddr(resolvedAddr);
        resp->setDestAddr(sourceAddr);  // Send back to the router that asked
        resp->setQueryId(queryId);
        resp->setOriginalPacketId(originalPacketId);




        send(resp, "gate$o");

        EV << " DNS Response sent to Router " << sourceAddr << endl;
    } else {
        EV << " DNS Resolution FAILED" << endl;
        EV << "  Hostname '" << hostname << "' not found" << endl;
        EV << "========================================" << endl;
    }
}
