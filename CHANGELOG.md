<!-- markdownlint-configure-file {"MD024": { "siblings_only": true } } -->

# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.1/), and this project
adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.0.3] - 2026-05-04

### Changed

- Overhaul the GitHub Actions workflow set, scoped to a Linux-only build: rewrite `cmake.yml` as
  a multi-architecture Build matrix using `install-qt-action` and AppImage bundling, switch test
  coverage to `lcov` with the Coveralls action, install Qt via `install-qt-action` in the CodeQL
  and Pages workflows, and add a `release.yml` that gates GitHub release publication on the
  relevant workflows.
- Add a CPack block to `CMakeLists.txt` that includes the system architecture in package file
  names so x86_64 and aarch64 artefacts built from the same matrix no longer collide.
- Add `_config.yml` so Jekyll excludes `CHANGELOG.md` when GitHub Pages serves the repository
  root.
- Bump development dependencies: `cspell`, `prettier`, `prettier-plugin-sort-json`,
  `markdownlint-cli2`, `pyright`, and `@prettier/plugin-xml`.
- Bump GitHub Actions: `actions/checkout`, `actions/configure-pages`, `actions/deploy-pages`,
  `actions/upload-artifact`, `actions/upload-pages-artifact`, `actions/attest-build-provenance`,
  `github/codeql-action`, and `softprops/action-gh-release`.
- Bump runtime and transitive dependencies: `js-yaml`, `lodash-es`, `flatted`, and `picomatch`.

### Fixed

- Adjust the `CMakeLists.txt` rules for documentation and man page installation.

## [0.0.1]

First release.

[unreleased]: https://github.com/Tatsh/ifup-systemd-resolved/compare/v0.0.3...HEAD
[0.0.3]: https://github.com/Tatsh/ifup-systemd-resolved/compare/v0.0.2...v0.0.3
[0.0.1]: https://github.com/Tatsh/ifup-systemd-resolved/releases/tag/v0.0.1
