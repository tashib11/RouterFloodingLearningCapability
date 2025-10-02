#ifndef ENDDEVICE_H
#define ENDDEVICE_H

#include <omnetpp.h>
#include "Packet_m_m.h"

using namespace omnetpp;

class EndDevice : public cSimpleModule {
private:
    int deviceId;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void sendTestPacket();
};

#endif
