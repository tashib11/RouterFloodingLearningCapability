#include "DNSServer.h"

Define_Module(DNSServer);

void DNSServer::initialize() {
    serverId = par("serverId");
    initializeDNSTable();
<<<<<<< HEAD
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
=======
    EV << "DNS Server " << serverId << " initialized" << endl;
}

void DNSServer::initializeDNSTable() {
    // Initialize some hostname-to-IP mappings
>>>>>>> origin/main
    dnsTable["pc1.local"] = 1;
    dnsTable["pc2.local"] = 2;
    dnsTable["pc3.local"] = 3;
    dnsTable["router1.local"] = 10;
    dnsTable["router2.local"] = 11;
    dnsTable["router3.local"] = 12;
<<<<<<< HEAD
    dnsTable["router4.local"] = 13;
    dnsTable["dhcp.local"] = 100;
    dnsTable["dns.local"] = 101;
    dnsTable["youtube.com"] = 200;
    dnsTable["youtube"] = 200;
    dnsTable["www.youtube.com"] = 200;
=======
    dnsTable["dhcp.local"] = 100;
    dnsTable["dns.local"] = 101;
>>>>>>> origin/main
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
<<<<<<< HEAD
        EV << "🌐 DNS Server received packet: " << pkt->getData() << endl;
=======
        EV << "DNS Server received packet: " << pkt->getData() << endl;
>>>>>>> origin/main
    }

    delete msg;
}

void DNSServer::handleDNSQuery(DNSQuery *query) {
    std::string hostname = query->getHostname();
    int sourceAddr = query->getSourceAddr();
<<<<<<< HEAD
    int queryId = query->getQueryId();

    EV << "========================================" << endl;
    EV << "🔍 DNS Query Received" << endl;
    EV << "  From: Device " << sourceAddr << endl;
    EV << "  Looking up: " << hostname << endl;
=======
>>>>>>> origin/main

    auto it = dnsTable.find(hostname);

    if (it != dnsTable.end()) {
<<<<<<< HEAD
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
=======
        EV << "DNS Server resolving " << hostname
           << " to " << it->second << endl;

        DNSResponse *resp = new DNSResponse("DNSResponse");
        resp->setHostname(hostname.c_str());
        resp->setIpAddr(it->second);

        // In real implementation, would route back to source
        delete resp;
    } else {
        EV << "DNS Server: hostname " << hostname << " not found" << endl;
>>>>>>> origin/main
    }
}
