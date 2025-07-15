local utils = import 'utils.libjsonnet';

(import 'defaults.libjsonnet') + {
  local top = self,
  // General settings

  // Shared
  github_username: 'Tatsh',
  security_policy_supported_versions: { '1.5.x': ':white_check_mark:' },
  authors: [
    {
      'family-names': 'Udvare',
      'given-names': 'Andrew',
      email: 'audvare@gmail.com',
      name: '%s %s' % [self['given-names'], self['family-names']],
    },
  ],
  project_name: 'ifup-systemd-resolved',
  version: '0.0.2',
  description: 'Hook for openfortivpn to set up DNS with systemd-resolved.',
  keywords: ['openconnect', 'systemd', 'vpn'],
  want_main: false,
  copilot: {
    intro: 'ifup-systemd-resolved is a tool for openfortivpn to set up DNS with systemd-resolved after connection.',
  },
  social+: {
    mastodon+: { id: '109370961877277568' },
  },

  // GitHub
  github+: {
    funding+: {
      ko_fi: 'tatsh2',
      liberapay: 'tatsh2',
      patreon: 'tatsh2',
    },
  },

  // C++ only
  cmake+: {
    uses_qt: true,
  },
  project_type: 'c++',
  vcpkg+: {
    dependencies: [{
      name: 'ecm',
      'version>=': '6.7.0',
    }],
  },
}
