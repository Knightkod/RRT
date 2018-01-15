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

#ifndef __CASO3_SOURCE_H
#define __CASO3_SOURCE_H

#include <omnetpp.h>
#include "paqueteCustom_m.h"

using namespace omnetpp;

namespace caso3 {

/**
 * Generates messages; see NED file for more info.
 */
class Source : public cSimpleModule{
private:
    simtime_t lamda;
    simtime_t tiempoInicio;
    int       seqNumber;
    cMessage* newEvent;
    cChannel* txChannel;
protected:
    virtual void handleMessage(cMessage* msg) override;
    virtual void initialize() override;
    PaqueteCustom* generatePackage();
public:
    Source();
    virtual ~Source();
};


}; // namespace

#endif
