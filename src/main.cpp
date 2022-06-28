#include <QtCore/QCoreApplication>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtNetwork/QNetworkInterface>

#include "constants.h"
#include "ifupdebug.h"
#include "resolve1_interface.h"
#include "specialtypes.h"

static void up() {
    Resolve1Manager iface(Strings::DBus::Services::resolve1,
                          Strings::DBus::Paths::resolve1,
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
            auto res = iface.SetLinkDNS(devIndex, dnsArgs);
            res.waitForFinished();
            if (res.isError()) {
                qFatal("SetLinkDNS failed");
            }
        }
        LinkDomainsList domainsArg;
        for (auto domain : Strings::EnvironmentVariables::dnsSuffix.split(Strings::singleSpace,
                                                                          Qt::SkipEmptyParts)) {
            LinkDomains add{domain, false};
            domainsArg << add;
        }
        if (domainsArg.length() > 0) {
            auto res = iface.SetLinkDomains(devIndex, domainsArg);
            res.waitForFinished();
            if (res.isError()) {
                qFatal("SetLinkDomains failed");
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
