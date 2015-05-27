APPNAME = 'gmath'
VERSION = '2.0'

top = '.'
out = 'build'

def options(ctx):
    ctx.load('compiler_cxx')

    ctx.add_option("-b", "--build-type", 
                   default='release', 
                   choices=['release', 'debug'], 
                   help="Set the build type. (release/debug), [default: %default]")
    
    ctx.add_option("-l", "--library", 
                   default='static', 
                   choices=['static', 'shared', 'python'], 
                   help='Set the type of library to build. (static/shared/python), [default: %default]')


def configure(ctx):
    ctx.load('compiler_cxx')


def build(ctx):
    # note: not caches attributes
    ctx.env.INCLUDES += ["include"]
    ctx.env.source = ctx.path.find_node("source").ant_glob("*.cpp")
    ctx.env.install_path = "./lib"

    if ctx.options.build_type=="release":
        ctx.env.DEFINES += ["RELEASE"]
    elif ctx.options.build_type=="debug" and not ctx.options.library=='python':
        ctx.env.DEFINES += ["DEBUG"]
        ctx.env.CXXFLAGS.append("-g")



    if ctx.options.library=='static':
        ctx.stlib(
            source=ctx.env.source,
            target="gmath",
            define=['RELEASE'],
            cxxflags=['-EHsc', '-Zl', '-MD'],
            install_path=ctx.env.install_path
            )

    elif ctx.options.library=='shared':
        ctx.shlib(
            source=ctx.env.source,
            target="gmath",
            define=['RELEASE'],
            cxxflags=['-EHsc', '-MD'],
            install_path=ctx.env.install_path)

    elif ctx.options.library=='python':
        ctx.recurse('gmath_py')
