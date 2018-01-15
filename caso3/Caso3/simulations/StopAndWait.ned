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

package caso3.simulations;

import caso3.Source;
import caso3.Destination;
import caso3.QueueStopAndWait;

//
// Sample network, consisting of a source and a sink.
//
network StopAndWait
{
    parameters:
        **.lenACK=1;
        
    types:
        channel Canal extends ned.DatarateChannel
        {
            datarate = 10bps;
            per= 0.15; 
            delay=100s;           
        }
    submodules:
        source: Source{
             @display("p=100,33");
             lambda=150;
            tiempoInicio=10;
            packageTam=2048;
        }
        queue: QueueStopAndWait{
             @display("p=240,33");
        }
        dest: Destination{
            probACKLoss = 0.2;
            probPacketLoss = 0.2;           
             @display("p=100,200");
        }
        
    connections:
        source.out --> Canal --> queue.entradaFuente;
        dest.out --> Canal --> queue.in;
        queue.out --> Canal --> dest.in;
}
