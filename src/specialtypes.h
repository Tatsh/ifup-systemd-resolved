/**
 * @file specialtypes.h
 * @brief Metatypes for D-Bus communication.
 */
#pragma once
#include <sys/socket.h>

#include <QtDBus/QDBusMetaType>

/** Used to call `org.freedesktop.resolve1` `SetLinkDNS`. */
struct LinkDnsIp {
    /** Valid values: `AF_INET`, `AF_INET6`. */
    int family = AF_INET;
    /** IP address. */
    QList<uchar> ipAddress;
};
Q_DECLARE_METATYPE(LinkDnsIp)
/** List of LinkDnsIp. */
typedef QList<LinkDnsIp> LinkDnsIpList;
Q_DECLARE_METATYPE(LinkDnsIpList)

/** Used to call `org.freedesktop.resolve1` `SetLinkDomains`. */
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

/** Register custom types with DBus. This function must be called before using the Up class. */
void registerDBusTypes();
