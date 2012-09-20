/* Copyright (c) 2012, Daniele Niero
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

#include "../include/gmMath.h"

namespace gmath
{
	template<> const float Math<float>::EPSILON = 1e-06f;
	template<> const float Math<float>::PI = (float)(4.0*atan(1.0));
	template<> const float Math<float>::HALFPI = Math<float>::PI*0.5f;
	template<> const float Math<float>::MAX = FLT_MAX;
	template<> const float Math<float>::MIN = -FLT_MAX;
	template<> const float Math<float>::SMALLEST = FLT_MIN;

	template<> const double Math<double>::EPSILON = 1e-08;
	template<> const double Math<double>::PI = 4.0*atan(1.0);
	template<> const double Math<double>::HALFPI = Math<double>::PI*0.5;
	template<> const double Math<double>::MAX = DBL_MAX;
	template<> const double Math<double>::MIN = -DBL_MAX;
	template<> const double Math<double>::SMALLEST = DBL_MIN;
}
