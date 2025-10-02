#include "DNSServer.h"

Define_Module(DNSServer);

void DNSServer::initialize() {
    serverId = par("serverId");
    initializeDNSTable();
    EV << "DNS Server " << serverId << " initialized" << endl;
}

void DNSServer::initializeDNSTable() {
    // Initialize some hostname-to-IP mappings
    dnsTable["pc1.local"] = 1;
    dnsTable["pc2.local"] = 2;
    dnsTable["pc3.local"] = 3;
    dnsTable["router1.local"] = 10;
    dnsTable["router2.local"] = 11;
    dnsTable["router3.local"] = 12;
    dnsTable["dhcp.local"] = 100;
    dnsTable["dns.local"] = 101;
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
        EV << "DNS Server received packet: " << pkt->getData() << endl;
    }

    delete msg;
}

void DNSServer::handleDNSQuery(DNSQuery *query) {
    std::string hostname = query->getHostname();
    int sourceAddr = query->getSourceAddr();

    auto it = dnsTable.find(hostname);

    if (it != dnsTable.end()) {
        EV << "DNS Server resolving " << hostname
           << " to " << it->second << endl;

        DNSResponse *resp = new DNSResponse("DNSResponse");
        resp->setHostname(hostname.c_str());
        resp->setIpAddr(it->second);

        // In real implementation, would route back to source
        delete resp;
    } else {
        EV << "DNS Server: hostname " << hostname << " not found" << endl;
    }
}
