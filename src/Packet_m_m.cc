//
// Generated file, do not edit! Created by opp_msgtool 6.2 from Packet_m.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "Packet_m_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(BasicPacket)

BasicPacket::BasicPacket(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

BasicPacket::BasicPacket(const BasicPacket& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

BasicPacket::~BasicPacket()
{
}

BasicPacket& BasicPacket::operator=(const BasicPacket& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void BasicPacket::copy(const BasicPacket& other)
{
    this->sourceAddr = other.sourceAddr;
    this->destAddr = other.destAddr;
    this->data = other.data;
    this->hopCount = other.hopCount;
    this->isFlooded_ = other.isFlooded_;
}

void BasicPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->sourceAddr);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->data);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->isFlooded_);
}

void BasicPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->sourceAddr);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->data);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->isFlooded_);
}

int BasicPacket::getSourceAddr() const
{
    return this->sourceAddr;
}

void BasicPacket::setSourceAddr(int sourceAddr)
{
    this->sourceAddr = sourceAddr;
}

int BasicPacket::getDestAddr() const
{
    return this->destAddr;
}

void BasicPacket::setDestAddr(int destAddr)
{
    this->destAddr = destAddr;
}

const char * BasicPacket::getData() const
{
    return this->data.c_str();
}

void BasicPacket::setData(const char * data)
{
    this->data = data;
}

int BasicPacket::getHopCount() const
{
    return this->hopCount;
}

void BasicPacket::setHopCount(int hopCount)
{
    this->hopCount = hopCount;
}

bool BasicPacket::isFlooded() const
{
    return this->isFlooded_;
}

void BasicPacket::setIsFlooded(bool isFlooded)
{
    this->isFlooded_ = isFlooded;
}

class BasicPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sourceAddr,
        FIELD_destAddr,
        FIELD_data,
        FIELD_hopCount,
        FIELD_isFlooded,
    };
  public:
    BasicPacketDescriptor();
    virtual ~BasicPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(BasicPacketDescriptor)

BasicPacketDescriptor::BasicPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(BasicPacket)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

BasicPacketDescriptor::~BasicPacketDescriptor()
{
    delete[] propertyNames;
}

bool BasicPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<BasicPacket *>(obj)!=nullptr;
}

const char **BasicPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *BasicPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int BasicPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int BasicPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sourceAddr
        FD_ISEDITABLE,    // FIELD_destAddr
        FD_ISEDITABLE,    // FIELD_data
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISEDITABLE,    // FIELD_isFlooded
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *BasicPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sourceAddr",
        "destAddr",
        "data",
        "hopCount",
        "isFlooded",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int BasicPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sourceAddr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destAddr") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "data") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "hopCount") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "isFlooded") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *BasicPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_sourceAddr
        "int",    // FIELD_destAddr
        "string",    // FIELD_data
        "int",    // FIELD_hopCount
        "bool",    // FIELD_isFlooded
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **BasicPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *BasicPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int BasicPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    BasicPacket *pp = omnetpp::fromAnyPtr<BasicPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void BasicPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    BasicPacket *pp = omnetpp::fromAnyPtr<BasicPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'BasicPacket'", field);
    }
}

const char *BasicPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    BasicPacket *pp = omnetpp::fromAnyPtr<BasicPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string BasicPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    BasicPacket *pp = omnetpp::fromAnyPtr<BasicPacket>(object); (void)pp;
    switch (field) {
        case FIELD_sourceAddr: return long2string(pp->getSourceAddr());
        case FIELD_destAddr: return long2string(pp->getDestAddr());
        case FIELD_data: return oppstring2string(pp->getData());
        case FIELD_hopCount: return long2string(pp->getHopCount());
        case FIELD_isFlooded: return bool2string(pp->isFlooded());
        default: return "";
    }
}

void BasicPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BasicPacket *pp = omnetpp::fromAnyPtr<BasicPacket>(object); (void)pp;
    switch (field) {
        case FIELD_sourceAddr: pp->setSourceAddr(string2long(value)); break;
        case FIELD_destAddr: pp->setDestAddr(string2long(value)); break;
        case FIELD_data: pp->setData((value)); break;
        case FIELD_hopCount: pp->setHopCount(string2long(value)); break;
        case FIELD_isFlooded: pp->setIsFlooded(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BasicPacket'", field);
    }
}

omnetpp::cValue BasicPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    BasicPacket *pp = omnetpp::fromAnyPtr<BasicPacket>(object); (void)pp;
    switch (field) {
        case FIELD_sourceAddr: return pp->getSourceAddr();
        case FIELD_destAddr: return pp->getDestAddr();
        case FIELD_data: return pp->getData();
        case FIELD_hopCount: return pp->getHopCount();
        case FIELD_isFlooded: return pp->isFlooded();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'BasicPacket' as cValue -- field index out of range?", field);
    }
}

void BasicPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    BasicPacket *pp = omnetpp::fromAnyPtr<BasicPacket>(object); (void)pp;
    switch (field) {
        case FIELD_sourceAddr: pp->setSourceAddr(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_destAddr: pp->setDestAddr(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_data: pp->setData(value.stringValue()); break;
        case FIELD_hopCount: pp->setHopCount(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_isFlooded: pp->setIsFlooded(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BasicPacket'", field);
    }
}

const char *BasicPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr BasicPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    BasicPacket *pp = omnetpp::fromAnyPtr<BasicPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void BasicPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    BasicPacket *pp = omnetpp::fromAnyPtr<BasicPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'BasicPacket'", field);
    }
}

Register_Class(RouteInfoPacket)

RouteInfoPacket::RouteInfoPacket(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

RouteInfoPacket::RouteInfoPacket(const RouteInfoPacket& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

RouteInfoPacket::~RouteInfoPacket()
{
}

RouteInfoPacket& RouteInfoPacket::operator=(const RouteInfoPacket& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void RouteInfoPacket::copy(const RouteInfoPacket& other)
{
    this->destAddr = other.destAddr;
    this->reporterAddr = other.reporterAddr;
    this->gateToDestination = other.gateToDestination;
}

void RouteInfoPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->reporterAddr);
    doParsimPacking(b,this->gateToDestination);
}

void RouteInfoPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->reporterAddr);
    doParsimUnpacking(b,this->gateToDestination);
}

int RouteInfoPacket::getDestAddr() const
{
    return this->destAddr;
}

void RouteInfoPacket::setDestAddr(int destAddr)
{
    this->destAddr = destAddr;
}

int RouteInfoPacket::getReporterAddr() const
{
    return this->reporterAddr;
}

void RouteInfoPacket::setReporterAddr(int reporterAddr)
{
    this->reporterAddr = reporterAddr;
}

int RouteInfoPacket::getGateToDestination() const
{
    return this->gateToDestination;
}

void RouteInfoPacket::setGateToDestination(int gateToDestination)
{
    this->gateToDestination = gateToDestination;
}

class RouteInfoPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_destAddr,
        FIELD_reporterAddr,
        FIELD_gateToDestination,
    };
  public:
    RouteInfoPacketDescriptor();
    virtual ~RouteInfoPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(RouteInfoPacketDescriptor)

RouteInfoPacketDescriptor::RouteInfoPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(RouteInfoPacket)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

RouteInfoPacketDescriptor::~RouteInfoPacketDescriptor()
{
    delete[] propertyNames;
}

bool RouteInfoPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RouteInfoPacket *>(obj)!=nullptr;
}

const char **RouteInfoPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RouteInfoPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RouteInfoPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int RouteInfoPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_destAddr
        FD_ISEDITABLE,    // FIELD_reporterAddr
        FD_ISEDITABLE,    // FIELD_gateToDestination
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *RouteInfoPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "destAddr",
        "reporterAddr",
        "gateToDestination",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int RouteInfoPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "destAddr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "reporterAddr") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "gateToDestination") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *RouteInfoPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_destAddr
        "int",    // FIELD_reporterAddr
        "int",    // FIELD_gateToDestination
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **RouteInfoPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *RouteInfoPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int RouteInfoPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RouteInfoPacket *pp = omnetpp::fromAnyPtr<RouteInfoPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RouteInfoPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RouteInfoPacket *pp = omnetpp::fromAnyPtr<RouteInfoPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RouteInfoPacket'", field);
    }
}

const char *RouteInfoPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RouteInfoPacket *pp = omnetpp::fromAnyPtr<RouteInfoPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RouteInfoPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RouteInfoPacket *pp = omnetpp::fromAnyPtr<RouteInfoPacket>(object); (void)pp;
    switch (field) {
        case FIELD_destAddr: return long2string(pp->getDestAddr());
        case FIELD_reporterAddr: return long2string(pp->getReporterAddr());
        case FIELD_gateToDestination: return long2string(pp->getGateToDestination());
        default: return "";
    }
}

void RouteInfoPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RouteInfoPacket *pp = omnetpp::fromAnyPtr<RouteInfoPacket>(object); (void)pp;
    switch (field) {
        case FIELD_destAddr: pp->setDestAddr(string2long(value)); break;
        case FIELD_reporterAddr: pp->setReporterAddr(string2long(value)); break;
        case FIELD_gateToDestination: pp->setGateToDestination(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RouteInfoPacket'", field);
    }
}

omnetpp::cValue RouteInfoPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RouteInfoPacket *pp = omnetpp::fromAnyPtr<RouteInfoPacket>(object); (void)pp;
    switch (field) {
        case FIELD_destAddr: return pp->getDestAddr();
        case FIELD_reporterAddr: return pp->getReporterAddr();
        case FIELD_gateToDestination: return pp->getGateToDestination();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RouteInfoPacket' as cValue -- field index out of range?", field);
    }
}

void RouteInfoPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RouteInfoPacket *pp = omnetpp::fromAnyPtr<RouteInfoPacket>(object); (void)pp;
    switch (field) {
        case FIELD_destAddr: pp->setDestAddr(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_reporterAddr: pp->setReporterAddr(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_gateToDestination: pp->setGateToDestination(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RouteInfoPacket'", field);
    }
}

const char *RouteInfoPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr RouteInfoPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RouteInfoPacket *pp = omnetpp::fromAnyPtr<RouteInfoPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RouteInfoPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RouteInfoPacket *pp = omnetpp::fromAnyPtr<RouteInfoPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RouteInfoPacket'", field);
    }
}

Register_Class(DHCPRequest)

DHCPRequest::DHCPRequest(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

DHCPRequest::DHCPRequest(const DHCPRequest& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

DHCPRequest::~DHCPRequest()
{
}

DHCPRequest& DHCPRequest::operator=(const DHCPRequest& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void DHCPRequest::copy(const DHCPRequest& other)
{
    this->clientMAC = other.clientMAC;
}

void DHCPRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->clientMAC);
}

void DHCPRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->clientMAC);
}

const char * DHCPRequest::getClientMAC() const
{
    return this->clientMAC.c_str();
}

void DHCPRequest::setClientMAC(const char * clientMAC)
{
    this->clientMAC = clientMAC;
}

class DHCPRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_clientMAC,
    };
  public:
    DHCPRequestDescriptor();
    virtual ~DHCPRequestDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(DHCPRequestDescriptor)

DHCPRequestDescriptor::DHCPRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(DHCPRequest)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

DHCPRequestDescriptor::~DHCPRequestDescriptor()
{
    delete[] propertyNames;
}

bool DHCPRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DHCPRequest *>(obj)!=nullptr;
}

const char **DHCPRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *DHCPRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int DHCPRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int DHCPRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_clientMAC
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *DHCPRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "clientMAC",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int DHCPRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "clientMAC") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *DHCPRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_clientMAC
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **DHCPRequestDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *DHCPRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int DHCPRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    DHCPRequest *pp = omnetpp::fromAnyPtr<DHCPRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void DHCPRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPRequest *pp = omnetpp::fromAnyPtr<DHCPRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'DHCPRequest'", field);
    }
}

const char *DHCPRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    DHCPRequest *pp = omnetpp::fromAnyPtr<DHCPRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DHCPRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    DHCPRequest *pp = omnetpp::fromAnyPtr<DHCPRequest>(object); (void)pp;
    switch (field) {
        case FIELD_clientMAC: return oppstring2string(pp->getClientMAC());
        default: return "";
    }
}

void DHCPRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPRequest *pp = omnetpp::fromAnyPtr<DHCPRequest>(object); (void)pp;
    switch (field) {
        case FIELD_clientMAC: pp->setClientMAC((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DHCPRequest'", field);
    }
}

omnetpp::cValue DHCPRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    DHCPRequest *pp = omnetpp::fromAnyPtr<DHCPRequest>(object); (void)pp;
    switch (field) {
        case FIELD_clientMAC: return pp->getClientMAC();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'DHCPRequest' as cValue -- field index out of range?", field);
    }
}

void DHCPRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPRequest *pp = omnetpp::fromAnyPtr<DHCPRequest>(object); (void)pp;
    switch (field) {
        case FIELD_clientMAC: pp->setClientMAC(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DHCPRequest'", field);
    }
}

const char *DHCPRequestDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr DHCPRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    DHCPRequest *pp = omnetpp::fromAnyPtr<DHCPRequest>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void DHCPRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPRequest *pp = omnetpp::fromAnyPtr<DHCPRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DHCPRequest'", field);
    }
}

Register_Class(DHCPResponse)

DHCPResponse::DHCPResponse(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

DHCPResponse::DHCPResponse(const DHCPResponse& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

DHCPResponse::~DHCPResponse()
{
}

DHCPResponse& DHCPResponse::operator=(const DHCPResponse& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void DHCPResponse::copy(const DHCPResponse& other)
{
    this->clientMAC = other.clientMAC;
    this->assignedAddr = other.assignedAddr;
}

void DHCPResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->clientMAC);
    doParsimPacking(b,this->assignedAddr);
}

void DHCPResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->clientMAC);
    doParsimUnpacking(b,this->assignedAddr);
}

const char * DHCPResponse::getClientMAC() const
{
    return this->clientMAC.c_str();
}

void DHCPResponse::setClientMAC(const char * clientMAC)
{
    this->clientMAC = clientMAC;
}

int DHCPResponse::getAssignedAddr() const
{
    return this->assignedAddr;
}

void DHCPResponse::setAssignedAddr(int assignedAddr)
{
    this->assignedAddr = assignedAddr;
}

class DHCPResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_clientMAC,
        FIELD_assignedAddr,
    };
  public:
    DHCPResponseDescriptor();
    virtual ~DHCPResponseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(DHCPResponseDescriptor)

DHCPResponseDescriptor::DHCPResponseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(DHCPResponse)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

DHCPResponseDescriptor::~DHCPResponseDescriptor()
{
    delete[] propertyNames;
}

bool DHCPResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DHCPResponse *>(obj)!=nullptr;
}

const char **DHCPResponseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *DHCPResponseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int DHCPResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int DHCPResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_clientMAC
        FD_ISEDITABLE,    // FIELD_assignedAddr
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *DHCPResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "clientMAC",
        "assignedAddr",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int DHCPResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "clientMAC") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "assignedAddr") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *DHCPResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_clientMAC
        "int",    // FIELD_assignedAddr
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **DHCPResponseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *DHCPResponseDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int DHCPResponseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    DHCPResponse *pp = omnetpp::fromAnyPtr<DHCPResponse>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void DHCPResponseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPResponse *pp = omnetpp::fromAnyPtr<DHCPResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'DHCPResponse'", field);
    }
}

const char *DHCPResponseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    DHCPResponse *pp = omnetpp::fromAnyPtr<DHCPResponse>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DHCPResponseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    DHCPResponse *pp = omnetpp::fromAnyPtr<DHCPResponse>(object); (void)pp;
    switch (field) {
        case FIELD_clientMAC: return oppstring2string(pp->getClientMAC());
        case FIELD_assignedAddr: return long2string(pp->getAssignedAddr());
        default: return "";
    }
}

void DHCPResponseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPResponse *pp = omnetpp::fromAnyPtr<DHCPResponse>(object); (void)pp;
    switch (field) {
        case FIELD_clientMAC: pp->setClientMAC((value)); break;
        case FIELD_assignedAddr: pp->setAssignedAddr(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DHCPResponse'", field);
    }
}

omnetpp::cValue DHCPResponseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    DHCPResponse *pp = omnetpp::fromAnyPtr<DHCPResponse>(object); (void)pp;
    switch (field) {
        case FIELD_clientMAC: return pp->getClientMAC();
        case FIELD_assignedAddr: return pp->getAssignedAddr();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'DHCPResponse' as cValue -- field index out of range?", field);
    }
}

void DHCPResponseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPResponse *pp = omnetpp::fromAnyPtr<DHCPResponse>(object); (void)pp;
    switch (field) {
        case FIELD_clientMAC: pp->setClientMAC(value.stringValue()); break;
        case FIELD_assignedAddr: pp->setAssignedAddr(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DHCPResponse'", field);
    }
}

const char *DHCPResponseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr DHCPResponseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    DHCPResponse *pp = omnetpp::fromAnyPtr<DHCPResponse>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void DHCPResponseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPResponse *pp = omnetpp::fromAnyPtr<DHCPResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DHCPResponse'", field);
    }
}

Register_Class(DNSQuery)

DNSQuery::DNSQuery(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

DNSQuery::DNSQuery(const DNSQuery& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

DNSQuery::~DNSQuery()
{
}

DNSQuery& DNSQuery::operator=(const DNSQuery& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void DNSQuery::copy(const DNSQuery& other)
{
    this->hostname = other.hostname;
    this->sourceAddr = other.sourceAddr;
<<<<<<< HEAD
    this->queryId = other.queryId;
=======
>>>>>>> origin/main
}

void DNSQuery::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->hostname);
    doParsimPacking(b,this->sourceAddr);
<<<<<<< HEAD
    doParsimPacking(b,this->queryId);
=======
>>>>>>> origin/main
}

void DNSQuery::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->hostname);
    doParsimUnpacking(b,this->sourceAddr);
<<<<<<< HEAD
    doParsimUnpacking(b,this->queryId);
=======
>>>>>>> origin/main
}

const char * DNSQuery::getHostname() const
{
    return this->hostname.c_str();
}

void DNSQuery::setHostname(const char * hostname)
{
    this->hostname = hostname;
}

int DNSQuery::getSourceAddr() const
{
    return this->sourceAddr;
}

void DNSQuery::setSourceAddr(int sourceAddr)
{
    this->sourceAddr = sourceAddr;
}

<<<<<<< HEAD
int DNSQuery::getQueryId() const
{
    return this->queryId;
}

void DNSQuery::setQueryId(int queryId)
{
    this->queryId = queryId;
}

=======
>>>>>>> origin/main
class DNSQueryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_hostname,
        FIELD_sourceAddr,
<<<<<<< HEAD
        FIELD_queryId,
=======
>>>>>>> origin/main
    };
  public:
    DNSQueryDescriptor();
    virtual ~DNSQueryDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(DNSQueryDescriptor)

DNSQueryDescriptor::DNSQueryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(DNSQuery)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

DNSQueryDescriptor::~DNSQueryDescriptor()
{
    delete[] propertyNames;
}

bool DNSQueryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DNSQuery *>(obj)!=nullptr;
}

const char **DNSQueryDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *DNSQueryDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int DNSQueryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
<<<<<<< HEAD
    return base ? 3+base->getFieldCount() : 3;
=======
    return base ? 2+base->getFieldCount() : 2;
>>>>>>> origin/main
}

unsigned int DNSQueryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_hostname
        FD_ISEDITABLE,    // FIELD_sourceAddr
<<<<<<< HEAD
        FD_ISEDITABLE,    // FIELD_queryId
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
=======
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
>>>>>>> origin/main
}

const char *DNSQueryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hostname",
        "sourceAddr",
<<<<<<< HEAD
        "queryId",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
=======
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
>>>>>>> origin/main
}

int DNSQueryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "hostname") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sourceAddr") == 0) return baseIndex + 1;
<<<<<<< HEAD
    if (strcmp(fieldName, "queryId") == 0) return baseIndex + 2;
=======
>>>>>>> origin/main
    return base ? base->findField(fieldName) : -1;
}

const char *DNSQueryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_hostname
        "int",    // FIELD_sourceAddr
<<<<<<< HEAD
        "int",    // FIELD_queryId
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
=======
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
>>>>>>> origin/main
}

const char **DNSQueryDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *DNSQueryDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int DNSQueryDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    DNSQuery *pp = omnetpp::fromAnyPtr<DNSQuery>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void DNSQueryDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    DNSQuery *pp = omnetpp::fromAnyPtr<DNSQuery>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'DNSQuery'", field);
    }
}

const char *DNSQueryDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    DNSQuery *pp = omnetpp::fromAnyPtr<DNSQuery>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DNSQueryDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    DNSQuery *pp = omnetpp::fromAnyPtr<DNSQuery>(object); (void)pp;
    switch (field) {
        case FIELD_hostname: return oppstring2string(pp->getHostname());
        case FIELD_sourceAddr: return long2string(pp->getSourceAddr());
<<<<<<< HEAD
        case FIELD_queryId: return long2string(pp->getQueryId());
=======
>>>>>>> origin/main
        default: return "";
    }
}

void DNSQueryDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DNSQuery *pp = omnetpp::fromAnyPtr<DNSQuery>(object); (void)pp;
    switch (field) {
        case FIELD_hostname: pp->setHostname((value)); break;
        case FIELD_sourceAddr: pp->setSourceAddr(string2long(value)); break;
<<<<<<< HEAD
        case FIELD_queryId: pp->setQueryId(string2long(value)); break;
=======
>>>>>>> origin/main
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DNSQuery'", field);
    }
}

omnetpp::cValue DNSQueryDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    DNSQuery *pp = omnetpp::fromAnyPtr<DNSQuery>(object); (void)pp;
    switch (field) {
        case FIELD_hostname: return pp->getHostname();
        case FIELD_sourceAddr: return pp->getSourceAddr();
<<<<<<< HEAD
        case FIELD_queryId: return pp->getQueryId();
=======
>>>>>>> origin/main
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'DNSQuery' as cValue -- field index out of range?", field);
    }
}

void DNSQueryDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DNSQuery *pp = omnetpp::fromAnyPtr<DNSQuery>(object); (void)pp;
    switch (field) {
        case FIELD_hostname: pp->setHostname(value.stringValue()); break;
        case FIELD_sourceAddr: pp->setSourceAddr(omnetpp::checked_int_cast<int>(value.intValue())); break;
<<<<<<< HEAD
        case FIELD_queryId: pp->setQueryId(omnetpp::checked_int_cast<int>(value.intValue())); break;
=======
>>>>>>> origin/main
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DNSQuery'", field);
    }
}

const char *DNSQueryDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr DNSQueryDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    DNSQuery *pp = omnetpp::fromAnyPtr<DNSQuery>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void DNSQueryDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    DNSQuery *pp = omnetpp::fromAnyPtr<DNSQuery>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DNSQuery'", field);
    }
}

Register_Class(DNSResponse)

DNSResponse::DNSResponse(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
}

DNSResponse::DNSResponse(const DNSResponse& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

DNSResponse::~DNSResponse()
{
}

DNSResponse& DNSResponse::operator=(const DNSResponse& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void DNSResponse::copy(const DNSResponse& other)
{
    this->hostname = other.hostname;
<<<<<<< HEAD
    this->resolvedAddr = other.resolvedAddr;
    this->destAddr = other.destAddr;
    this->queryId = other.queryId;
=======
    this->ipAddr = other.ipAddr;
>>>>>>> origin/main
}

void DNSResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->hostname);
<<<<<<< HEAD
    doParsimPacking(b,this->resolvedAddr);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->queryId);
=======
    doParsimPacking(b,this->ipAddr);
>>>>>>> origin/main
}

void DNSResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->hostname);
<<<<<<< HEAD
    doParsimUnpacking(b,this->resolvedAddr);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->queryId);
=======
    doParsimUnpacking(b,this->ipAddr);
>>>>>>> origin/main
}

const char * DNSResponse::getHostname() const
{
    return this->hostname.c_str();
}

void DNSResponse::setHostname(const char * hostname)
{
    this->hostname = hostname;
}

<<<<<<< HEAD
int DNSResponse::getResolvedAddr() const
{
    return this->resolvedAddr;
}

void DNSResponse::setResolvedAddr(int resolvedAddr)
{
    this->resolvedAddr = resolvedAddr;
}

int DNSResponse::getDestAddr() const
{
    return this->destAddr;
}

void DNSResponse::setDestAddr(int destAddr)
{
    this->destAddr = destAddr;
}

int DNSResponse::getQueryId() const
{
    return this->queryId;
}

void DNSResponse::setQueryId(int queryId)
{
    this->queryId = queryId;
=======
int DNSResponse::getIpAddr() const
{
    return this->ipAddr;
}

void DNSResponse::setIpAddr(int ipAddr)
{
    this->ipAddr = ipAddr;
>>>>>>> origin/main
}

class DNSResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_hostname,
<<<<<<< HEAD
        FIELD_resolvedAddr,
        FIELD_destAddr,
        FIELD_queryId,
=======
        FIELD_ipAddr,
>>>>>>> origin/main
    };
  public:
    DNSResponseDescriptor();
    virtual ~DNSResponseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(DNSResponseDescriptor)

DNSResponseDescriptor::DNSResponseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(DNSResponse)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

DNSResponseDescriptor::~DNSResponseDescriptor()
{
    delete[] propertyNames;
}

bool DNSResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DNSResponse *>(obj)!=nullptr;
}

const char **DNSResponseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *DNSResponseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int DNSResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
<<<<<<< HEAD
    return base ? 4+base->getFieldCount() : 4;
=======
    return base ? 2+base->getFieldCount() : 2;
>>>>>>> origin/main
}

unsigned int DNSResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_hostname
<<<<<<< HEAD
        FD_ISEDITABLE,    // FIELD_resolvedAddr
        FD_ISEDITABLE,    // FIELD_destAddr
        FD_ISEDITABLE,    // FIELD_queryId
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
=======
        FD_ISEDITABLE,    // FIELD_ipAddr
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
>>>>>>> origin/main
}

const char *DNSResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "hostname",
<<<<<<< HEAD
        "resolvedAddr",
        "destAddr",
        "queryId",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
=======
        "ipAddr",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
>>>>>>> origin/main
}

int DNSResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "hostname") == 0) return baseIndex + 0;
<<<<<<< HEAD
    if (strcmp(fieldName, "resolvedAddr") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "destAddr") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "queryId") == 0) return baseIndex + 3;
=======
    if (strcmp(fieldName, "ipAddr") == 0) return baseIndex + 1;
>>>>>>> origin/main
    return base ? base->findField(fieldName) : -1;
}

const char *DNSResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_hostname
<<<<<<< HEAD
        "int",    // FIELD_resolvedAddr
        "int",    // FIELD_destAddr
        "int",    // FIELD_queryId
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
=======
        "int",    // FIELD_ipAddr
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
>>>>>>> origin/main
}

const char **DNSResponseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *DNSResponseDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int DNSResponseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    DNSResponse *pp = omnetpp::fromAnyPtr<DNSResponse>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void DNSResponseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    DNSResponse *pp = omnetpp::fromAnyPtr<DNSResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'DNSResponse'", field);
    }
}

const char *DNSResponseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    DNSResponse *pp = omnetpp::fromAnyPtr<DNSResponse>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DNSResponseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    DNSResponse *pp = omnetpp::fromAnyPtr<DNSResponse>(object); (void)pp;
    switch (field) {
        case FIELD_hostname: return oppstring2string(pp->getHostname());
<<<<<<< HEAD
        case FIELD_resolvedAddr: return long2string(pp->getResolvedAddr());
        case FIELD_destAddr: return long2string(pp->getDestAddr());
        case FIELD_queryId: return long2string(pp->getQueryId());
=======
        case FIELD_ipAddr: return long2string(pp->getIpAddr());
>>>>>>> origin/main
        default: return "";
    }
}

void DNSResponseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DNSResponse *pp = omnetpp::fromAnyPtr<DNSResponse>(object); (void)pp;
    switch (field) {
        case FIELD_hostname: pp->setHostname((value)); break;
<<<<<<< HEAD
        case FIELD_resolvedAddr: pp->setResolvedAddr(string2long(value)); break;
        case FIELD_destAddr: pp->setDestAddr(string2long(value)); break;
        case FIELD_queryId: pp->setQueryId(string2long(value)); break;
=======
        case FIELD_ipAddr: pp->setIpAddr(string2long(value)); break;
>>>>>>> origin/main
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DNSResponse'", field);
    }
}

omnetpp::cValue DNSResponseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    DNSResponse *pp = omnetpp::fromAnyPtr<DNSResponse>(object); (void)pp;
    switch (field) {
        case FIELD_hostname: return pp->getHostname();
<<<<<<< HEAD
        case FIELD_resolvedAddr: return pp->getResolvedAddr();
        case FIELD_destAddr: return pp->getDestAddr();
        case FIELD_queryId: return pp->getQueryId();
=======
        case FIELD_ipAddr: return pp->getIpAddr();
>>>>>>> origin/main
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'DNSResponse' as cValue -- field index out of range?", field);
    }
}

void DNSResponseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DNSResponse *pp = omnetpp::fromAnyPtr<DNSResponse>(object); (void)pp;
    switch (field) {
        case FIELD_hostname: pp->setHostname(value.stringValue()); break;
<<<<<<< HEAD
        case FIELD_resolvedAddr: pp->setResolvedAddr(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_destAddr: pp->setDestAddr(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_queryId: pp->setQueryId(omnetpp::checked_int_cast<int>(value.intValue())); break;
=======
        case FIELD_ipAddr: pp->setIpAddr(omnetpp::checked_int_cast<int>(value.intValue())); break;
>>>>>>> origin/main
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DNSResponse'", field);
    }
}

const char *DNSResponseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr DNSResponseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    DNSResponse *pp = omnetpp::fromAnyPtr<DNSResponse>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void DNSResponseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    DNSResponse *pp = omnetpp::fromAnyPtr<DNSResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DNSResponse'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

