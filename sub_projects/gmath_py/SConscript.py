# A math library for 3D graphic.
# Copyright (C) 2010-2012 Daniele Niero

# Author contact: daniele . niero @ gmail . com

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 3
# of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.


cyan   = '\033[96m'
purple = '\033[95m'
blue   = '\033[94m'
green  = '\033[92m'
yellow = '\033[93m'
red    = '\033[91m'
end    = '\033[0m'


import sys, os
import config

Import('env')

if env.has_key('install'):
    install_path = env['install']
else:
    from distutils.sysconfig import get_python_lib
    print(get_python_lib())
    print yellow+'Guessing install path: '+purple+get_python_lib()
    install_path = get_python_lib()

# if sys.platform == "win32":
#     env.Append(CCFLAGS='/EHsc')
#     env.Append(no_import_lib=1)
#     shlib_suffix='.pyd'
# if sys.platform == "darwin":
#     print 'it\'s a mac'
#     shlib_suffix='.so'
# if sys.platform == "linux2":
#     shlib_suffix='.so'

# env.Append(CCFLAGS = '-DBOOST_PYTHON_STATIC_LIB -DBOOST_PYTHON_MAX_ARITY=17')
                  
# env.Append(CPPPATH=['include',
#                     config.python_include_path,
#                     config.boost_include_path,
#                     os.environ['GMATH_INCLUDE']] )

# env.Append(LIBPATH = [config.python_lib_path,
#                       config.boost_lib_path, 
#                       os.environ['GMATH_LIB']])

# static_boostpython = File( os.path.join(config.boost_lib_path, config.boost_python_lib) )
# python_binding = env.SharedLibrary(
#     target='gmath',
#     source=Glob('source/*.cpp'),
#     CPPDEFINES='BUILD_BINDINGS',
#     LIBS=[static_boostpython, 
#           'gmath', 
#           config.python_lib],
#     SHLIBPREFIX='',
#     SHLIBSUFFIX=shlib_suffix
#     )

# env.Install(install_path, python_binding)

