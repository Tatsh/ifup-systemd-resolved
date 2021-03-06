#include "specialtypes.h"

QDBusArgument &operator<<(QDBusArgument &argument, const LinkDnsIp &ld) {
    argument.beginStructure();
    argument << ld.family << ld.ipAddress;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, LinkDnsIp &ld) {
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
    qDBusRegisterMetaType<LinkDnsIp>();
    qDBusRegisterMetaType<LinkDnsIpList>();
    qDBusRegisterMetaType<LinkDomains>();
    qDBusRegisterMetaType<LinkDomainsList>();
}
