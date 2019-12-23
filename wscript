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

    opt=ctx.add_option_group("Test Build")  
    opt.add_option('--test-name', default='', )


def configure(conf):
    conf.msg("Platform", sys.platform)

    conf.load('compiler_cxx')
    conf.load('doxygen', tooldir="./waftools")

    if sys.platform=="win32":
        conf.env.append_value('DEFINES', ['WINDOWS'])
    elif sys.platform=="darwin":
        conf.env.append_value('DEFINES', ['MAC'])
        conf.env.append_value('CXXFLAGS', ['-std=c++11', '-stdlib=libc++'])
    elif sys.platform=="linux2":
        conf.env.append_value('DEFINES', ['LINUX'])
        conf.env.append_value('CXXFLAGS', ['-std=c++11', '-stdlib=libc++'])

    debenv = conf.env.derive().detach()
    
    if sys.platform=="win32":
        conf.env.append_value('CXXFLAGS', ['-EHsc'])
    conf.env.append_value('DEFINES', ['RELEASE'])

    conf.setenv('debug', debenv)
    debenv.append_value('CXXFLAGS', ['-O2', '-g'])
    debenv.append_value('DEFINES', ['DEBUG'])


from waflib.Build import BuildContext, InstallContext

class Debug(BuildContext):
    '''Build the debug variant'''
    cmd = 'debug'
    variant = 'debug'

class InstallDebug(InstallContext):
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
        features = 'cxx cxxshlib',
        name="gmath-shared",
        install_path = ctx.env.LIBDIR
        )

    if ctx.env.DOXYGEN:
        ctx.add_group()
        ctx(name="doc", 
            features="doxygen", 
            doxyfile='./resources/doxygen/doxy_config', 
            install_path=ctx.options.doc_out_path)


# from waflib.Build import BuildContext, InstallContext


def build_test(ctx):
    ctx.recurse('./tests/testXfo', 'suka')

# 
class BuildTest(BuildContext):
    '''Build the debug variant'''
    cmd = 'build-test'
    fun = 'build_test'
    variant = 'build_test'