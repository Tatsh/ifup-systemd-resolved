# ifup-systemd-resolved

<!-- WISWA-GENERATED-README:START -->

[![C++](https://img.shields.io/badge/C++-00599C?logo=c%2B%2B)](https://isocpp.org)
[![GitHub tag (with filter)](https://img.shields.io/github/v/tag/Tatsh/ifup-systemd-resolved)](https://github.com/Tatsh/ifup-systemd-resolved/tags)
[![License](https://img.shields.io/github/license/Tatsh/ifup-systemd-resolved)](https://github.com/Tatsh/ifup-systemd-resolved/blob/master/LICENSE.txt)
[![GitHub commits since latest release (by SemVer including pre-releases)](https://img.shields.io/github/commits-since/Tatsh/ifup-systemd-resolved/v0.0.3/master)](https://github.com/Tatsh/ifup-systemd-resolved/compare/v0.0.3...master)
[![Dependabot](https://img.shields.io/badge/Dependabot-enabled-blue?logo=dependabot)](https://github.com/dependabot)
[![GitHub Pages](https://github.com/Tatsh/ifup-systemd-resolved/actions/workflows/pages.yml/badge.svg)](https://tatsh.github.io/ifup-systemd-resolved/)
[![Stargazers](https://img.shields.io/github/stars/Tatsh/ifup-systemd-resolved?logo=github&style=flat)](https://github.com/Tatsh/ifup-systemd-resolved/stargazers)
[![pre-commit](https://img.shields.io/badge/pre--commit-enabled-brightgreen?logo=pre-commit)](https://github.com/pre-commit/pre-commit)
[![CMake](https://img.shields.io/badge/CMake-6E6E6E?logo=cmake)](https://cmake.org/)
[![Prettier](https://img.shields.io/badge/Prettier-black?logo=prettier)](https://prettier.io/)

[![@Tatsh](https://img.shields.io/badge/dynamic/json?url=https%3A%2F%2Fpublic.api.bsky.app%2Fxrpc%2Fapp.bsky.actor.getProfile%2F%3Factor=did%3Aplc%3Auq42idtvuccnmtl57nsucz72&query=%24.followersCount&label=Follow+%40Tatsh&logo=bluesky&style=social)](https://bsky.app/profile/Tatsh.bsky.social)
[![Buy Me A Coffee](https://img.shields.io/badge/Buy%20Me%20a%20Coffee-Tatsh-black?logo=buymeacoffee)](https://buymeacoffee.com/Tatsh)
[![Libera.Chat](https://img.shields.io/badge/Libera.Chat-Tatsh-black?logo=liberadotchat)](irc://irc.libera.chat/Tatsh)
[![Mastodon Follow](https://img.shields.io/mastodon/follow/109370961877277568?domain=hostux.social&style=social)](https://hostux.social/@Tatsh)
[![Patreon](https://img.shields.io/badge/Patreon-Tatsh2-F96854?logo=patreon)](https://www.patreon.com/Tatsh2)

<!-- WISWA-GENERATED-README:STOP -->

This tool is primarily for use with [openfortivpn](https://github.com/adrienverge/openfortivpn),
[patched](https://github.com/adrienverge/openfortivpn/pull/1092)
([alternative](https://github.com/adrienverge/openfortivpn/pull/986/files))
to allow for hook scripts. It uses D-Bus to set up DNS settings for the PPP interface. It is based
on the script in
[adrienverge/openfortivpn#1092](https://github.com/adrienverge/openfortivpn/pull/1092).

## Usage

In your configuration file for your patched copy of openfortivpn:

```plain
ifup-script = /path/to/ifup-systemd-resolved
```

### General usage

Environment variables must be set for this application to do anything.

| Name          | Description                                                                               |
| ------------- | ----------------------------------------------------------------------------------------- |
| `DNS_SERVERS` | DNS server IPs and names. Both IPv4 and IPv6 are supported.                               |
| `DNS_SUFFIX`  | Search domains.                                                                           |
| `DNSSEC`      | If non-empty, it should be `default`, `yes`, `no`, or `allow-downgrade`.                  |
| `PPP_IFACE`   | Name of the device (see `ifconfig` or similar). Usually this something similar to `ppp0`. |

These are usually set by openfortivpn calling the script.

## How to build

You must have Qt development libraries and
[Extra CMake Modules](https://invent.kde.org/frameworks/extra-cmake-modules) installed.

```shell
git clone ...
mkdir the-repo-dir/build
cd the-repo-dir/build
cmake ..
make
```

## How to build with vcpkg

1. Have vcpkg configured. See [Set up vcpkg](https://learn.microsoft.com/en-gb/vcpkg/get_started/get-started?pivots=shell-bash#1---set-up-vcpkg).
2. Clone the project.
3. In the project directory, run `cmake --preset=default && cmake --build build`.
