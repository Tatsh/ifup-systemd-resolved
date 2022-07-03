#include <QtCore/QCoreApplication>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtNetwork/QNetworkInterface>

#include "constants.h"
#include "ifupdebug.h"
#include "resolve1_interface.h"
#include "specialtypes.h"

namespace EnvVars = Strings::EnvironmentVariables;

static void up() {
    Resolve1Manager iface(Strings::DBus::Services::resolve1,
                          Strings::DBus::Paths::resolve1,
                          QDBusConnection::systemBus());
    if (iface.isValid()) {
        const auto devIndex = QNetworkInterface::interfaceFromName(EnvVars::netDevice).index();
        LinkDnsIpList dnsArgs;
        for (auto ipAddress : EnvVars::dnsServers.split(Strings::singleSpace, Qt::SkipEmptyParts)) {
            const QHostAddress addr(ipAddress);
            bool isIpv4 = false;
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
        if (dnsArgs.length()) {
            auto res = iface.SetLinkDNS(devIndex, dnsArgs);
            res.waitForFinished();
            if (res.isError()) {
                qFatal("SetLinkDNS failed");
            }
        }
        LinkDomainsList domainsArg;
        for (auto domain : EnvVars::dnsSuffix.split(Strings::singleSpace, Qt::SkipEmptyParts)) {
            LinkDomains add{domain, false};
            domainsArg << add;
        }
        if (domainsArg.length()) {
            auto res = iface.SetLinkDomains(devIndex, domainsArg);
            res.waitForFinished();
            if (res.isError()) {
                qFatal("SetLinkDomains failed");
            }
        }
        if (EnvVars::dnsSec.length()) {
            auto res = iface.SetLinkDNSSEC(
                devIndex,
                EnvVars::dnsSec == Strings::dnsSecDefaultValue ? Strings::empty : EnvVars::dnsSec);
            res.waitForFinished();
            if (res.isError()) {
                qFatal("SetLinkDNSSEC failed");
            }
        }
    } else {
        qFatal("Invalid interface!");
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    registerDBusTypes();
    if (!QDBusConnection::systemBus().isConnected()) {
        qFatal("Failed to connect to system bus.");
    }
    up();
    return 0;
}
