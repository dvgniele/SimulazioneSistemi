import org.omnetpp.queueing.Allocate;
import org.omnetpp.queueing.Deallocate;
import org.omnetpp.queueing.Delay;
import org.omnetpp.queueing.PassiveQueue;
import org.omnetpp.queueing.Queue;
import org.omnetpp.queueing.ResourcePool;
import org.omnetpp.queueing.Server;
import org.omnetpp.queueing.SourceOnce;


network net
{
    parameters:
        volatile int n_servers;
        string moduleType = "org.omnetpp.queueing.Queue";
        string moduleName = "server";
        volatile double sTime @unit(s);


        @display("bgb=769,417");
    submodules:
        sorg: SourceOnce {
            @display("p=69,77");
        }
        disp_delay: Delay {
            @display("p=494,77");
        }
        dispatcher: Dispatcher {
            @display("p=197,77");
        }
        serverList: ServerList {
            @display("p=361,222");
        }
    connections:
        sorg.out --> dispatcher.in++;
        dispatcher.out --> disp_delay.in++;
        serverList.out --> dispatcher.in++;
        disp_delay.out --> serverList.ext_in;
}
