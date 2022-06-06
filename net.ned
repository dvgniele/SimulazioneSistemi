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

        @display("bgb=777,777");
    submodules:
        sorg: SourceOnce {
            @display("p=69,69");
        }
        disp_delay: Delay {
            @display("p=570,211");
        }
        dispatcher: Dispatcher {
            @display("p=160,211");
        }
        serverList: ServerList {
            @display("p=379,530");
        }
        poissonDelay: PoissonDelay {
            @display("p=160,69");
        }
    connections:
        dispatcher.out --> disp_delay.in++;
        disp_delay.out --> serverList.ext_in;
        serverList.out --> dispatcher.in;
        poissonDelay.out --> dispatcher.source_in;
        sorg.out --> poissonDelay.src_in;
        dispatcher.sink_out --> poissonDelay.ext_in;
}
