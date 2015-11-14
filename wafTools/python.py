import sys, os
from waflib import Logs
from waflib.Configure import conf
from waflib.Tools import msvc, clang

def options(ctx):
    opt=ctx.add_option_group("Python Configuration options")
    
    opt.add_option('--python-dir', default='', 
                   help='Override if necessary, for example if you want to use a different python than the default one.')

@conf
def find_python(ctx):
    print ctx
    ctx.start_msg('Finding Python')

    if ctx.options.python_dir:
        path_list=[ctx.options.python_dir]
    else:
        path_list=None
    python = ctx.find_program('python', path_list=path_list, var='PYTHON')[0]
    ctx.end_msg(result=True)
    ctx.msg('python dir', python)

    python = ctx.check_cxx(lib='python', uselib_store='')
    ctx.check_cxx(lib='c++', uselib_store='')
    ctx.msg('PYTHON LIB', python)

@conf
def find_python_version(conf):
    pybin=conf.env['PYTHON']
    if not pybin:
        conf.fatal('could not find the python executable')
    cmd=pybin+['-c','import sys\nfor x in sys.version_info: print(str(x))']
    lines=conf.cmd_and_log(cmd).split()
    Logs.info(lines)
    

def configure(ctx):
    ctx.find_python()
    ctx.find_python_version()