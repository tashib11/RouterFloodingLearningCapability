package routerfloodinglearningcapability;
simple DNSServer {
    parameters:
        int serverId = default(101);
        @display("i=device/server");
    gates:
        inout gate;
}