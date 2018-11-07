%module gmath
%{
#include "gmVector3.h"
%}


namespace gmath {
    class Vector3;
    %typemap(out) double* data %{
        $result = PyTuple_New(3); // use however you know the size here
        for (int i = 0; i < 3; ++i) {
            PyTuple_SetItem($result, i, PyFloat_FromDouble($1[i]));
        }
    %}
}

#ifdef CMAYA
    // ignore the c++ functions and re-implement them in python
    // this bypass the compatibility problem between swig and whatever maya's return in python.
    %ignore fromMayaVector;
    %ignore toMayaVector;
#endif

%include "gmVector3.h"

// extending Vector3
namespace gmath{
    
    %extend Vector3{

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
                    return other.x==self.x and other.y==self.y and other.z==self.z
                else:
                    return False
        }

        #if defined(CMAYA) || defined(PYMAYA)

        %pythoncode {
            def toMayaVector(self):
                return OpenMaya.MVector(self.x, self.y, self.z)

            def fromMayaVector(self, mayaVector):
                self.set(mayaVector.x, mayaVector.y, mayaVector.z)
        }
        
        #endif
    }
}

