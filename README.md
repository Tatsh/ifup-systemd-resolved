# ifup-systemd-resolved

This tool is primarily for use with [openfortivpn](https://github.com/adrienverge/openfortivpn),
[patched](https://github.com/adrienverge/openfortivpn/pull/615)
([alternative](https://github.com/adrienverge/openfortivpn/pull/986/files))
to allow for hook scripts. It uses D-Bus to set up DNS settings for the PPP interface. It is based
on the script in
[adrienverge/openfortivpn#615](https://github.com/adrienverge/openfortivpn/pull/615).

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

```shell
git clone ...
mkdir the-repo-dir/build
cd the-repo-dir/build
cmake ..
make
```
