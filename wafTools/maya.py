import sys, os
from waflib import Logs
from waflib.Configure import conf
from waflib.Tools import msvc, clang

def getMayaDirectory(mayaVersion):
    if sys.platform=="win32":
        return 'C:\\Program Files\\Autodesk\\Maya%s\\bin' %mayaVersion
    elif sys.platform=="darwin":
        return "/Applications/Autodesk/maya%s/Maya.app/Contents/bin" %mayaVersion

def options(ctx):
    opt=ctx.add_option_group("Maya Configuration options")
    
    opt.add_option('--maya-version', default="2015", help='Version of Maya to try to detect. [default %default]')
    opt.add_option('--maya-dir', default='', 
                help='Autodetected. Override if necessary. [default %s]' %getMayaDirectory('2015'))

@conf
def find_maya(ctx):
    ctx.start_msg('Finding Maya')

    if ctx.options.maya_dir:
        searching_path = ctx.options.maya_dir
    else:
        searching_path = getMayaDirectory(ctx.options.maya_version)

    maya = ctx.find_program('maya', path_list=[searching_path], var='MAYA')
    ctx.msg('Finding Maya', maya[0])

    maya_v = ctx.cmd_and_log(maya + ['-v']).split(',')[0].split()[1]
    ctx.end_msg(maya[0])
    
    if maya_v!=ctx.options.maya_version:
        Logs.warn("Version found (%s) differ from version requested (%s). Version found will be the version taken in account" %(maya_v, ctx.options.maya_version))

        ctx.env['MAYA_VERSION'] = maya_v
    else:
        ctx.env['MAYA_VERSION'] = ctx.options.maya_version

    ctx.msg('', 'Maya Version ' + ctx.env['MAYA_VERSION'])

    ctx.env['MAYA_DIR'] = os.path.split(searching_path)[0]
    if sys.platform=="win32":
        ctx.env['MAYA_PYTHON_INCLUDE'] = os.path.join(ctx.env['MAYA_DIR'], 'include')
        ctx.env['MAYA_PYTHON_LIB_PATH'] = os.path.join(ctx.env['MAYA_DIR'], 'lib')
        ctx.env['MAYA_PYTHON_LIB'] = 'python27'
    if sys.platform=="darwin":
        ctx.env['MAYA_PYTHON_INCLUDE'] = os.path.join(ctx.env['MAYA_DIR'], 'Frameworks/Python.framework/Headers')
        ctx.env['MAYA_PYTHON_LIB'] = os.path.join(ctx.env['MAYA_DIR'], 'Frameworks/Python.framework/Versions/Current/lib')
        ctx.env['MAYA_PYTHON_LIB'] = 'python2.7'


def configure(ctx):
    ctx.find_maya()

    if sys.platform=="win32":
        # ctx.env['MSVC_VERSIONS'] = ['msvc 10.0']
        ctx.env['MSVC_TARGETS'] = ['x64']
        ctx.load('msvc')