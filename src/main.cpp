#include <QtCore/QCoreApplication>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtNetwork/QNetworkInterface>

#include "ifupdebug.h"
#include "specialtypes.h"
#include "up.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    qCDebug(LOG_IFUP_SYSTEMD_RESOLVED)
        << QStringLiteral("ifup-systemd-resolved v%1").arg(QString::fromLocal8Bit(VERSION));
    registerDBusTypes();
    if (!QDBusConnection::systemBus().isConnected()) {
        qFatal("Failed to connect to system bus.");
    }
    return up() ? 0 : 1;
}
