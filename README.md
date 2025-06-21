# ifup-systemd-resolved

[![Build](https://github.com/Tatsh/ifup-systemd-resolved/actions/workflows/cmake.yml/badge.svg)](https://github.com/Tatsh/ifup-systemd-resolved/actions/workflows/cmake.yml)
[![Tests](https://github.com/Tatsh/ifup-systemd-resolved/actions/workflows/tests.yml/badge.svg)](https://github.com/Tatsh/ifup-systemd-resolved/actions/workflows/tests.yml)
[![Coverage Status](https://coveralls.io/repos/github/Tatsh/ifup-systemd-resolved/badge.svg?branch=master)](https://coveralls.io/github/Tatsh/ifup-systemd-resolved?branch=master)
[![Documentation](https://img.shields.io/badge/docs-deployed-blue)](https://tatsh.github.io/ifup-systemd-resolved/)
[![QA](https://github.com/Tatsh/ifup-systemd-resolved/actions/workflows/qa.yml/badge.svg)](https://github.com/Tatsh/ifup-systemd-resolved/actions/workflows/qa.yml)
[![pre-commit](https://img.shields.io/badge/pre--commit-enabled-brightgreen?logo=pre-commit&logoColor=white)](https://github.com/pre-commit/pre-commit)
[![CodeQL](https://github.com/Tatsh/ifup-systemd-resolved/actions/workflows/codeql.yml/badge.svg)](https://github.com/Tatsh/ifup-systemd-resolved/actions/workflows/codeql.yml)
[![License](https://img.shields.io/github/license/Tatsh/ifup-systemd-resolved)](https://github.com/Tatsh/ifup-systemd-resolved/blob/master/LICENSE.txt)
![GitHub tag (with filter)](https://img.shields.io/github/v/tag/Tatsh/ifup-systemd-resolved)
![GitHub](https://img.shields.io/github/license/Tatsh/ifup-systemd-resolved)
![GitHub commits since latest release (by SemVer including pre-releases)](https://img.shields.io/github/commits-since/Tatsh/ifup-systemd-resolved/v0.0.1/master)
[![Stargazers](https://img.shields.io/github/stars/Tatsh/ifup-systemd-resolved?logo=github&style=flat)](https://github.com/Tatsh/ifup-systemd-resolved/stargazers)

[![@Tatsh](https://img.shields.io/badge/dynamic/json?url=https%3A%2F%2Fpublic.api.bsky.app%2Fxrpc%2Fapp.bsky.actor.getProfile%2F%3Factor%3Ddid%3Aplc%3Auq42idtvuccnmtl57nsucz72%26query%3D%24.followersCount%26style%3Dsocial%26logo%3Dbluesky%26label%3DFollow%2520%40Tatsh&query=%24.followersCount&style=social&logo=bluesky&label=Follow%20%40Tatsh)](https://bsky.app/profile/Tatsh.bsky.social)
[![Mastodon Follow](https://img.shields.io/mastodon/follow/109370961877277568?domain=hostux.social&style=social)](https://hostux.social/@Tatsh)

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
| `NET_DEVICE`  | Name of the device (see `ifconfig` or similar). Usually this something similar to `ppp0`. |

## How to build

You must have Qt development libraries and
[Extra CMake Modules](https://invent.kde.org/frameworks/extra-cmake-modules)
installed.

### vcpkg

1. Have vcpkg configured. See [Set up vcpkg](https://learn.microsoft.com/en-gb/vcpkg/get_started/get-started?pivots=shell-bash#1---set-up-vcpkg).
2. Clone the project.
3. In the project directory, run `cmake --preset=default && cmake --build build`

### Link against system dependencies

```shell
git clone ...
mkdir the-repo-dir/build
cd the-repo-dir/build
cmake ..
make
```
