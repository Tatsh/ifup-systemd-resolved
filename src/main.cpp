#include <QtCore/QCoreApplication>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtNetwork/QNetworkInterface>

#include "resolve1_interface.h"
#include "up.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    qCDebug(LOG_IFUP_SYSTEMD_RESOLVED)
        << QStringLiteral("ifup-systemd-resolved v%1").arg(QString::fromLocal8Bit(VERSION));
    registerDBusTypes();
    auto connection = QDBusConnection::systemBus();
    if (!connection.isConnected()) {
        qFatal("Failed to connect to system bus.");
    }
    Resolve1Manager dbus_iface(
        Strings::DBus::Services::resolve1, Strings::DBus::Paths::resolve1, connection);
    return Up(dbus_iface).up() ? EXIT_SUCCESS : EXIT_FAILURE;
}
