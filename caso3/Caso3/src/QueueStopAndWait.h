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

#ifndef QUEUESTOPANDWAIT_H_
#define QUEUESTOPANDWAIT_H_

#include <omnetpp.h>
#include "paqueteCustom_m.h"

using namespace omnetpp;

namespace caso3 {

class QueueStopAndWait : public cSimpleModule{
public:
    QueueStopAndWait();
    virtual ~QueueStopAndWait();

protected:
  virtual void initialize();
  virtual void handleMessage(cMessage *msg);
  void sendCopyOf(PaqueteCustom* paquete);

private:
  double    ackTam;
  cDatarateChannel* txChannel;
  cQueue*   txQueue;
  cMessage* evento;
  cMessage* timeoutEvento;
  cMessage* startEventTimeout;
  PaqueteCustom*  sendMsg;
};

}; /* namespace caso3 */

#endif /* QUEUESTOPANDWAIT_H_ */
