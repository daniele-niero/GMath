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
if not sys.stdout.isatty():
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
    (colors['blue'], colors['blue'], colors['green'], colors['end'])

def appen_to_environment(inEnv):
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