logiops_sources = [
  'main.c',
  'l-application-resources.c',
  'l-application.c',
  'l-window.c',
  'ui/l-content-manager.c',
  'ui/header-bar.c',
  'ui/l-device-button.c',
  'ui/l-pref-panel.c',
  'data/l-conf-reader.c',
  'types/l-device.c',
]

logiops_deps = [
  dependency('libadwaita-1', version: '>= 1.3'),
  dependency('libconfig'),
]

logiops_sources += gnome.compile_resources('l-resources',
  'l.gresource.xml',
  c_name: 'logiops'
)

executable('logiops', logiops_sources,
  dependencies: logiops_deps,
       install: true,
)
