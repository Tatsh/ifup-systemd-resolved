#include "specialtypes.h"

QDBusArgument &operator<<(QDBusArgument &argument, const LinkDNSIPv4 &ld) {
    argument.beginStructure();
    argument << ld.family << ld.ipAddress;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, LinkDNSIPv4 &ld) {
    argument.beginStructure();
    argument >> ld.family >> ld.ipAddress;
    argument.endStructure();
    return argument;
}

QDBusArgument &operator<<(QDBusArgument &argument, const LinkDomains &ld) {
    argument.beginStructure();
    argument << ld.domain << ld.b;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, LinkDomains &ld) {
    argument.beginStructure();
    argument >> ld.domain >> ld.b;
    argument.endStructure();
    return argument;
}

void registerDBusTypes() {
    qDBusRegisterMetaType<LinkDNSIPv4>();
    qDBusRegisterMetaType<LinkDNSIPv4List>();
    qDBusRegisterMetaType<LinkDomains>();
    qDBusRegisterMetaType<LinkDomainsList>();
}
