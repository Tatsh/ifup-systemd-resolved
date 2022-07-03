#ifndef SPECIALTYPES_H
#define SPECIALTYPES_H

#include <sys/socket.h>

#include <QtDBus/QDBusMetaType>

struct LinkDnsIp {
    int family = AF_INET;
    QList<uchar> ipAddress;
};
Q_DECLARE_METATYPE(LinkDnsIp)
typedef QList<LinkDnsIp> LinkDnsIpList;
Q_DECLARE_METATYPE(LinkDnsIpList)

struct LinkDomains {
    QString domain;
    bool b;
};
Q_DECLARE_METATYPE(LinkDomains)
typedef QList<LinkDomains> LinkDomainsList;
Q_DECLARE_METATYPE(LinkDomainsList)

void registerDBusTypes();

#endif // SPECIALTYPES_H
