%module gmath
%{
#include "gmUsefulFunctions.h"
%}


#if defined(PYENUM)

%ignore IntersectionType;

%pythonbegin %{
    class IntersectionType(enum.IntEnum):
        UNDEFINED           = 0
        INTERSECTION        = 1
        NO_INTERSECTION     = 2
        PARRALLEL           = 3
        LAYS_ON_PLANE       = 4
        TOUCH_ON_ONE_POINT  = 5
%}
    
#endif


%include "gmUsefulFunctions.h"