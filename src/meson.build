logiops_sources = [
  'main.c',
  'logiops-application.c',
  'logiops-window.c',
]

logiops_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1', version: '>= 1.2'),
]

logiops_sources += gnome.compile_resources('logiops-resources',
  'logiops.gresource.xml',
  c_name: 'logiops'
)

executable('logiops', logiops_sources,
  dependencies: logiops_deps,
       install: true,
)
