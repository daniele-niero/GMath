%module gmath
%{
#include "gmVector4.h"
%}

namespace gmath {
    class Vector4;
    %typemap(out) double* data %{
        $result = PyTuple_New(4); // use however you know the size here
        for (int i = 0; i < 4; ++i) {
            PyTuple_SetItem($result, i, PyFloat_FromDouble($1[i]));
        }
    %}
}


%include "gmVector4.h"

// extending Vector4
namespace gmath{

    %extend Vector4{
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
    }
}

