logiops_sources = [
  'main.c',
  'l-application.c',
  'l-window.c',
  'ui/l-content-manager.c',
  'ui/header-bar.c',
  'ui/l-device-button.c',
  'ui/device-layers/mx-master-3.c',
  'ui/device-layers/buttons-layer.c',
]

logiops_deps = [
  dependency('libadwaita-1', version: '>= 1.3'),
]

logiops_sources += gnome.compile_resources('l-resources',
  'l.gresource.xml',
  c_name: 'logiops'
)

executable('logiops', logiops_sources,
  dependencies: logiops_deps,
       install: true,
)
