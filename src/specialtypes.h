#pragma once
#include <sys/socket.h>

#include <QtDBus/QDBusMetaType>

/** @struct LinkDnsIp */
struct LinkDnsIp {
    /** Valid values: AF_INET, AF_INET6. */
    int family = AF_INET;
    /** IP address. */
    QList<uchar> ipAddress;
};
Q_DECLARE_METATYPE(LinkDnsIp)
/** List of LinkDnsIp. */
typedef QList<LinkDnsIp> LinkDnsIpList;
Q_DECLARE_METATYPE(LinkDnsIpList)

/** @struct LinkDomain */
struct LinkDomain {
    /** Domain name. */
    QString domain;
    /** This field is always set to `false`. */
    bool b;
};
Q_DECLARE_METATYPE(LinkDomain)
/** List of LinkDomain. */
typedef QList<LinkDomain> LinkDomainList;
Q_DECLARE_METATYPE(LinkDomainList)

/** Register custom types with DBus. */
void registerDBusTypes();
