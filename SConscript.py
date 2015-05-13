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

# import the environmet. This is a little SCons magic... mmm...
Import('env')

print env["build_path"]

#-------------------------------------------------------------------------------------------------------------------
# Build the specified library
#-------------------------------------------------------------------------------------------------------------------
if env['library']=='static' :
    if sys.platform == "win32":
        env.Append(CCFLAGS=['/EHsc', '/Zl', '/MD'])
        env.Append(no_import_lib=1)

    lib = env.Library('gmath', Glob("source/*.cpp"), CPPPATH=['include'])

elif env['library']=='shared' :
    if sys.platform == "win32":
        env.Append(CCFLAGS=['/EHsc', '/MD'])
        env.Append(no_import_lib=1)

	lib = env.SharedLibrary('gmath', Glob("source/*.cpp"), CPPPATH=['include'])

#-------------------------------------------------------------------------------------------------------------------
# Install the library if and only if the user specify a path usign the extra argument "install"
# for example scons library=static install=/usr/local/bin
#-------------------------------------------------------------------------------------------------------------------
if env.has_key('install'): 
    Default( env.Install(env['install'], lib) )