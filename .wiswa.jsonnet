local utils = import 'utils.libjsonnet';

{
  uses_user_defaults: true,
  project_name: 'ifup-systemd-resolved',
  version: '0.0.3',
  description: 'Hook for openfortivpn to set up DNS with systemd-resolved.',
  custom_project_badges: [
    {
      anchor: '[![Tests](https://github.com/Tatsh/ifup-systemd-resolved/actions/workflows/tests.yml/badge.svg)]',
      href: 'https://github.com/Tatsh/ifup-systemd-resolved/actions/workflows/tests.yml',
    },
    {
      anchor: '[![Coverage Status](https://coveralls.io/repos/github/Tatsh/ifup-systemd-resolved/badge.svg?branch=master)]',
      href: 'https://coveralls.io/github/Tatsh/ifup-systemd-resolved?branch=master',
    },
  ],
  keywords: ['openconnect', 'systemd', 'vpn'],
  want_main: false,
  want_codeql: false,
  want_tests: false,
  want_winget: false,
  package_json+: {
    cspell+: {
      ignorePaths+: ['*.tags'],
    },
  },
  prettierignore+: ['*.tags'],
  cz+: {
    commitizen+: {
      version_files+: [
        'man/ifup-systemd-resolved.1',
      ],
    },
  },
  github+: {
    pages_using_jekyll: false,
    zizmor: {
      rules: {
        // The hand-maintained release.yml consumes workflow_run to gate the draft release on the
        // build and QA workflows.
        'dangerous-triggers': {
          ignore: ['release.yml'],
        },
      },
    },
  },
  vscode+: {
    c_cpp+: {
      configurations: [
        {
          cStandard: 'gnu23',
          compilerPath: '/usr/bin/gcc',
          cppStandard: 'gnu++23',
          defines: [
            'QT_NO_CAST_FROM_ASCII',
            'QT_NO_CAST_FROM_BYTEARRAY',
            'QT_NO_CAST_TO_ASCII',
            'QT_NO_SIGNALS_SLOTS_KEYWORDS',
            'QT_NO_URL_CAST_FROM_STRING',
            'QT_STRICT_ITERATORS',
            'QT_USE_FAST_OPERATOR_PLUS',
            'QT_USE_QSTRINGBUILDER',
            'VERSION="unknown"',
          ],
          includePath: [
            '${workspaceFolder}/src/**',
            '${workspaceFolder}/build/generated',
            '/usr/include/KF6/KAuthCore',
            '/usr/include/KF6/KCoreAddons',
            '/usr/include/qt6',
          ],
          name: 'Linux',
        },
      ],
    },
    launch+: {
      configurations: [
        {
          cwd: '${workspaceFolder}/build',
          name: 'Debug',
          program: '${workspaceFolder}/build/src/ifup-systemd-resolved',
          request: 'launch',
          type: 'cppdbg',
        },
        {
          cwd: '${workspaceFolder}/build',
          name: 'Debug tests',
          program: '${workspaceFolder}/build/src/ifup-systemd-resolved-tests',
          request: 'launch',
          type: 'cppdbg',
        },
      ],
    },
    settings+: {
      'cmake.configureArgs': ['-DBUILD_DOCS=ON', '-DBUILD_TESTS=ON'],
    },
  },
  // C++ only
  cmake+: {
    uses_qt: true,
  },
  project_type: 'c++',
  vcpkg+: {
    dependencies: [
      {
        name: 'ecm',
        'version>=': utils.latestVcpkgPortVersion('ecm'),
      },
      {
        name: 'qtbase',
        'version>=': utils.latestVcpkgPortVersion('qtbase'),
      },
    ],
    documentation: 'https://tatsh.github.io/ifup-systemd-resolved/',
    homepage: 'https://github.com/Tatsh/ifup-systemd-resolved/',
    supports: 'linux',
  },
}
