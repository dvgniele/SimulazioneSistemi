//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

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
        allocate.out --> serverList.in++;
        serverList.out --> deallocate.in++;
        deallocate.out --> dispatcher.in++;
        dispatcher.out --> disp_delay.in++;
}
