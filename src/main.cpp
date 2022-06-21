#include <QtCore/QCoreApplication>
#include <QtDBus/QDBusArgument>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusMetaType>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>

#include "ifupdebug.h"
#include "specialtypes.h"

static void up() {
    auto iface = QDBusInterface(QStringLiteral("org.freedesktop.resolve1"),
                                QStringLiteral("/org/freedesktop/resolve1"),
                                QStringLiteral("org.freedesktop.resolve1.Manager"),
                                QDBusConnection::systemBus());
    if (iface.isValid()) {
        const auto devIndex = QNetworkInterface::interfaceFromName(
                                  QString(qEnvironmentVariable("NET_DEVICE")).trimmed())
                                  .index();
        LinkDNSIPv4List dnsArgs;
        for (auto ipAddress : QString(qEnvironmentVariable("DNS_SERVERS"))
                                  .trimmed()
                                  .split(QStringLiteral(" "), Qt::SkipEmptyParts)) {
            LinkDNSIPv4 add;
            add.family = 2;
            for (auto val : ipAddress.split(QStringLiteral("."), Qt::SkipEmptyParts)) {
                add.ipAddress << val.toUInt();
            }
            dnsArgs << add;
        }
        if (dnsArgs.length() > 0) {
            qCDebug(LOG_IFUP_SYSTEMD_RESOLVED)
                << iface.call(QStringLiteral("SetLinkDNS"), devIndex, QVariant::fromValue(dnsArgs));
        }
        LinkDomainsList domainsArg;
        for (auto domain : QString(qEnvironmentVariable("DNS_SUFFIX"))
                               .trimmed()
                               .split(QStringLiteral(" "), Qt::SkipEmptyParts)) {
            LinkDomains add{domain, false};
            domainsArg << add;
        }
        if (domainsArg.length() > 0) {
            qCDebug(LOG_IFUP_SYSTEMD_RESOLVED) << iface.call(
                QStringLiteral("SetLinkDomains"), devIndex, QVariant::fromValue(domainsArg));
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
