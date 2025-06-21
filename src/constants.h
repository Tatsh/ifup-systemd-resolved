/**
 * @file constants.h
 * @brief Constants.
 */
#pragma once
#include <QtCore/QStringLiteral>

namespace Strings {
    /** Empty string. */
    const QString empty = QStringLiteral("");
    /** Single ASCII period. */
    const QString period = QStringLiteral(".");
    /** Single ASCII space. */
    const QString singleSpace = QStringLiteral(" ");
#pragma region DNSSEC
    /** DNSSEC environment variable value for default. */
    const QString dnsSecDefaultValue = QStringLiteral("default");
#pragma endregion
    namespace DBus {
        namespace Services {
            /** D-Bus service name for Resolve1. */
            const QString resolve1 = QStringLiteral("org.freedesktop.resolve1");
        } // namespace Services
        namespace Paths {
            /** D-Bus path for Resolve1. */
            const QString resolve1 = QStringLiteral("/org/freedesktop/resolve1");
        } // namespace Paths
    } // namespace DBus
    namespace EnvironmentVariables {
        /** Environment variable for DNSSEC value. */
        const QString dnsSec = QString(qEnvironmentVariable("DNSSEC")).trimmed();
        /** Environment variable for first DNS entry. */
        const QString dns1 = QString(qEnvironmentVariable("DNS1")).trimmed();
        /** Environment variable for second DNS entry. */
        const QString dns2 = QString(qEnvironmentVariable("DNS2")).trimmed();
        /** Environment variable for space-separated list of DNS suffixes. */
        const QString dnsSuffix = QString(qEnvironmentVariable("DNS_SUFFIX")).trimmed();
        /** Environment variable for network device name. */
        const QString netDevice = QString(qEnvironmentVariable("PPP_IFACE")).trimmed();
    } // namespace EnvironmentVariables
} // namespace Strings
