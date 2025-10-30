package routerfloodinglearningcapability;

network RouterFloodingNetwork {
    submodules:
        // End devices
        pc1: EndDevice {
            deviceId = 1;
            @display("p=100,200;i=device/pc");
        }

        pc2: EndDevice {
            deviceId = 2;
            @display("p=500,200;i=device/pc");
        }

        pc3: EndDevice {
            deviceId = 3;
            @display("p=300,400;i=device/pc");
        }

        // Routers
        router1: LearningRouter {
            routerId = 10;
            @display("p=200,200;i=abstract/router");
        }

        router2: LearningRouter {
            routerId = 11;
            @display("p=400,200;i=abstract/router");
        }

        router3: LearningRouter {
            routerId = 12;
            @display("p=300,300;i=abstract/router");
        }

        router4: LearningRouter {
            routerId = 13;
            @display("p=400,400;i=abstract/router");
        }

        // Servers
        dhcpServer: DHCPServer {
            serverId = 100;
            @display("p=150,100;i=device/server");
        }

        dnsServer: DNSServer {
            serverId = 101;
            @display("p=450,100;i=device/server");
        }

        youtubeServer: WebServer {
            serverId = 200;
            hostname = "youtube.com";
            @display("p=500,450;i=device/server2");
        }

    connections:
        // Connect PCs to routers with gate labels
        pc1.gate <--> {  @display("t=R1:G0"); } <--> router1.gate++;    // Router1 Gate 0
        pc2.gate <--> {  @display("t=R2:G0"); } <--> router2.gate++;    // Router2 Gate 0
        pc3.gate <--> {  @display("t=R3:G0"); } <--> router3.gate++;    // Router3 Gate 0

  // Connect routers to each other with gate labels
    router1.gate++ <--> {  @display("t=R1:G1-R2:G1"); } <--> router2.gate++;
    router2.gate++ <--> {  @display("t=R2:G2-R3:G1"); } <--> router3.gate++;
    router3.gate++ <--> {  @display("t=R3:G2-R1:G2"); } <--> router1.gate++;
    router3.gate++ <--> {  @display("t=R3:G3-R4:G0"); } <--> router4.gate++;

        // Connect servers with gate labels
        dhcpServer.gate <--> {  @display("t=R1:G3"); } <--> router1.gate++;       // Router1 Gate 3
        dnsServer.gate <--> {  @display("t=R2:G3"); } <--> router2.gate++;        // Router2 Gate 3
        youtubeServer.gate <--> {  @display("t=R4:G1"); } <--> router4.gate++;    // Router4 Gate 1
}
