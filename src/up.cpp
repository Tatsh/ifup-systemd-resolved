#include <QtCore/QCoreApplication>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtNetwork/QNetworkInterface>

#include "up.h"

LinkDnsIpList generateAddresses() {
    LinkDnsIpList dnsArgs;
    for (const auto &ipAddress : QStringList{
             QString(qEnvironmentVariable(Strings::EnvironmentVariableNames::dns1)).trimmed(),
             QString(qEnvironmentVariable(Strings::EnvironmentVariableNames::dns2)).trimmed()}) {
        if (!ipAddress.isEmpty()) {
            const QHostAddress addr(ipAddress);
            auto isIpv4 = false;
            const auto ipv4 = addr.toIPv4Address(&isIpv4);
            LinkDnsIp add;
            if (isIpv4) {
                for (auto shift = 24; shift >= 0; shift -= 8) {
                    add.ipAddress << ((ipv4 >> shift) & 0xFF);
                }
            } else {
                add.family = AF_INET6;
                const auto ipv6 = addr.toIPv6Address();
                for (auto i = 0; i < 16; i++) {
                    add.ipAddress << ipv6[i];
                }
            }
            dnsArgs << add;
        }
    }
    return dnsArgs;
}

LinkDomainList generateDomains() {
    LinkDomainList domainsArg;
    for (const auto &domain :
         QString(qEnvironmentVariable(Strings::EnvironmentVariableNames::dnsSuffix))
             .trimmed()
             .split(Strings::singleSpace, Qt::SkipEmptyParts)) {
        domainsArg << LinkDomain{domain, false};
    }
    return domainsArg;
}
