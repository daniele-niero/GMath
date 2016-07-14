
%module gmath

%feature("autodoc", 1);

%include "exception.i"
%include "std_except.i"
%include "std_string.i"

%{
#define SWIG_FILE_WITH_INIT
#include "gmRoot.h"

%}

#ifdef MAYA
%pythoncode {
    from maya import OpenMaya
    import pymel.core.datatypes as pmdt
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


%include "gmRoot.h"
%include "gmVector3.i"
%include "gmVector4.i"
%include "gmEuler.i"
%include "gmQuaternion.i"
%include "gmMatrix3.i"
%include "gmMatrix4.i"

