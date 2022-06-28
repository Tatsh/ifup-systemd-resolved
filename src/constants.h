#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QtCore/QString>

namespace Strings {
    const QString period = QStringLiteral(".");
    const QString singleSpace = QStringLiteral(" ");
    namespace DBus {
        namespace Services {
            const QString resolve1 = QStringLiteral("org.freedesktop.resolve1");
        }
        namespace Paths {
            const QString resolve1 = QStringLiteral("/org/freedesktop/resolve1");
        }
    }         // namespace DBus
    namespace EnvironmentVariables {
        const QString dnsServers = QString(qEnvironmentVariable("DNS_SERVERS")).trimmed();
        const QString dnsSuffix = QString(qEnvironmentVariable("DNS_SUFFIX")).trimmed();
        const QString netDevice = QString(qEnvironmentVariable("NET_DEVICE")).trimmed();
    } // namespace EnvironmentVariables
} // namespace Strings

#endif // CONSTANTS_H
