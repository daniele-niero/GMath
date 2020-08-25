%module gmath
%{
#include "gmQuaternion.h"
%}

namespace gmath {
    class Quaternion;
    %typemap(out) double* data %{
        $result = PyTuple_New(4); // use however you know the size here
        for (int i = 0; i < 4; ++i) {
            PyTuple_SetItem($result, i, PyFloat_FromDouble($1[i]));
        }
    %}
}

#ifdef CMAYA
    // ignore the c++ functions and re-implement them in python
    // this bypass the compatibility problem between swig and whatever maya's return in python.
    %ignore fromMayaQuaternion;
    %ignore toMayaQuaternion;
#endif

%include "gmQuaternion.h"

// extending Quaternion
namespace gmath{

    %extend Quaternion{
        const double& __getitem__(int i) {
            return (*$self)[i];
        }

        void __setitem__(int i, double value) {
            (*$self)[i] = value;
        }

        std::string __str__() { // this is convenient in python
            return $self->toString();
        }

        // pure python extension 
        %pythoncode {
            def __reduce__(self):
                ''' provides pickle support '''
                return self.__class__, self.data()

            def __eq__(self, other):
                if type(other) == type(self):
                    return other.x==self.x and other.y==self.y and other.z==self.z and other.w==self.w
                else:
                    return False
        }

        #if defined(CMAYA) || defined(PYMAYA)

        %pythoncode {
            def toMayaQuaternion(self):
                return OpenMaya.MQuaternion(self.x, self.y, self.z, self.w)

            def fromMayaQuaternion(self, mayaQuat):
                self.set(mayaQuat.x, mayaQuat.y, mayaQuat.z, mayaQuat.w)

            def toMaya2Quaternion(self):
                return OpenMaya2.MQuaternion(self.x, self.y, self.z, self.w)
        }

        #endif
    }
}

