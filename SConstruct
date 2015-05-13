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

import os, sys
import SConsOutputColors as output_colors

#-------------------------------------------------------------------------------------------------------------------
# preparing the SCons Environment
#-------------------------------------------------------------------------------------------------------------------
scons_vars = Variables()
scons_vars.AddVariables( 
    EnumVariable('build', 'Set the build type', 'release', allowed_values=('release', 'debug')),
    EnumVariable('library', 'Set the type of library to build', 'static', allowed_values=('static', 'shared', 'python')),
    BoolVariable('docs', 'Set to "yes" or "t" to build documentation with Doxygen.', 0),
    PathVariable('install', 'Set where to install the library', os.path.abspath(os.path.join('.', 'bin')), PathVariable.PathAccept) )

env = Environment(variables = scons_vars, MSVC_VERSION = "10.0")
# generates the help
Help(scons_vars.GenerateHelpText(env))
# customizes output
output_colors.append_to_environment(env)

#-------------------------------------------------------------------------------------------------------------------
# Set up the Release or Debug 
#-------------------------------------------------------------------------------------------------------------------
if env['build']=='release':
    env.Append(CCFLAGS = '-DRELEASE')
elif env['build']=='debug':
    env.Append(CCFLAGS = '-g')
    env.Append(CCFLAGS = '-DDEBUG')

env["gmathInclude"] = os.path.abspath(os.path.join('.', 'include'))
env["gmathSource"]  = os.path.abspath(os.path.join('.', 'source'))

#-------------------------------------------------------------------------------------------------------------------
# Deciding wich Sconscipt to use.
# if we are building a static or shared library, then we will use the Sconscript for build GMath C++
# if we are building the python wrapper than we will use the Sconscript in  ./sub_projects/gmath_py
#-------------------------------------------------------------------------------------------------------------------

cppScript = 'SConscript.py'
# prepare a suitable build path
env['build_path'] = os.path.join('./build', sys.platform, env['build'], env['library'])


sys.path.append(os.path.abspath('./sub_projects/gmath_py'))
pyScript = './sub_projects/gmath_py/SConscript.py'
# prepare a suitable build path


if env['library'] == 'static' or env['library'] == 'shared':
    SConscript(
        cppScript, 'env', 
        variant_dir=env['build_path'], 
        duplicate=0)

elif env['library'] == 'python':
    python_ver = '%i.%i' %(sys.version_info.major, sys.version_info.minor)
    env['build_path'] = os.path.join(env['build_path'], 'python'+python_ver)
    SConscript(
        pyScript, 'env', 
        variant_dir=env['build_path'], 
        duplicate=0)

#-------------------------------------------------------------------------------------------------------------------
# End finally, if the the user decided to build the doc, just fire the doxygen command
#-------------------------------------------------------------------------------------------------------------------
if env['docs']:
    doc_command = "doxygen resources/doxygen/doxy_config"
    os.system(doc_command)

