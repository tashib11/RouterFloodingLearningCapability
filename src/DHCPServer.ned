package routerfloodinglearningcapability;
simple DHCPServer {
    parameters:
        int serverId = default(100);
        @display("i=device/server");
    gates:
        inout gate;
}