
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
            if isinstance(arg, (OpenMaya.MDagPath, OpenMaya2.MDagPath)):
                return arg
            elif isinstance(arg, (str, unicode)):
                return mpathFromString(arg)
            elif hasattr(arg, '__apimdagpath__'): # this must be a pymel object
                return arg.__apimdagpath__()
            elif hasattr(arg, 'getDagPath'): # this must be a ggNodes object
                return arg.getDagPath()
            else:
                raise RuntimeError('unsupported object type')

        def getMMatrixData(mmatrix):
            if isinstance(mmatrix, OpenMaya.MMatrix):
                return [mmatrix(row, col) for row in range(4) for col in range(4)]
            else:
                return [i for i in mmatrix]

        def setMFnTransform(mfnTransform, mTraMatrix):
            if isinstance(mfnTransform, OpenMaya.MFnTransform):
                mfnTransform.set(mTraMatrix)
            else:
                mfnTransform.setTransformation(mTraMatrix)

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



%pythoncode %{
#--------------------------------------------------------------------#
#  MANUAL PATCH TO PLAY NICE WITH GMATH PURE PYTHON VERSION          #
#               (This is for Guerrilla Only)                         #
#--------------------------------------------------------------------#

PRECISION = EPSILON

#--------------------- deal with python's enum ----------------------#

py_enum_available = False

try:
    import enum
    py_enum_available = True
except ImportError:
    try:
        from DeciPyCommon.Libs.Extensions import Enum as enum
        py_enum_available = True
    except ImportError:
        pass


if py_enum_available:
    class CartesianPlane(enum.IntEnum):
        XY = 0
        YZ = 1
        ZX = 2
        YX = 0
        ZY = 1
        XZ = 2

        def normalVector(self):
            ''' return the vector perpendicular to this plane '''
            if self.value == 0:
                return Vector3.ZAXIS
            elif self.value == 1:
                return Vector3.XAXIS
            elif self.value == 2:
                return Vector3.YAXIS


    class Unit(enum.IntEnum):
        Degrees = 0
        Radians = 1


    class RotationOrder(enum.IntEnum):
        XYZ = 0
        XZY = 1
        YXZ = 2
        YZX = 3
        ZXY = 4
        ZYX = 5


    class Axis(enum.IntEnum):
        NEGX = -1
        NEGY = -2
        NEGZ = -3
        POSX =  1
        POSY =  2
        POSZ =  3

        def asVecotor3(self):
            ''' Gets a Vector3 instance from the Axis enumerator value '''
            if self.value == 1:
                return Vector3.XAXIS
            elif self.value == 2:
                return Vector3.YAXIS
            elif self.value == 3:
                return Vector3.ZAXIS
            elif self.value == -1:
                return -Vector3.XAXIS
            elif self.value == -2:
                return -Vector3.YAXIS
            elif self.value == -3:
                return -Vector3.ZAXIS

        def isX(self):
            ''' Returns if Axis is the X axis (positive or negative) '''
            return abs(self.value) == 1

        def isY(self):
            ''' Returns if Axis is the Y axis (positive or negative) '''
            return abs(self.value) == 2

        def isZ(self):
            ''' Returns if Axis is the Z axis (positive or negative) '''
            return abs(self.value) == 3

#----------------------------- clean up -----------------------------#

del py_enum_available
%}

