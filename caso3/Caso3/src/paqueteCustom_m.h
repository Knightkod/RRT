//
// Generated file, do not edit! Created by nedtool 5.2 from paqueteCustom.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __CASO3_PAQUETECUSTOM_M_H
#define __CASO3_PAQUETECUSTOM_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0502
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif


namespace caso3 {

/**
 * Class generated from <tt>paqueteCustom.msg:21</tt> by nedtool.
 * <pre>
 * //
 * // TODO generated message class
 * //
 * packet PaqueteCustom
 * {
 *     unsigned int secuencia;
 *     short ack = -1; //0: NACK, 1:ACK
 *     simtime_t timestamp;
 *     simtime_t txFinish;
 * }
 * </pre>
 */
class PaqueteCustom : public ::omnetpp::cPacket
{
  protected:
    unsigned int secuencia;
    short ack;
    ::omnetpp::simtime_t timestamp;
    ::omnetpp::simtime_t txFinish;

  private:
    void copy(const PaqueteCustom& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const PaqueteCustom&);

  public:
    PaqueteCustom(const char *name=nullptr, short kind=0);
    PaqueteCustom(const PaqueteCustom& other);
    virtual ~PaqueteCustom();
    PaqueteCustom& operator=(const PaqueteCustom& other);
    virtual PaqueteCustom *dup() const override {return new PaqueteCustom(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual unsigned int getSecuencia() const;
    virtual void setSecuencia(unsigned int secuencia);
    virtual short getAck() const;
    virtual void setAck(short ack);
    virtual ::omnetpp::simtime_t getTimestamp() const;
    virtual void setTimestamp(::omnetpp::simtime_t timestamp);
    virtual ::omnetpp::simtime_t getTxFinish() const;
    virtual void setTxFinish(::omnetpp::simtime_t txFinish);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const PaqueteCustom& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, PaqueteCustom& obj) {obj.parsimUnpack(b);}

} // namespace caso3

#endif // ifndef __CASO3_PAQUETECUSTOM_M_H

