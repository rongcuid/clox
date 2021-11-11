project('clox', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

exe = executable('clox', [
  'main.c',
  'chunk.c',
  'memory.c',
  'debug.c',
  'value.c',
  'vm.c',
  'compiler.c',
  'scanner.c',
  'object.c',
  ],
  install : true)

test('basic', exe)
