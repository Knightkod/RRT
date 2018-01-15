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

#include "Source.h"

namespace caso3 {

Define_Module(Source);

Source::Source()
{
    this->seqNumber=0;
    this->newEvent = new cMessage("EmpiezaRetransmision");
}

Source::~Source()
{
    cancelAndDelete(newEvent);
}

void Source::initialize()
{

    this->tiempoInicio = par("tiempoInicio");
        this->lamda = par("lambda");
        scheduleAt(tiempoInicio, newEvent);
        txChannel = gate("out")->getTransmissionChannel();
}

void Source::handleMessage(cMessage *msg)
{
    simtime_t tiempoServicio;
        send(generatePackage(), "out");
        try {

            tiempoServicio = simTime() + exponential(lamda);
            if (tiempoServicio >= txChannel->getTransmissionFinishTime())
                scheduleAt(tiempoServicio, newEvent);
            else
                scheduleAt(txChannel->getTransmissionFinishTime(), newEvent);
        } catch (cException e) {
            delete(msg);
        }
}

PaqueteCustom* Source::generatePackage() {
    char nombre[15];
    double tamPkt = par("packageTam");
    sprintf(nombre, "msg-%d", seqNumber);
    PaqueteCustom* msg = new PaqueteCustom(nombre, 0);
    msg->setSecuencia(seqNumber++);
    msg->setBitLength(exponential(tamPkt));
    msg->setTimestamp(simTime());

    return msg;
}

}; // namespace
