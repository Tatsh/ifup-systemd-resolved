# ifup-systemd-resolved

This script is primarily for use with [openfortivpn](https://github.com/adrienverge/openfortivpn),
[patched](https://github.com/adrienverge/openfortivpn/pull/615)
([alternative](https://github.com/adrienverge/openfortivpn/pull/986/files))
to allow for hook scripts.

## Usage

In your configuration file for your patched copy of openfortivpn:

```plain
ifup-script = /path/to/ifup-systemd-resolved
```

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
