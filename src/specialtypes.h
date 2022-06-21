#include <QtDBus/QDBusMetaType>

struct LinkDNSIPv4 {
    int family;
    QList<uchar> ipAddress;
};
Q_DECLARE_METATYPE(LinkDNSIPv4)
typedef QList<LinkDNSIPv4> LinkDNSIPv4List;
Q_DECLARE_METATYPE(LinkDNSIPv4List)

struct LinkDomains {
    QString domain;
    bool b;
};
Q_DECLARE_METATYPE(LinkDomains)
typedef QList<LinkDomains> LinkDomainsList;
Q_DECLARE_METATYPE(LinkDomainsList)

void registerDBusTypes();
