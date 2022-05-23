import org.omnetpp.queueing.Allocate;
import org.omnetpp.queueing.Deallocate;
import org.omnetpp.queueing.Delay;
import org.omnetpp.queueing.ResourcePool;
import org.omnetpp.queueing.SourceOnce;


network net
{
    @display("bgb=769,417");
    submodules:
        sorg: SourceOnce {
            @display("p=69,77");
        }
        disp_delay: Delay {
            @display("p=328,127");
        }
        allocate: Allocate {
            @display("p=420,127");
        }
        deallocate: Deallocate {
            @display("p=367,282");
        }
        serverList: ServerList {
            @display("p=569,127");
        }
        resourcePool: ResourcePool {
            @display("p=210,299");
        }
        dispatcher: Dispatcher {
            @display("p=190,127");
        }
    connections:
        sorg.out --> dispatcher.in++;
        disp_delay.out --> allocate.in++;
        serverList.out --> deallocate.in++;
        deallocate.out --> dispatcher.in++;
        dispatcher.out --> disp_delay.in++;
        allocate.out --> serverList.ext_in;
}
