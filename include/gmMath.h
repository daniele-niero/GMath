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

#ifndef GMMATH_H
#define GMMATH_H

#include <math.h>
#include <float.h>
#include <limits.h>
#include <iostream>

#ifdef LINUX
#include <memory.h>
#endif

namespace gmath
{
	template <typename real>
	struct Math
	{
		public:
			/** The acos and asin
			    functions clamp the input argument to [-1,1] to avoid NaN issues
			    when the input is slightly larger than 1 or slightly smaller than -1.
			*/
			static real acos(real x);
			static real asin(real x);
			static real toRadians(real x);
			static real toDegrees(real x);

			static const real EPSILON;
			static const real PI;
			static const real HALFPI;
			static const real MAX;
			static const real MIN;
			static const real SMALLEST;
	};

	#include "gmMath.hpp"
}

#endif // GMMATH_H
