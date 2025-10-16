packet BasicPacket {
    int sourceAddr;
    int destAddr;
    string data;
    int hopCount = 0;
    bool isFlooded = false;
}

packet RouteInfoPacket {
    int destAddr;          // Which destination was found
    int reporterAddr;      // Router reporting the route
    int gateToDestination; // Which gate leads to destination
}

packet DHCPRequest {
    string clientMAC;
}

packet DHCPResponse {
    string clientMAC;
    int assignedAddr;
}

packet DNSQuery {
    string hostname;
    int sourceAddr;
<<<<<<< HEAD
    int queryId;
=======
>>>>>>> origin/main
}

packet DNSResponse {
    string hostname;
<<<<<<< HEAD
    int resolvedAddr;
    int destAddr;
    int queryId;
=======
    int ipAddr;
>>>>>>> origin/main
}