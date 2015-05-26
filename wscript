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
    source_files = ctx.path.find_node("source").ant_glob("*.cpp")
    include_path = ["./include"]
    install_path = "./lib"

    if ctx.options.library=='static':
        ctx.stlib(
            source=source_files,
            includes=include_path,
            target="gmath",
            define=['RELEASE'],
            cxxflags=['-EHsc', '-Zl', '-MD'],
            install_path=install_path)

    elif ctx.options.library=='shared':
        ctx.shlib(
            source=source_files,
            includes=include_path,
            target="gmath",
            define=['RELEASE'],
            cxxflags=['-EHsc', '-MD'],
            install_path=install_path)

    elif ctx.options.library=='python':
        print "Python library can be only build as release and shared"

        python_include_path = "D:/dev/HRZ/Tools/Software/Maya/Maya-SCE-2015_x64/include/python2.7"
        python_lib_path = "D:/dev/HRZ/Tools/Software/Maya/Maya-SCE-2015_x64/lib"
        python_lib = "python27"

        boost_include_path = "D:/dev/common/Tools/PythonTools/BoostPython/boost-1_54-python27/include"
        boost_lib_path = "D:/dev/common/Tools/PythonTools/BoostPython/boost-1_54-python27/lib"
        boost_python_lib = "libboost_python-vc100-mt-1_54"

        library_name = "_win_gmath"

        source_files += ctx.path.find_node("gmath_py/source").ant_glob("*.cpp")
        include_path += ['./gmath_py/include', python_include_path, boost_include_path]
        pygmath = ctx.shlib(
            target      = library_name, 
            source      = source_files,
            includes    = include_path,
            defines     = ['RELEASE', 'GMATH_PY_MODULE_NAME=%s' %library_name],
            libpath     = [python_lib_path, boost_lib_path],
            lib         = [python_lib, boost_python_lib],
            cxxflags    = ['-EHsc', '-Zl', '-MD', '-DBOOST_PYTHON_STATIC_LIB', '-DBOOST_PYTHON_MAX_ARITY=17'],
            install_path=install_path
            )
        pygmath.env.cxxshlib_PATTERN = "%s.pyd"


def test(ctx):
    print(ctx.options.build_type)
    print(ctx.options.library)