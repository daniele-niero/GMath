%module gmath
%{
#include "gmEuler.h"
%}


namespace gmath {
    class Euler;
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
    %ignore fromMayaEuler;
    %ignore toMayaEuler;
#endif

%include "gmEuler.h"

// extending Euler
namespace gmath{

    %extend Euler{

        const double& __getitem__(int i) {
            return (*$self)[i];
        }

        void __setitem__(int i, double value) {
            (*$self)[i] = value;
        }

        // this is convenient in python
        std::string __str__() { 
            return $self->toString();
        }

        // pure python extension 
        %pythoncode {
            def __reduce__(self):
                """ provides pickle support """
                data = list(self.data())
                data.append(self.getUnit())
                return self.__class__, data

            def __eq__(self, other):
                if type(other) == type(self):
                    return other.x==self.x and other.y==self.y and other.z==self.z
                else:
                    return False
        }

        #if defined(CMAYA) || defined(PYMAYA)

        %pythoncode {
            def toMayaEuler(self):
                return OpenMaya.MEulerRotation(self.x, self.y, self.z)

            def fromMayaEuler(self, mayaEul):
                self.set(mayaEul.x, mayaEul.y, mayaEul.z)
        }
        
        #endif
    }
}

