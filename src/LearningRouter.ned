package routerfloodinglearningcapability;
simple LearningRouter {
    parameters:
        int routerId;
        @display("i=abstract/router");
    gates:
        inout gate[];
}

