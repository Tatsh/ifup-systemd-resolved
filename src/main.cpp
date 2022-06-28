#include <QtCore/QCoreApplication>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtNetwork/QNetworkInterface>

#include "constants.h"
#include "ifupdebug.h"
#include "specialtypes.h"

static void up() {
    auto iface = QDBusInterface(Strings::DBus::Services::resolve1,
                                Strings::DBus::Paths::resolve1,
                                Strings::DBus::Interfaces::resolve1Manager,
                                QDBusConnection::systemBus());
    if (iface.isValid()) {
        const auto devIndex =
            QNetworkInterface::interfaceFromName(Strings::EnvironmentVariables::netDevice).index();
        LinkDNSIPv4List dnsArgs;
        for (auto ipAddress : Strings::EnvironmentVariables::dnsServers.split(Strings::singleSpace,
                                                                              Qt::SkipEmptyParts)) {
            LinkDNSIPv4 add;
            add.family = 2;
            for (auto val : ipAddress.split(Strings::period, Qt::SkipEmptyParts)) {
                add.ipAddress << val.toUInt();
            }
            dnsArgs << add;
        }
        if (dnsArgs.length() > 0) {
            qCDebug(LOG_IFUP_SYSTEMD_RESOLVED)
                << iface.call(Strings::DBus::Resolve1::Methods::setLinkDNS,
                              devIndex,
                              QVariant::fromValue(dnsArgs));
        }
        LinkDomainsList domainsArg;
        for (auto domain : Strings::EnvironmentVariables::dnsSuffix.split(Strings::singleSpace,
                                                                          Qt::SkipEmptyParts)) {
            LinkDomains add{domain, false};
            domainsArg << add;
        }
        if (domainsArg.length() > 0) {
            qCDebug(LOG_IFUP_SYSTEMD_RESOLVED)
                << iface.call(Strings::DBus::Resolve1::Methods::setLinkDomains,
                              devIndex,
                              QVariant::fromValue(domainsArg));
        }
    } else {
        qCCritical(LOG_IFUP_SYSTEMD_RESOLVED) << "Invalid interface!";
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    registerDBusTypes();
    if (!QDBusConnection::systemBus().isConnected()) {
        qCCritical(LOG_IFUP_SYSTEMD_RESOLVED) << "Failed to connect to system bus.";
        return 1;
    }
    up();
    return 0;
}
