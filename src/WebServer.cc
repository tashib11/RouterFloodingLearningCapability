#include "WebServer.h"

Define_Module(WebServer);

void WebServer::initialize() {
    serverId = par("serverId");
    hostname = par("hostname").stdstringValue();

    EV << "========================================" << endl;
    EV << "Web Server initialized" << endl;
    EV << "  Server ID: " << serverId << endl;
    EV << "  Hostname: " << hostname << endl;
    EV << "========================================" << endl;
}

void WebServer::handleMessage(cMessage *msg) {
    BasicPacket *pkt = dynamic_cast<BasicPacket *>(msg);
    if (pkt && pkt->getDestAddr() == serverId) {
        EV << "========================================" << endl;
        EV << "YouTube Server (" << hostname << ") received request" << endl;
        EV << "  From: Device " << pkt->getSourceAddr() << endl;
        EV << "  Data: " << pkt->getData() << endl;
        EV << "========================================" << endl;

        // Send response back
        BasicPacket *response = new BasicPacket("webResponse");
        response->setSourceAddr(serverId);
        response->setDestAddr(pkt->getSourceAddr());
        response->setData("VIDEO_DATA");

        send(response, "gate$o");

        EV << "YouTube Server sent video data to Device "
           << pkt->getSourceAddr() << endl;
    }

    delete msg;
}
