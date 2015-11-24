import os, sys

APPNAME = 'gmath'
VERSION = '2.0'

top = '.'
out = 'build'

def options(ctx):
    ctx.load('compiler_cxx')

def configure(conf):
    conf.load('compiler_cxx')

    debenv = conf.env.derive().detach()

    conf.env.append_value('DEFINES', ['RELEASE'])

    conf.setenv('debug', debenv)
    debenv.append_value('CXXFLAGS', ['-O2', '-g'])
    debenv.append_value('DEFINES', ['DEBUG'])


from waflib.Build import BuildContext, InstallContext
class debug(BuildContext):
    '''Build the debug variant'''
    cmd = 'debug'
    variant = 'debug'
class installdebug(InstallContext):
    '''Install the debug variant'''
    cmd = 'install-debug'
    variant = 'debug'

        
def build(ctx):
    source = ctx.path.find_node("source").ant_glob("*.cpp")

    ctx.stlib(
        target='gmath',
        includes='include',
        source=source,
        name="gmath-static",
        install_path=ctx.env.LIBDIR
        )

    ctx.shlib(
        target='gmath',
        includes='include',
        source=source,
        name="gmath-shared"
        )
