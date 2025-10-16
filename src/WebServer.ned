package routerfloodinglearningcapability;
simple WebServer {
    parameters:
        int serverId = default(200);
        string hostname = default("server.com");
        @display("i=device/server2");
    gates:
        inout gate;
}