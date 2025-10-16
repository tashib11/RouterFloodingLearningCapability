#include "EndDevice.h"

Define_Module(EndDevice);

void EndDevice::initialize() {
    deviceId = par("deviceId");
<<<<<<< HEAD
    dnsServerAddr = 101;  // DNS server address
    nextQueryId = 1;

=======
>>>>>>> origin/main
    EV << "🖥️  End Device " << deviceId << " initialized" << endl;

    // Schedule test packet sending
    if (deviceId == 1) { // Only device 1 sends test packets
        scheduleAt(simTime() + uniform(1.0, 2.0), new cMessage("sendPacket"));
<<<<<<< HEAD
        // Schedule DNS query for youtube.com
        scheduleAt(simTime() + 5.0, new cMessage("queryYoutube"));
=======
>>>>>>> origin/main
    }
}

void EndDevice::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        if (strcmp(msg->getName(), "sendPacket") == 0) {
            sendTestPacket();
            // Schedule next packet
<<<<<<< HEAD
            scheduleAt(simTime() + uniform(10.0, 15.0), msg);
            return;
        }

        if (strcmp(msg->getName(), "queryYoutube") == 0) {
            EV << endl;
            EV << "========================================" << endl;
            EV << "🔍 Device " << deviceId << " wants to access YouTube!" << endl;
            EV << "========================================" << endl;
            sendDNSQuery("youtube.com");
            delete msg;
            return;
        }

        delete msg;
=======
            scheduleAt(simTime() + uniform(8.0, 12.0), msg);
        }
>>>>>>> origin/main
        return;
    }

    BasicPacket *pkt = dynamic_cast<BasicPacket *>(msg);
    if (pkt) {
<<<<<<< HEAD
        // Check if this is a DNS response
        if (pkt->getEncapsulatedPacket()) {
            DNSResponse *dnsResp = dynamic_cast<DNSResponse *>(pkt->getEncapsulatedPacket());
            if (dnsResp) {
                handleDNSResponse(dnsResp);
                delete msg;
                return;
            }
        }

        // Regular data packet
        if (strcmp(pkt->getData(), "VIDEO_STREAM_DATA") == 0) {
            EV << "========================================" << endl;
            EV << "🎬 Device " << deviceId << " received YouTube video!" << endl;
            EV << "  Streaming content from server " << pkt->getSourceAddr() << endl;
            EV << "========================================" << endl;
        } else {
            EV << "✉️  Device " << deviceId << " RECEIVED packet from Device "
               << pkt->getSourceAddr() << ": " << pkt->getData() << endl;
        }
=======
        EV << "✉️  Device " << deviceId << " RECEIVED packet from Device "
           << pkt->getSourceAddr() << ": " << pkt->getData() << endl;
>>>>>>> origin/main
    }

    delete msg;
}

void EndDevice::sendTestPacket() {
    // Send packet to different destinations
    static int targetDest = 2;

    BasicPacket *pkt = new BasicPacket("dataPacket");
    pkt->setSourceAddr(deviceId);
    pkt->setDestAddr(targetDest);
    pkt->setData("Hello from PC");

    EV << endl;
    EV << "📤 Device " << deviceId << " SENDING packet to Device "
       << targetDest << endl;

    send(pkt, "gate$o");

    // Cycle through destinations (2 and 3)
    targetDest = (targetDest == 2) ? 3 : 2;
}
<<<<<<< HEAD

void EndDevice::sendDNSQuery(const char* hostname) {
    // Check cache first
    auto it = dnsCache.find(hostname);
    if (it != dnsCache.end()) {
        EV << "✅ Device " << deviceId << " found " << hostname
           << " in cache: " << it->second << endl;
        sendDataToServer(it->second, hostname);
        return;
    }

    // Send DNS query
    int queryId = nextQueryId++;
    pendingDNSQueries[queryId] = hostname;

    EV << "📤 Device " << deviceId << " sending DNS query for '"
       << hostname << "' (Query ID: " << queryId << ")" << endl;

    DNSQuery *query = new DNSQuery("dnsQuery");
    query->setHostname(hostname);
    query->setSourceAddr(deviceId);
    query->setQueryId(queryId);

    // Wrap in BasicPacket for routing
    BasicPacket *pkt = new BasicPacket("dnsQueryPacket");
    pkt->setSourceAddr(deviceId);
    pkt->setDestAddr(dnsServerAddr);
    pkt->setData("DNS_QUERY");
    pkt->encapsulate(query);

    send(pkt, "gate$o");
}

void EndDevice::handleDNSResponse(DNSResponse *resp) {
    std::string hostname = resp->getHostname();
    int resolvedAddr = resp->getResolvedAddr();
    int queryId = resp->getQueryId();

    EV << "========================================" << endl;
    EV << "✅ Device " << deviceId << " received DNS response" << endl;
    EV << "  Query ID: " << queryId << endl;
    EV << "  Hostname: " << hostname << endl;
    EV << "  Resolved to: " << resolvedAddr << endl;
    EV << "========================================" << endl;

    // Cache the result
    dnsCache[hostname] = resolvedAddr;

    // Remove from pending queries
    pendingDNSQueries.erase(queryId);

    // Now send actual data to the resolved server
    sendDataToServer(resolvedAddr, hostname.c_str());
}

void EndDevice::sendDataToServer(int serverAddr, const char* hostname) {
    EV << "========================================" << endl;
    EV << "📤 Device " << deviceId << " connecting to " << hostname << endl;
    EV << "  Server address: " << serverAddr << endl;
    EV << "========================================" << endl;

    BasicPacket *pkt = new BasicPacket("webRequest");
    pkt->setSourceAddr(deviceId);
    pkt->setDestAddr(serverAddr);
    pkt->setData("GET_VIDEO_REQUEST");

    send(pkt, "gate$o");
}
=======
>>>>>>> origin/main
