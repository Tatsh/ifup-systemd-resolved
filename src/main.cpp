#include <QtCore/QCoreApplication>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtNetwork/QNetworkInterface>

#include "constants.h"
#include "ifupdebug.h"
#include "resolve1_interface.h"
#include "specialtypes.h"

namespace EnvVars = Strings::EnvironmentVariables;

static void doSetLinkDns(Resolve1Manager &iface, const int devIndex) {
    LinkDnsIpList dnsArgs;
    auto x = QStringList{EnvVars::dns1, EnvVars::dns2};
    for (const auto &ipAddress : QStringList{EnvVars::dns1, EnvVars::dns2}) {
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
    if (dnsArgs.length()) {
        auto res = iface.SetLinkDNS(devIndex, dnsArgs);
        res.waitForFinished();
        if (res.isError()) {
            qFatal("SetLinkDNS failed");
        }
    }
}

static void doSetLinkDomains(Resolve1Manager &iface, const int devIndex) {
    LinkDomainsList domainsArg;
    for (const auto &domain : EnvVars::dnsSuffix.split(Strings::singleSpace, Qt::SkipEmptyParts)) {
        domainsArg << LinkDomains{domain, false};
    }
    if (domainsArg.length()) {
        auto res = iface.SetLinkDomains(devIndex, domainsArg);
        res.waitForFinished();
        if (res.isError()) {
            qFatal("SetLinkDomains failed");
        }
    }
}

static void doSetLinkDnssec(Resolve1Manager &iface, const int devIndex) {
    if (EnvVars::dnsSec.length()) {
        auto res = iface.SetLinkDNSSEC(
            devIndex,
            EnvVars::dnsSec == Strings::dnsSecDefaultValue ? Strings::empty : EnvVars::dnsSec);
        res.waitForFinished();
        if (res.isError()) {
            qFatal("SetLinkDNSSEC failed");
        }
    }
}

static void up() {
    Resolve1Manager iface(Strings::DBus::Services::resolve1,
                          Strings::DBus::Paths::resolve1,
                          QDBusConnection::systemBus());
    if (EnvVars::netDevice.isEmpty()) {
        qCCritical(LOG_IFUP_SYSTEMD_RESOLVED) << "Empty net device name.";
        return;
    }
    const auto devIndex = QNetworkInterface::interfaceFromName(EnvVars::netDevice).index();
    if (devIndex == 0) {
        qCWarning(LOG_IFUP_SYSTEMD_RESOLVED) << "Unusual to have network device index 0";
    }
    if (iface.isValid()) {
        doSetLinkDns(iface, devIndex);
        doSetLinkDomains(iface, devIndex);
        doSetLinkDnssec(iface, devIndex);
    } else {
        qCCritical(LOG_IFUP_SYSTEMD_RESOLVED) << iface.lastError();
        qFatal("Invalid interface!");
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    qCDebug(LOG_IFUP_SYSTEMD_RESOLVED)
        << QStringLiteral("ifup-systemd-resolved v%1").arg(QString::fromLocal8Bit(VERSION));
    registerDBusTypes();
    if (!QDBusConnection::systemBus().isConnected()) {
        qFatal("Failed to connect to system bus.");
    }
    up();
    return 0;
}
