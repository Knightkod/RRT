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

#ifndef __CASO3_DESTINATION_H
#define __CASO3_DESTINATION_H

#include <omnetpp.h>
#include "paqueteCustom_m.h"

using namespace omnetpp;

namespace caso3 {

/**
 * Message sink; see NED file for more info.
 */
class Destination : public cSimpleModule
{
private:
    cChannel* txChannel;
    cQueue* txQueue;
    cMessage* evento;
    double probPacketLoss;
    double probAckLoss;
    double ackTam;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    PaqueteCustom* generatePackage(int error, unsigned int secuencia, simtime_t timestamp);
  public:
      Destination();
      virtual ~Destination();
};

}; // namespace

#endif
