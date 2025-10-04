#include "DNSServer.h"

Define_Module(DNSServer);

void DNSServer::initialize() {
    serverId = par("serverId");
    initializeDNSTable();
    EV << "========================================" << endl;
    EV << "🌐 DNS Server " << serverId << " initialized" << endl;
    EV << "DNS Records loaded:" << endl;
    for (const auto& entry : dnsTable) {
        EV << "  " << entry.first << " → " << entry.second << endl;
    }
    EV << "========================================" << endl;
}

void DNSServer::initializeDNSTable() {
    // Initialize hostname-to-IP mappings
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
    DNSQuery *query = dynamic_cast<DNSQuery *>(msg);
    if (query) {
        handleDNSQuery(query);
        delete query;
        return;
    }

    BasicPacket *pkt = dynamic_cast<BasicPacket *>(msg);
    if (pkt && pkt->getDestAddr() == serverId) {
        EV << "🌐 DNS Server received packet: " << pkt->getData() << endl;
    }

    delete msg;
}

void DNSServer::handleDNSQuery(DNSQuery *query) {
    std::string hostname = query->getHostname();
    int sourceAddr = query->getSourceAddr();
    int queryId = query->getQueryId();

    EV << "========================================" << endl;
    EV << "🔍 DNS Query Received" << endl;
    EV << "  From: Device " << sourceAddr << endl;
    EV << "  Looking up: " << hostname << endl;

    auto it = dnsTable.find(hostname);

    if (it != dnsTable.end()) {
        int resolvedAddr = it->second;
        EV << "✅ DNS Resolution SUCCESS" << endl;
        EV << "  " << hostname << " → " << resolvedAddr << endl;
        EV << "========================================" << endl;

        // Send DNS Response back to source
        DNSResponse *resp = new DNSResponse("dnsResponse");
        resp->setHostname(hostname.c_str());
        resp->setResolvedAddr(resolvedAddr);
        resp->setDestAddr(sourceAddr);
        resp->setQueryId(queryId);

        // Create a BasicPacket wrapper to send through network
        BasicPacket *pkt = new BasicPacket("dnsResponsePacket");
        pkt->setSourceAddr(serverId);
        pkt->setDestAddr(sourceAddr);
        pkt->setData("DNS_RESPONSE");

        // Encapsulate DNS response
        pkt->encapsulate(resp);

        send(pkt, "gate$o");

        EV << "📤 DNS Response sent to Device " << sourceAddr << endl;
    } else {
        EV << "❌ DNS Resolution FAILED" << endl;
        EV << "  Hostname '" << hostname << "' not found" << endl;
        EV << "========================================" << endl;
    }
}
