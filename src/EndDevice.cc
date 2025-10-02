#include "EndDevice.h"

Define_Module(EndDevice);

void EndDevice::initialize() {
    deviceId = par("deviceId");
    EV << "🖥️  End Device " << deviceId << " initialized" << endl;

    // Schedule test packet sending
    if (deviceId == 1) { // Only device 1 sends test packets
        scheduleAt(simTime() + uniform(1.0, 2.0), new cMessage("sendPacket"));
    }
}

void EndDevice::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        if (strcmp(msg->getName(), "sendPacket") == 0) {
            sendTestPacket();
            // Schedule next packet
            scheduleAt(simTime() + uniform(8.0, 12.0), msg);
        }
        return;
    }

    BasicPacket *pkt = dynamic_cast<BasicPacket *>(msg);
    if (pkt) {
        EV << "✉️  Device " << deviceId << " RECEIVED packet from Device "
           << pkt->getSourceAddr() << ": " << pkt->getData() << endl;
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
