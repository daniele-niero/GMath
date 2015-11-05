%module gmath

%include "exception.i"
%include "std_string.i"

%{
#include "gmMatrix4.h"
%}


%typemap(out) double* data %{
  $result = PyTuple_New(16); // use however you know the size here
  for (int i = 0; i < 16; ++i) {
    PyTuple_SetItem($result, i, PyFloat_FromDouble($1[i]));
  }
%}

%include "gmMatrix4.h"

// extending Matrix4
namespace gmath{

    %extend Matrix4{

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
                    for i in range(0, 16):
                        if self[i]!=other[i]:
                            return False
                    return True
                else:
                    return False
        }

        #ifdef MAYA
        %pythoncode {
            def toMayaMatrix(self):
                mayaMat = OpenMaya.MMatrix()
                OpenMaya.MScriptUtil.createMatrixFromList(self.data(), mayaMat) 
                return mayaMat

            def fromMayaMatrix(self, mayaMat):
                self.set(
                    mayaMat(0, 0), mayaMat(0, 1), mayaMat(0, 2), mayaMat(0, 3),
                    mayaMat(1, 0), mayaMat(1, 1), mayaMat(1, 2), mayaMat(1, 3),
                    mayaMat(2, 0), mayaMat(2, 1), mayaMat(2, 2), mayaMat(2, 3),
                    mayaMat(3, 0), mayaMat(3, 1), mayaMat(3, 2), mayaMat(3, 3) )
                return self

            def toPymelMatrix(self):
                pymelMat = pmdt.Matrix()
                pymelMat.assign(self.data())
                return pymelMat

            def fromPymelMatrix(self, pymelMat):
                self.set(
                    pymelMat(0, 0), pymelMat(0, 1), pymelMat(0, 2), pymelMat(0, 3),
                    pymelMat(1, 0), pymelMat(1, 1), pymelMat(1, 2), pymelMat(1, 3),
                    pymelMat(2, 0), pymelMat(2, 1), pymelMat(2, 2), pymelMat(2, 3),
                    pymelMat(3, 0), pymelMat(3, 1), pymelMat(3, 2), pymelMat(3, 3) )
                return self
        }
        #endif
    }
}

