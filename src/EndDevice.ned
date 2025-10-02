package routerfloodinglearningcapability;
// File: EndDevice.ned
simple EndDevice {
    parameters:
        int deviceId;
        @display("i=device/pc");
    gates:
        inout gate;
}