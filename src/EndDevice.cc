#include "EndDevice.h"

Define_Module(EndDevice);

void EndDevice::initialize() {
    deviceId = par("deviceId");

    EV << " PC" << deviceId << " initialized" << endl;

    if (deviceId == 1) {
        scheduleAt(simTime() + uniform(1.0, 2.0), new cMessage("sendPacket"));
        scheduleAt(simTime() + 5.0, new cMessage("accessYoutube"));
    }
}

void EndDevice::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        if (strcmp(msg->getName(), "sendPacket") == 0) {
            sendTestPacket();
            scheduleAt(simTime() + uniform(10.0, 15.0), msg);
            return;
        }

        if (strcmp(msg->getName(), "accessYoutube") == 0) {
            EV << endl;
            EV << "========================================" << endl;
            EV << " PC " << deviceId << " wants to access YouTube" << endl;
            EV << "  Sending packet to 'youtube.com'" << endl;
            EV << "========================================" << endl;

            // Send packet with HOSTNAME - Router will handle DNS
            BasicPacket *pkt = new BasicPacket("youtubeRequest");
            pkt->setSourceAddr(deviceId);
            pkt->setDestAddr(0);  // Unknown - needs DNS
            pkt->setDestHostname("youtube.com");
            pkt->setNeedsDNSResolution(true);
            pkt->setData("GET_VIDEO_REQUEST");

            send(pkt, "gate$o");
            delete msg;
            return;
        }

        delete msg;
        return;
    }

    BasicPacket *pkt = dynamic_cast<BasicPacket *>(msg);
    if (pkt) {
        if (strcmp(pkt->getData(), "VIDEO_DATA") == 0) {
            EV << "========================================" << endl;
            EV << " PC " << deviceId << " received YouTube video" << endl;
            EV << "  from Youtube server " << pkt->getSourceAddr() << endl;
            EV << "========================================" << endl;
        } else {
            EV << "  PC " << deviceId << " RECEIVED packet from Device "
               << pkt->getSourceAddr() << ": " << pkt->getData() << endl;
        }
    }

    delete msg;
}

void EndDevice::sendTestPacket() {
    static int targetDest = 2;

    BasicPacket *pkt = new BasicPacket("dataPacket");
    pkt->setSourceAddr(deviceId);
    pkt->setDestAddr(targetDest);
    pkt->setData("Hello from PC 1");

    EV << endl;
    EV << "PC " << deviceId << " SENDING packet to PC "
       << targetDest << endl;

    send(pkt, "gate$o");

    targetDest = (targetDest == 2) ? 3 : 2;
}
