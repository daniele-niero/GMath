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
            @staticmethod
            def init(*args):
                ''' Through this function is possible to initialise the class also with a Python list or tuple '''
                if type(args[0]) in (list, tuple):
                    a = args[0]
                    if len(a) != 4:
                        raise AttributeError('list must contains 4 values')
                    args = a[0], a[1], a[2], a[3]
                return Quaternion(*args)

            def __reduce__(self):
                ''' provides pickle support '''
                return self.__class__, self.data()

            def __eq__(self, other):
                if type(other) == type(self):
                    return other.x==self.x and other.y==self.y and other.z==self.z and other.w==self.w
                else:
                    return False
        }

        #ifdef MAYA
        %pythoncode {
            def toMayaQuaternion(self):
                return OpenMaya.MQuaternion(self.x, self.y, self.z, self.w)

            def fromMayaQuaternion(self, mayaQuat):
                self.set(mayaQuat.x, mayaQuat.y, mayaQuat.z, mayaQuat.w)
                return self

            def toPymelQuaternion(self):
                return pmdt.Quaternion(self.x, self.y, self.z, self.w)

            def fromPymelQuaternion(self, pymelQuat):
                self.set(pymelQuat.x, pymelQuat.y, pymelQuat.z, pymelQuat.w)
                return self
        }
        #endif
    }
}

