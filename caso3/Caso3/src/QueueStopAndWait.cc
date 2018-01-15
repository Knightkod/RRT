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

#include "QueueStopAndWait.h"

namespace caso3 {

Define_Module(QueueStopAndWait);

QueueStopAndWait::QueueStopAndWait() {
    // TODO Auto-generated constructor stub
    ackTam = 0;
    evento = new cMessage();
    timeoutEvento = new cMessage();
    startEventTimeout = new cMessage();
    sendMsg = NULL;

}

QueueStopAndWait::~QueueStopAndWait() {
    cancelAndDelete(evento);
    cancelAndDelete(timeoutEvento);
    cancelAndDelete(startEventTimeout);

    // TODO Auto-generated destructor stub
}

void QueueStopAndWait::initialize() {
    txChannel = (cDatarateChannel*) gate("out")->getTransmissionChannel();
    txQueue = new cQueue();
    ackTam = par("lenACK");
}

void QueueStopAndWait::handleMessage(cMessage* msg) {
    PaqueteCustom* paquete = NULL;

    if (msg == evento) {
        paquete = (PaqueteCustom*) txQueue->pop();
        sendMsg = paquete->dup();

        EV << "msg: " << sendMsg->getName();
        send(paquete, "out");

        scheduleAt(txChannel->getTransmissionFinishTime(), startEventTimeout);

    } else if (msg == timeoutEvento) {
        if (simTime() >= txChannel->getTransmissionFinishTime()) {
            EV << "Timeout msg: : " << sendMsg->getName();
            sendMsg->setTimestamp(simTime());
            send(sendMsg->dup(), "out");
            scheduleAt(txChannel->getTransmissionFinishTime(),
                    startEventTimeout);

        } else {
            scheduleAt(txChannel->getTransmissionFinishTime(), timeoutEvento);
        }

    } else if (msg == startEventTimeout) {
        scheduleAt(
                simTime() + (txChannel->getDelay()) * 2
                        + (ackTam / txChannel->getDatarate()) + 1,
                timeoutEvento);
    } else {
        paquete = check_and_cast<PaqueteCustom *>(msg);

        if (msg->arrivedOn("entradaFuente")) {


            sendCopyOf(paquete);

        } else if (msg->arrivedOn("in")) {

            if (sendMsg->getTimestamp() == paquete->getTimestamp()
                    && sendMsg->getSecuencia()
                            == paquete->getSecuencia()) {
                cancelEvent (timeoutEvento);
                if (startEventTimeout->isScheduled())
                    cancelEvent (startEventTimeout);

                if (paquete->hasBitError() || paquete->getAck() == 0) {
                    EV << "ERROR ON ACK/NACK, RESEND: "
                              << sendMsg->getName();
                    sendMsg->setTimestamp(simTime());
                    send(sendMsg->dup(), "out");
                    scheduleAt(txChannel->getTransmissionFinishTime(),
                            startEventTimeout);

                } else {
                    EV << "ACK: " << sendMsg->getName();
                    delete (sendMsg);
                    sendMsg = NULL;

                    if (!txQueue->isEmpty()) {
                        scheduleAt(simTime(), evento);
                    }
                }
            } else {
                EV << "old package";
            }
        }

        delete (paquete);
    }
}
void QueueStopAndWait::sendCopyOf(PaqueteCustom* paquete) {

    if (txQueue->isEmpty() && sendMsg == NULL) {
        simtime_t timer = 0;

        if (simTime() >= txChannel->getTransmissionFinishTime())
            timer = simTime();
        else
            timer = txChannel->getTransmissionFinishTime();

        scheduleAt(timer, evento);
    }

    txQueue->insert(paquete->dup());
}

} /* namespace caso3 */
