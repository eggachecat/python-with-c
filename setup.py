from distutils.core import setup, Extension

sa_module = Extension('sa_module',
                      sources=['sa_module.c'])

setup(name='lesson_one',
      version='1.0',
      description='Python Package with Hello World C Extension',
      ext_modules=[sa_module])
