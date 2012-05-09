# A math library for 3D graphic.
# Copyright (C) 2010 Daniele Niero

# Author contact: nieroinfo@gmail.com

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

import sys, os
import config

Import('env')
install_path = os.path.join(env['install_path'], 'python%s/site-packages' %config.py_ver)

if sys.platform == "win32":
    env.Append(CCFLAGS='/EHsc')
    env.Append(no_import_lib=1)
    env.Append(SHLIBSUFFIX='.pyd')
if sys.platform == "darwin":
    env.Append(SHLIBPREFIX='')
    env.Append(SHLIBSUFFIX='.so')
if sys.platform == "linux2":
    env.Append(SHLIBSUFFIX='.so')

env.Append(CCFLAGS = '-DBOOST_PYTHON_STATIC_LIB -DBOOST_PYTHON_MAX_ARITY=17')
                  
env.Append(CPPPATH=['include',
                    config.python_include_path,
                    config.boost_include_path,
                    os.environ['GMATH_INCLUDE']] )

env.Append(LIBPATH = [config.python_lib_path,
                      config.boost_lib_path, 
                      os.environ['GMATH_LIB']])

static_boostpython = File( os.path.join(config.boost_lib_path, config.boost_python_lib) )
python_binding = env.SharedLibrary(
    target='gmath',
    source=Glob('source/*.cpp'),
    CPPDEFINES='BUILD_BINDINGS',
    LIBS=[static_boostpython, 
          'gmath', 
          config.python_lib]
    )

env.Install(install_path, python_binding)

