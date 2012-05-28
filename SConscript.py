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
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA	02110-1301, USA.

import os, sys

Import('env')
install_path = env['install_path']


if sys.platform == "win32":
    env.Append(CCFLAGS='/EHsc')
    env.Append(no_import_lib=1)


if env['library']=='static' :
   lib = env.Library('gmath', Glob("source/*.cpp"), CPPPATH=['include'])
elif env['library']=='shared' :
	lib = env.SharedLibrary('gmath', Glob("source/*.cpp"), CPPPATH=['include'])

env.Install(install_path, lib)