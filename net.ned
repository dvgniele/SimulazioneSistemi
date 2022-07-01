import org.omnetpp.queueing.Allocate;
import org.omnetpp.queueing.Deallocate;
import org.omnetpp.queueing.Delay;
import org.omnetpp.queueing.PassiveQueue;
import org.omnetpp.queueing.Queue;
import org.omnetpp.queueing.ResourceBasedQueue;
import org.omnetpp.queueing.ResourcePool;
import org.omnetpp.queueing.Server;
import org.omnetpp.queueing.Sink;
import org.omnetpp.queueing.Source;
import org.omnetpp.queueing.SourceOnce;


network net
{
    parameters:
        volatile int n_servers;
        string moduleType = "org.omnetpp.queueing.Queue";
        string moduleName = "server";
        volatile double serverServiceTime @unit(s);

        @display("bgb=777,777");
    submodules:
        dispatcher: Dispatcher {
            @display("p=417,217");
        }
        serverList: ServerList {
            @display("p=417,517");
        }
        sink: Sink {
            @display("p=69,217");
        }
        sorg: Source {
            @display("p=68.728004,68.728004");
        }
    connections:
        dispatcher.sink_out --> sink.in++;
        serverList.out --> dispatcher.ext_in;
        dispatcher.out --> serverList.ext_in;
        sorg.out --> dispatcher.source_in;
}
