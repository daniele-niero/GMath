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

import os, sys
import SConsOutputColors as output_colors

vars = Variables()
vars.AddVariables( EnumVariable('build', 'Set the build type', 'release', allowed_values=('release', 'debug')),
                   EnumVariable('library', 'Set the type of library to build', 'static', allowed_values=('static', 'shared', 'python')),
                   BoolVariable('tests', 'Set to "yes" or "t" to build the test suite.', 0),
                   BoolVariable('docs', 'Set to "yes" or "t" to build documentation with Doxygen.', 0),
                   PathVariable('install_path', 'Set where to install the library', '.', PathVariable.PathIsDirCreate) )


env = Environment(variables = vars)
output_colors.appen_to_environment(env)

if env['install_path'] == ".":
    env['install_path'] = os.path.join('./lib', sys.platform, env['build'], env['library'])
else:
    pass
env['install_path'] = os.path.abspath(env['install_path'])


Help(vars.GenerateHelpText(env))

# mostly needed by the python Sconscript
os.environ["GMATH_INCLUDE"] = os.path.abspath("./include")
os.environ["GMATH_LIB"]     = env['install_path'].replace('python', 'static')

script = None

if env['build']=='release':
    env.Append(CCFLAGS = '-DRELEASE')
elif env['build']=='debug':
    env.Append(CCFLAGS = '-g')
    env.Append(CCFLAGS = '-DDEBUG')


if env['library'] == 'static':
    script = 'SConscript.py'
elif env['library'] == 'shared':
    script = 'SConscript.py'
elif env['library'] == 'python':
    sys.path.append(os.path.abspath('./sub_projects/gmath_py'))
    script = './sub_projects/gmath_py/SConscript.py'


if env['tests']:
    script = './sub_projects/tests/SConscript.py'

if env['docs']:
    doc_command = "doxygen resources/doxygen/doxy_config"
    os.system(doc_command)

SConscript(
    script, 'env', 
    variant_dir=os.path.join('./build', sys.platform, env['build'], env['library']), 
    duplicate=0)


