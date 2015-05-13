/* Copyright (c) 2010-13, Daniele Niero
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this 
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */


#include <boost/python.hpp>
#include "pygmRoot.h"
#include "pygmMath.h"
#include "pygmEuler.h"
#include "pygmVector3.h"
#include "pygmVector4.h"
#include "pygmMatrix3.h"
#include "pygmMatrix4.h"
#include "pygmQuaternion.h"


#ifndef GMATH_PY_MODULE_NAME
  #define GMATH_PY_MODULE_NAME gmath
#endif  

BOOST_PYTHON_MODULE(GMATH_PY_MODULE_NAME)
{
    wrapRoot();
    wrapMath();
    wrapEuler();
    wrapVector3();
    wrapVector4();
    wrapMatrix3();
    wrapMatrix4();
    wrapQuaternion();
}

