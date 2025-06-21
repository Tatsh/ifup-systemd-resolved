/**
 * @file up.h
 * @brief Functions used by `ifup-systemd-resolved` to set DNS and domain information.
 */
#pragma once
#include "specialtypes.h"

class Resolve1Manager;

/**
 * Generate addresses for the call to `org.freedesktop.resolve1` `SetLinkDNS`.
 * Requires environment variables `DNS1` and `DNS2` to be set to valid IP addresses.
 *
 * @return A unique pointer to a LinkDnsIpList containing the addresses.
 */
std::unique_ptr<LinkDnsIpList> generateAddresses();
/**
 * Generate domains for the call to `org.freedesktop.resolve1` `SetLinkDomains`.
 * Requires the environment variable `DNS_SUFFIX` to be set to a space-separated list of domain
 * names. Each domain will be added as a LinkDomain object with the second field set to false.
 *
 * @return A unique pointer to a LinkDomainList containing the domains.
 */
std::unique_ptr<LinkDomainList> generateDomains();
/**
 * Call `SetLinkDNS` on the `Resolve1Manager` interface passed in.
 *
 * This function retrieves the DNS addresses from environment variables `DNS1` and `DNS2`.
 *
 * This function blocks until the response from D-Bus is received.
 *
 * @param iface The Resolve1Manager interface.
 * @param devIndex The index of the network device.
 * @return true if the call was successful, false otherwise.
 *
 * @see generateAddresses()
 */
bool doSetLinkDns(Resolve1Manager &iface, const int devIndex);
/**
 * Call `SetLinkDomains` on the `Resolve1Manager` interface passed in.
 *
 * This function retrieves the domains from the environment variable `DNS_SUFFIX` (space-separated
 * list).
 *
 * This function blocks until the response from D-Bus is received.
 *
 * @param iface The Resolve1Manager interface.
 * @param devIndex The index of the network device.
 * @return true if the call was successful, false otherwise.
 *
 * @see generateDomains()
 */
bool doSetLinkDomains(Resolve1Manager &iface, const int devIndex);
/**
 * Call `SetLinkDNSSEC` on the `Resolve1Manager` interface passed in.
 *
 * This function retrieves the DNSSEC value from the environment variable `DNSSEC`. If the value is
 * `default`, empty string is passed to D-Bus.
 *
 * This function blocks until the response from D-Bus is received.
 *
 * @param iface    The Resolve1Manager interface.
 * @param devIndex The index of the network device.
 * @return true if the call was successful, false otherwise.
 */
bool doSetLinkDnssec(Resolve1Manager &iface, const int devIndex);
/**
 * Call `SetLinkDNS`, `SetLinkDomains`, and `SetLinkDNSSEC` on the `Resolve1Manager` interface.
 *
 * The network interface name is retrieved from the environment variable `PPP_IFACE`.
 *
 * @return true if all calls were successful, false otherwise.
 */
bool up();
