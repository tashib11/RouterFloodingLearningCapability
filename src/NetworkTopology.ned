package routerfloodinglearningcapability;

network RouterFloodingNetwork {
    submodules:
        // End devices
        pc1: EndDevice {
            deviceId = 1;
            @display("p=100,200");
        }

        pc2: EndDevice {
            deviceId = 2;
            @display("p=500,200");
        }

        pc3: EndDevice {
            deviceId = 3;
            @display("p=300,400");
        }

        // Routers
        router1: LearningRouter {
            routerId = 1;
            @display("p=200,200");
        }

        router2: LearningRouter {
            routerId = 2;
            @display("p=400,200");
        }

        router3: LearningRouter {
            routerId = 3;
            @display("p=300,300");
        }

        // Servers
        dhcpServer: DHCPServer {
            serverId = 100;
            @display("p=150,100");
        }

        dnsServer: DNSServer {
            serverId = 101;
            @display("p=450,100");
        }

    connections:
        // Connect PCs to routers
        pc1.gate <--> router1.gate++;
        pc2.gate <--> router2.gate++;
        pc3.gate <--> router3.gate++;

        // Connect routers to each other
        router1.gate++ <--> router2.gate++;
        router2.gate++ <--> router3.gate++;
        router3.gate++ <--> router1.gate++;

        // Connect servers
        dhcpServer.gate <--> router1.gate++;
        dnsServer.gate <--> router2.gate++;
}
