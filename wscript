import os, sys

APPNAME = 'gmath'
VERSION = '2.0'

top = '.'
out = 'build'

def options(ctx):
    ctx.load('compiler_cxx')
    ctx.load('doxygen', tooldir="./waftools")

    grp = ctx.get_option_group('Configuration options')
    grp.add_option('--doc-out-path', default='./documentation',
                   help='documentation install path [default: %default]')


def configure(conf):
    conf.load('compiler_cxx')
    conf.load('doxygen', tooldir="./waftools")

    debenv = conf.env.derive().detach()
    
    conf.env.append_value('CXXFLAGS', ['-EHsc'])
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
        install_path = ctx.env.LIBDIR
        )

    ctx.shlib(
        target='gmath',
        includes='include',
        source=source,
        name="gmath-shared",
        install_path = ctx.env.LIBDIR
        )

    if ctx.env.DOXYGEN:
        ctx.add_group()
        ctx(name="doc", 
            features="doxygen", 
            doxyfile='./resources/doxygen/doxy_config', 
            install_path=ctx.options.doc_out_path)
