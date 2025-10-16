packet BasicPacket {
    int sourceAddr;
    int destAddr;
    string destHostname;      // NEW: For hostname-based addressing
    string data;
    int hopCount = 0;
    bool isFlooded = false;
    bool needsDNSResolution = false;  // NEW: Flag for router to query DNS
}

packet RouteInfoPacket {
    int destAddr;
    int reporterAddr;
    int gateToDestination;
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
    int queryId;
    int originalPacketId;     // NEW: To track original packet
}

packet DNSResponse {
    string hostname;
    int resolvedAddr;
    int destAddr;
    int queryId;
    int originalPacketId;     // NEW: To track original packet
}