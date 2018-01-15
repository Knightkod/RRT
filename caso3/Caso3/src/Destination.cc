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

#include "Destination.h"

namespace caso3 {

Define_Module(Destination);

Destination::Destination() {
    // TODO Auto-generated constructor stub
    txQueue = NULL;
    this->evento = new cMessage();
    this->probAckLoss = 0;
    this->probPacketLoss = 0;
    this->ackTam = 0;
}

Destination::~Destination() {
    // TODO Auto-generated destructor stub
    if (txQueue != NULL)
        txQueue->~cQueue();

    cancelAndDelete(evento);

}

void Destination::initialize() {
    txChannel = gate("out")->getTransmissionChannel();
    txQueue = new cQueue();
    this->probAckLoss = par("probACKLoss");
    this->probPacketLoss = par("probPacketLoss");
    this->ackTam = par("lenACK");
}

void Destination::handleMessage(cMessage *msg) {
    PaqueteCustom* pkt = NULL;

    if (msg == evento) {
        pkt = (PaqueteCustom*) txQueue->pop();
        if (uniform(0, 1) >= probAckLoss) {
            send(pkt, "out");

            if (!txQueue->isEmpty()) {
                scheduleAt(txChannel->getTransmissionFinishTime(), evento);
            }
        } else {
            EV << "LOST ON DESTINATION: " << pkt->getName() << "\n";

            if (!txQueue->isEmpty()) {
                scheduleAt(simTime(), evento);
            }

            delete (pkt);
        }
    } else {
        pkt = check_and_cast<PaqueteCustom *>(msg);

        if (uniform(0, 1) >= probPacketLoss) {

            PaqueteCustom* paquete = generatePackage(pkt->hasBitError() ? 1 : 0,
                    pkt->getSecuencia(), pkt->getTimestamp());
            if (txQueue->isEmpty()) {
                simtime_t timer = 0;

                if (simTime() >= txChannel->getTransmissionFinishTime())
                    timer = simTime();
                else
                    timer = txChannel->getTransmissionFinishTime();
                scheduleAt(timer, evento);
            }

            txQueue->insert(paquete);
        } else {
            EV << "LOST ON DESTINATION: " << pkt->getName() << "\n";
        }

        delete (pkt);
    }
}

PaqueteCustom* Destination::generatePackage(int error, unsigned int secuencia,
        simtime_t timestamp) {
    char nombre[15];

    if (error == 1) {
        sprintf(nombre, "NACK-%d", secuencia);
        EV << "DESTINATION NACK-" << secuencia << "\n";
    } else {
        sprintf(nombre, "ACK-%d", secuencia);
        EV << "DESTINATION ACK-" << secuencia << "\n";
    }

    PaqueteCustom* msg = new PaqueteCustom(nombre, 0);
    msg->setAck(!error);
    msg->setSecuencia(secuencia);
    msg->setBitLength(ackTam);
    msg->setTimestamp(timestamp);

    return msg;
}
}
// namespace
