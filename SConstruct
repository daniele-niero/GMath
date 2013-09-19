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

import os, sys
# import SConsOutputColors as output_colors

#-------------------------------------------------------------------------------------------------------------------
# preparing the SCons Environment
#-------------------------------------------------------------------------------------------------------------------
scons_vars = Variables()
scons_vars.AddVariables( 
    EnumVariable('build', 'Set the build type', 'release', allowed_values=('release', 'debug')),
    EnumVariable('library', 'Set the type of library to build', 'static', allowed_values=('static', 'shared', 'python')),
    BoolVariable('docs', 'Set to "yes" or "t" to build documentation with Doxygen.', 0),
    PathVariable('install', 'Set where to install the library', os.path.abspath(os.path.join('.', 'bin')), PathVariable.PathAccept) )

env = Environment(variables = scons_vars)
# generates the help
Help(scons_vars.GenerateHelpText(env))
# customizes output
# output_colors.append_to_environment(env)

#-------------------------------------------------------------------------------------------------------------------
# Set up the Release or Debug 
#-------------------------------------------------------------------------------------------------------------------
if env['build']=='release':
    env.Append(CCFLAGS = '-DRELEASE')
elif env['build']=='debug':
    env.Append(CCFLAGS = '-g')
    env.Append(CCFLAGS = '-DDEBUG')

#-------------------------------------------------------------------------------------------------------------------
# Deciding wich Sconscipt to use.
# if we are building a static or shared library, then we will use the Sconscript for build GMath C++
# if we are building the python wrapper than we will use the Sconscript in  ./sub_projects/gmath_py
#-------------------------------------------------------------------------------------------------------------------
script = None

if env['library'] == 'static' or env['library'] == 'shared':
    script = 'SConscript.py'
    # prepare a suitable build path
    env['build_path'] = os.path.join('./build', sys.platform, env['build'], env['library'])
elif env['library'] == 'python':
    sys.path.append(os.path.abspath('./sub_projects/gmath_py'))
    script = './sub_projects/gmath_py/SConscript.py'
    # prepare a suitable build path
    python_ver = '%i.%i' %(sys.version_info.major, sys.version_info.minor)
    env['build_path'] = os.path.join('./build', sys.platform, 'python'+python_ver)


SConscript(
    script, 'env') 
    # variant_dir=env['build_path'], 
    # duplicate=0)

#-------------------------------------------------------------------------------------------------------------------
# End finally, if the the user decided to build the doc, just fire the doxygen command
#-------------------------------------------------------------------------------------------------------------------
if env['docs']:
    doc_command = "doxygen resources/doxygen/doxy_config"
    os.system(doc_command)

