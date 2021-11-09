project('clox', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

exe = executable('clox', [
  'clox.c',
  'chunk.c',
  'memory.c',
  'debug.c',
  ],
  install : true)

test('basic', exe)
