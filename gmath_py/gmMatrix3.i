%module gmath
%{
#include "gmMatrix3.h"
%}


namespace gmath {
    class Matrix3;
    %typemap(out) double* data %{
        $result = PyTuple_New(9); // use however you know the size here
        for (int i = 0; i < 9; ++i) {
            PyTuple_SetItem($result, i, PyFloat_FromDouble($1[i]));
        }
    %}
}

%include "gmMatrix3.h"

// extending Matrix3
namespace gmath{

    %extend Matrix3{
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
                    if len(a) != 9:
                        raise AttributeError('list must contains 9 values')
                    args = a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8]
                return Matrix3(*args)
            
            def __reduce__(self):
                ''' provides pickle support '''
                return self.__class__, self.data()

            def __eq__(self, other):
                if type(other) == type(self):
                    for i in range(0, 9):
                        if self[i]!=other[i]:
                            return False
                    return True
                else:
                    return False
        }
    }
}

