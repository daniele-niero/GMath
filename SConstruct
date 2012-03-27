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
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA	02110-1301, USA.

import os, sys


vars = Variables()
vars.AddVariables( EnumVariable('build', 'Set the build type', 'release', allowed_values=('release', 'debug', 'none')),
				   EnumVariable('library', 'Set the type of library to build', 'static', allowed_values=('static', 'dynamic', 'python_bindings')),
				   BoolVariable('tests', 'Set to "yes" or "t" to build the test suite. NOTE: this doesn\'t work with library=python_bindings', 0),
				   BoolVariable('docs', 'Set to "yes" or "t" to build documentation with Doxygen.', 0),
				   PathVariable('install_path', 'Set where to install the library', "./lib/", PathVariable.PathIsDirCreate) )

env = Environment(variables = vars)
install_fullpath = os.path.abspath(env['install_path'])
env['install_path'] = os.path.join(install_fullpath, env['build'])

Help(vars.GenerateHelpText(env))


scripts = []

if env['build']=='release':
	env.Append(CCFLAGS = '-DRELEASE')
	scripts = ['./SConscript.py']
elif env['build']=='debug':
	env.Append(CCFLAGS = '-g')
	env.Append(CCFLAGS = '-DDEBUG')
	scripts = ['./SConscript.py']

if env['tests']:
	scripts.append('./sub_projects/tests/SConscript.py')

if env['docs']:
	doxy_config_path = os.path.join( os.path.abspath('resources/doxygen'), 'doxy_config' )
	doc_command = """export $
	cd %s
	doxygen %s""" %(install_fullpath, doxy_config_path)
	os.system(doc_command)

SConscript(scripts, 'env')


