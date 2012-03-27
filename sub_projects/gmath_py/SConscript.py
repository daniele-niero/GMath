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

import sys, os

Import('env')
inf = sys.version_info
pythonVer = 'python%s.%s' %(inf[0], inf[1])
install_path = os.pah.join(env['install_path'], '%s/site-packages' %pythonVer)

def dependenciesCheck(varToCheck):
	errorFound = False
	print ''
	for var in varToCheck:
		if not os.environ.has_key(var):
			print "%s environment variable doesn't exist." %var
			errorFound = True
	print ''
	return errorFound

if dependenciesCheck(['BOOST_LIB', 'BOOST_INCLUDE', 'PYTHON_INCLUDE']):
	raise EnvironmentError, 'please correct the above problem(s)\n'


env = Environment(CPPPATH=['../includes',
					       os.environ['BOOST_INCLUDE'],
					       os.environ['PYTHON_INCLUDE']],
				  LIBPATH = [os.environ['BOOST_LIB']]
				  )

python_binding = env.SharedLibrary(
	target='gmath',
	source=Glob('../sources/*.cpp')+Glob('*.cpp'),
	CPPDEFINES='BUILD_BINDINGS',
	CPPPATH=['../includes',
	         os.environ['BOOST_INCLUDE'],
	         os.environ['PYTHON_INCLUDE']],
    LIBPATH = [os.environ['BOOST_LIB']],
	LIBS=['libboost_python'],
	SHLIBPREFIX=''
	)

env.Install(install_path, python_binding)

