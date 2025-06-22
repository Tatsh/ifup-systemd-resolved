/**
 * @file constants.h
 * @brief Constants.
 */
#pragma once
#include <QtCore/QString>

/** Common strings. */
namespace Strings {
    /** Empty string. */
    const QString empty = QStringLiteral("");
    /** Single ASCII period. */
    const QString period = QStringLiteral(".");
    /** Single ASCII space. */
    const QString singleSpace = QStringLiteral(" ");
    /** DNSSEC environment variable value for default. */
    const QString dnsSecDefaultValue = QStringLiteral("default");
    /** D-Bus strings. */
    namespace DBus {
        /** D-Bus service names. */
        namespace Services {
            /** D-Bus service name for Resolve1. */
            const QString resolve1 = QStringLiteral("org.freedesktop.resolve1");
        } // namespace Services
        /** D-Bus paths. */
        namespace Paths {
            /** D-Bus path for Resolve1. */
            const QString resolve1 = QStringLiteral("/org/freedesktop/resolve1");
        } // namespace Paths
    } // namespace DBus
    /** Environment variable names. */
    namespace EnvironmentVariableNames {
        /** Environment variable name for DNSSEC. */
        inline const char *dnsSec = "DNSSEC";
        /** Environment variable name for first DNS entry. */
        inline const char *dns1 = "DNS1";
        /** Environment variable name for second DNS entry. */
        inline const char *dns2 = "DNS2";
        /** Environment variable name for DNS suffixes. */
        inline const char *dnsSuffix = "DNS_SUFFIX";
        /** Environment variable name for network device name. */
        inline const char *netDevice = "PPP_IFACE";
    } // namespace EnvironmentVariableNames
} // namespace Strings
