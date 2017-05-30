%module gmath
%{
#include "gmXfo.h"
%}


%include "gmXfo.h"

// extending Xfo
namespace gmath{

    %extend Xfo{
        std::string __str__() { // this is convenient in python
            return $self->toString();
        }

        // pure python extension
        %pythoncode {
            def __reduce__(self):
                ''' provides pickle support '''
                return self.__class__, [self.ori.data(), self.tr.data(), self.sc.data()] 
        }
    }
}

