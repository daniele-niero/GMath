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


colors = {}
colors['cyan']   = '\033[96m'
colors['purple'] = '\033[95m'
colors['blue']   = '\033[94m'
colors['green']  = '\033[92m'
colors['yellow'] = '\033[93m'
colors['red']    = '\033[91m'
colors['end']    = '\033[0m'

#If the output is not a terminal, remove the colors
if not sys.stdout.isatty() or sys.platform=="win32":
   for key, value in colors.iteritems():
      colors[key] = ''

compile_source_message = '%sCompiling %s==> %s$SOURCE%s' % \
   (colors['blue'], colors['blue'], colors['green'], colors['end'])

compile_shared_source_message = '%sCompiling shared %s==> %s$SOURCE%s' % \
   (colors['blue'], colors['blue'], colors['green'], colors['end'])

link_program_message = '%sLinking Program %s==> %s$TARGET%s' % \
   (colors['blue'], colors['blue'], colors['green'], colors['end'])

link_library_message = '%sLinking Static Library %s==> %s$TARGET%s' % \
   (colors['blue'], colors['blue'], colors['green'], colors['end'])

ranlib_library_message = '%sRanlib Library %s==> %s$TARGET%s' % \
   (colors['blue'], colors['blue'], colors['green'], colors['end'])

link_shared_library_message = '%sLinking Shared Library %s==> %s$TARGET%s' % \
   (colors['blue'], colors['blue'], colors['green'], colors['end'])

java_library_message = '%sCreating Java Archive %s==> %s$TARGET%s' % \
   (colors['blue'], colors['blue'], colors['green'], colors['end'])

install_message = ".\n%sInstallation:\n\t%s$SOURCE  ==>  %s$TARGET%s\n." % \
    (colors['green'], colors['green'], colors['green'], colors['end'])

def append_to_environment(inEnv):
    inEnv.Append(CXXCOMSTR = compile_source_message)
    inEnv.Append(CCCOMSTR = compile_source_message)
    inEnv.Append(SHCCCOMSTR = compile_shared_source_message)
    inEnv.Append(SHCXXCOMSTR = compile_shared_source_message)
    inEnv.Append(ARCOMSTR = link_library_message)
    inEnv.Append(RANLIBCOMSTR = ranlib_library_message)
    inEnv.Append(SHLINKCOMSTR = link_shared_library_message)
    inEnv.Append(LINKCOMSTR = link_program_message)
    inEnv.Append(JARCOMSTR = java_library_message)
    inEnv.Append(JAVACCOMSTR = compile_source_message)

    inEnv.Append(INSTALLSTR = install_message)