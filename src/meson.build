logiops_sources = [
  'main.c',
  'l-application-resources.c',
  'l-application.c',
  'l-window.c',
  'ui/l-content-manager.c',
  'ui/l-device-card.c',
  'ui/l-authority-check-page.c',
  'ui/l-overview-page.c',
  'ui/l-device-page.c',
  'ui/header-bar.c',
  'ui/l-device-button.c',
  'ui/l-pref-panel.c',
  'ui/l-button-pref-panel.c',
  'ui/l-key-grab-window.c',
  'ui/action-cards/l-keys-label.c',
  'ui/action-cards/l-action-card.c',
  'ui/action-cards/l-cycle-card.c',
  'ui/action-cards/l-keypress-card.c',
  'ui/action-cards/l-gesture-card.c',
  'ui/action-cards/l-action-selector.c',
  'ui/device-description/mx-master-3-description.c',
  'ui/device-description/mx-anywhere-3-description.c',
  'data/l-data-manager.c',
  'data/l-bus-manager.c',
  'data/l-key-code.c',
  'types/l-device.c',
]

logiops_deps = [
  dependency('polkit-gobject-1'),
  dependency('gtk4'),
  dependency('libadwaita-1', version: '>= 1.4'),
]

logiops_sources += gnome.compile_resources('l-resources',
  'l.gresource.xml',
  c_name: 'logiops'
)

executable('logiops', logiops_sources,
  dependencies: logiops_deps,
       install: true,
)
