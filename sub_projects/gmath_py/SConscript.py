# /* Copyright (c) 2010-13, Daniele Niero
# All rights reserved.

# Redistribution and use in source and binary forms, with or without 
# modification, are permitted provided that the following conditions are met:

# 1. Redistributions of source code must retain the above copyright notice, this 
#    list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice, 
#    this list of conditions and the following disclaimer in the documentation 
#    and/or other materials provided with the distribution.

# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
# IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */


import sys, os
try:
    import config
except:
    error = """ config.py file not found. 
    Please, copy 'config_example' to config.py (create if necessary) and change it to accomodate your system.
    The mandatory attributes are:
     * python_include_path
     * python_lib_path
     * python_lib
     * boost_include_path
     * boost_lib_path
     * boost_python_lib """
    raise EnvironmentError(error)

Import('env')

if env.has_key('install'):
    install_path = env['install']
else:
    from distutils.sysconfig import get_python_lib
    print(get_python_lib())
    print 'Guessing install path: '+get_python_lib()
    install_path = get_python_lib()

if sys.platform == "win32":
    env.Append(CCFLAGS=['/EHsc', '/Zl', '/MD'])
    env.Append(no_import_lib=1)
    shlib_suffix='.pyd'
if sys.platform == "darwin":
    print 'it\'s a mac'
    shlib_suffix='.so'
if sys.platform == "linux2":
    shlib_suffix='.so'

env.Append(CXXFLAGS = '-DBOOST_PYTHON_STATIC_LIB -DBOOST_PYTHON_MAX_ARITY=17')
                  
env.Append(CPPPATH=['include',
                    '../../include',
                    config.python_include_path,
                    config.boost_include_path] )


env.Append(LIBPATH = [config.python_lib_path,
                      config.boost_lib_path,
                      '../../bin'])


python_binding = env.SharedLibrary(
    target='gmath',
    source=Glob('source/*.cpp'),
    CPPDEFINES='BUILD_BINDINGS',
    LIBS=['gmath',
          config.boost_python_lib,
          config.python_lib],
    SHLIBPREFIX='',
    SHLIBSUFFIX=shlib_suffix
    )

env.Install(install_path, python_binding)

