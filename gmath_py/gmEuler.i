%module gmath

%include "exception.i"
%include "std_string.i"

%{
#include "gmEuler.h"
%}


%typemap(out) double* data %{
    $result = PyTuple_New(3); // use however you know the size here
    for (int i = 0; i < 3; ++i) {
        PyTuple_SetItem($result, i, PyFloat_FromDouble($1[i]));
    }
%}

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
                return self.__class__, self.data()

            def __eq__(self, other):
                if type(other) == type(self):
                    return other.x==self.x and other.y==self.y and other.z==self.z
                else:
                    return False
        }

        #ifdef MAYA
        %pythoncode {
            def toMayaEuler(self):
                return OpenMaya.MEulerRotation(self.x, self.y, self.z)

            def fromMayaEuler(self, mayaEul):
                self.set(mayaEul.x, mayaEul.y, mayaEul.z)
                return self

            def toPymelEuler(self):
                return pmdt.EulerRotation(self.x, self.y, self.z, unit=self.unit)

            def fromPymelEuler(self, pymelEul):
                pmUnit = pymelEul.unit
                if pmUnit=='degrees':
                    pmUnit=0
                elif pmUnit=='radians':
                    pmUnit=1
                self.setUnit(pmUnit)
                self.set(pymelEul.x, pymelEul.y, pymelEul.z)
                return self
        }
        #endif
    }
}

