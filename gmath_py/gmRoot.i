
%module gmath
%begin %{
#define SWIG_PYTHON_2_UNICODE
%}

%feature("autodoc", 1);

%include "exception.i"
%include "std_except.i"
%include "std_string.i"
%include "std_vector.i"
namespace std {
  %template(DoubleVector) vector<double>;
}

%{
#define SWIG_FILE_WITH_INIT
//#include <memory>
#include "gmRoot.h"
%}

#if defined(CMAYA) || defined(PYMAYA)
%pythoncode {
    MAYA_IMPLEMENTED = True
    try:
        from maya.api import OpenMaya as OpenMaya2
        from maya import cmds, OpenMaya

        def mpathFromString(dagName):
            sl = OpenMaya.MSelectionList()
            sl.add(dagName)
            path = OpenMaya.MDagPath()
            sl.getDagPath(0, path)
            return path

        def getMDagPath(arg):
            dagpath = None 
            if isinstance(arg, OpenMaya.MDagPath):
                return arg
            elif isinstance(arg, (str, unicode)):
                return mpathFromString(arg)
            elif hasattr(arg, '__apimdagpath__'): # this must be a pymel object
                return arg.__apimdagpath__()
            else:
                raise RuntimeError('unsupported object type')

    except:
        MAYA_IMPLEMENTED = False

}
#endif

%exception {
    try {
        $action
    } catch (const std::exception& e) {
        SWIG_exception(SWIG_RuntimeError, e.what());
    }
}

// handler for std::out_of_range thrown by the extended 
// __getitem__ implmented in each class' wrapper
%exception __getitem__ {
    try {
        $action
    } catch (std::out_of_range &e) {
        SWIG_exception(SWIG_IndexError, const_cast<char*>(e.what()));
        return NULL;
    }
}

// __setitem__ implmented in each class' wrapper
%exception __setitem__ {
    try {
        $action
    } catch (std::out_of_range &e) {
        SWIG_exception(SWIG_IndexError, const_cast<char*>(e.what()));
        return NULL;
    }
}

%ignore *::operator[](int i);
%ignore *::operator[](int i) const;
%ignore *::operator=;
%ignore *::operator==;
%ignore *::operator!=;
%ignore GMathError;


//%include <std_shared_ptr.i>
//
//%shared_ptr(gmath::Vector3)
//%shared_ptr(gmath::Vector4)
//%shared_ptr(gmath::Matrix3)
//%shared_ptr(gmath::Matrix4)
//%shared_ptr(gmath::Quaternion)
//%shared_ptr(gmath::Xfo)


%include "gmRoot.h"
%include "gmVector3.i"
%include "gmVector4.i"
%include "gmEuler.i"
%include "gmQuaternion.i"
%include "gmMatrix3.i"
%include "gmMatrix4.i"
%include "gmXfo.i"
%include "gmUsefulFunctions.i"

