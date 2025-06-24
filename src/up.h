/**
 * @file up.h
 * @brief Functions used by `ifup-systemd-resolved` to set DNS and domain information.
 */
#pragma once
#include <QtNetwork/QNetworkInterface>

#include "constants.h"
#include "ifupdebug.h"
#include "resolve1_interface.h"
#include "specialtypes.h"

/**
 * Generate addresses for the call to `org.freedesktop.resolve1` `SetLinkDNS`.
 * Requires environment variables `DNS1` and `DNS2` to be set to valid IP addresses.
 *
 * @return A unique pointer to a LinkDnsIpList containing the addresses.
 */
LinkDnsIpList generateAddresses();
/**
 * Generate domains for the call to `org.freedesktop.resolve1` `SetLinkDomains`.
 * Requires the environment variable `DNS_SUFFIX` to be set to a space-separated list of domain
 * names. Each domain will be added as a LinkDomain object with the second field set to false.
 *
 * @return A unique pointer to a LinkDomainList containing the domains.
 */
LinkDomainList generateDomains();
/**
 * Call `SetLinkDNS`, `SetLinkDomains`, and `SetLinkDNSSEC` on the `Resolve1Manager` interface.
 *
 * The network interface name is retrieved from the environment variable `PPP_IFACE`.
 *
 * @tparam Manager The type of the Resolve1Manager interface.
 * @return true if all calls were successful, false otherwise.
 */
template <class Manager>
class Up {
public:
    /**
     * Constructor for Up.
     *
     * @param dbus_iface The Manager to use for D-Bus calls.
     */
    Up(Manager &dbus_iface) : dbus_iface_(dbus_iface) {
    }
    /**
     * Call `SetLinkDNS`, `SetLinkDomains`, and `SetLinkDNSSEC` on the `Manager` interface.
     *
     * The network interface name is retrieved from the environment variable `PPP_IFACE`.
     *
     * @return true if all calls were successful, false otherwise.
     */
    bool up() {
        const auto devIndex = netDeviceIndex();
        int res = 0;
        if (dbus_iface_.isValid() && devIndex >= 0) {
            doSetLinkDns(devIndex) ? res++ : res;
            doSetLinkDomains(devIndex) ? res++ : res;
            doSetLinkDnssec(devIndex) ? res++ : res;
        } else {
            qCCritical(LOG_IFUP_SYSTEMD_RESOLVED)
                << "Invalid interface!" << dbus_iface_.lastError();
            return false;
        }
        qCCritical(LOG_IFUP_SYSTEMD_RESOLVED)
            << "At least one D-Bus call failed. Expected 3, got" << res << ".";
        return res == 3;
    }
    /**
     * Call `SetLinkDNS` on the `Resolve1Manager` interface passed in.
     *
     * This function retrieves the DNS addresses from environment variables `DNS1` and `DNS2`.
     *
     * This function blocks until the response from D-Bus is received.
     *
     * @tparam Manager The type of the Resolve1Manager interface.
     * @param devIndex The index of the network device.
     * @return true if the call was successful, false otherwise.
     *
     * @see generateAddresses()
     */
    virtual bool doSetLinkDns(const int devIndex) {
        auto dnsArgs = generateAddresses();
        if (!dnsArgs.isEmpty()) {
            auto res = dbus_iface_.SetLinkDNS(devIndex, dnsArgs);
            res.waitForFinished();
            if (res.isError()) {
                qCCritical(LOG_IFUP_SYSTEMD_RESOLVED) << "SetLinkDNS failed.";
                return false;
            }
        }
        return true;
    }
    /**
     * Call `SetLinkDomains` on the `Resolve1Manager` interface passed in.
     *
     * This function retrieves the domains from the environment variable `DNS_SUFFIX`
     * (space-separated list).
     *
     * This function blocks until the response from D-Bus is received.
     *
     * @tparam Manager The type of the Resolve1Manager interface.
     * @param devIndex The index of the network device.
     * @return true if the call was successful, false otherwise.
     *
     * @see generateDomains()
     */
    virtual bool doSetLinkDomains(const int devIndex) {
        auto domainsArg = generateDomains();
        if (!domainsArg.isEmpty()) {
            auto res = dbus_iface_.SetLinkDomains(devIndex, domainsArg);
            res.waitForFinished();
            if (res.isError()) {
                qCCritical(LOG_IFUP_SYSTEMD_RESOLVED) << "SetLinkDomains failed.";
                return false;
            }
        }
        return true;
    }
    /**
     * Call `SetLinkDNSSEC` on the `Resolve1Manager` interface passed in.
     *
     * This function retrieves the DNSSEC value from the environment variable `DNSSEC`. If the value
     * is `default`, empty string is passed to D-Bus.
     *
     * This function blocks until the response from D-Bus is received.
     *
     * @tparam Manager The type of the Resolve1Manager interface.
     * @param devIndex The index of the network device.
     * @return true if the call was successful, false otherwise.
     */
    virtual bool doSetLinkDnssec(const int devIndex) {
        auto dnsSec =
            QString(qEnvironmentVariable(Strings::EnvironmentVariableNames::dnsSec)).trimmed();
        if (!dnsSec.isEmpty()) {
            auto res = dbus_iface_.SetLinkDNSSEC(
                devIndex, dnsSec == Strings::dnsSecDefaultValue ? Strings::empty : dnsSec);
            res.waitForFinished();
            if (res.isError()) {
                qCCritical(LOG_IFUP_SYSTEMD_RESOLVED) << "SetLinkDNSSEC failed.";
                return false;
            }
        }
        return true;
    }

private:
    int netDeviceIndex() const {
        const auto netDevEnvValue =
            QString(qEnvironmentVariable(Strings::EnvironmentVariableNames::netDevice)).trimmed();
        if (netDevEnvValue.isEmpty()) {
            qCCritical(LOG_IFUP_SYSTEMD_RESOLVED) << "Empty network device name.";
            return -1;
        }
        const auto iface = QNetworkInterface::interfaceFromName(netDevEnvValue);
        if (!iface.isValid()) {
            // LCOV_EXCL_START
            qCCritical(LOG_IFUP_SYSTEMD_RESOLVED)
                << "Invalid network device name:" << netDevEnvValue;
            return -1;
            // LCOV_EXCL_STOP
        }
        const auto devIndex = iface.index();
        if (devIndex == 0) {
            // LCOV_EXCL_START
            qCWarning(LOG_IFUP_SYSTEMD_RESOLVED) << "Unusual to have network device index 0.";
            // LCOV_EXCL_STOP
        }
        return devIndex;
    }

    Manager &dbus_iface_;
};
