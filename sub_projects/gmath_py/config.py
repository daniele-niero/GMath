import os

py_ver = 2.6

python_include_path = "/System/Library/Frameworks/Python.framework/Versions/%s/include/python%s" %(py_ver, py_ver)
python_lib_path = "/System/Library/Frameworks/Python.framework/Versions/%s/lib" %py_ver
python_lib = "python%s" %py_ver

boost_include_path = "/usr/local/boost_1_49_0/lib_boost_python%s/include" %py_ver
boost_lib_path = "/usr/local/boost_1_49_0/lib_boost_python%s/stage/lib" %py_ver
boost_python_lib = "libboost_python.a"
