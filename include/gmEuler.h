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


#ifndef GMEULER_H
#define GMEULER_H

#include "gmRoot.h"
#include "gmMath.h"
#include "gmVector3.h"

namespace gmath
{

	template <typename real>
	class Euler
	{
		public:
			Euler();
			Euler(const Euler<real>& other);
			Euler(const real inX, const real inY, const real inZ);
			Euler(const Vector3<real>& vec);

			real x, y, z;

			/*------ coordinate access ------*/
			real operator[] (int i) const;
			real& operator[] (int i);

			/*------ Comparisons ------*/
			bool operator == (const Euler<real> &other) const;
			bool operator != (const Euler<real> &other) const;

			void set(const real inX, const real inY, const real inZ);

			Euler<real> toDegrees() const;
			Euler<real> toRadians() const;

			void toDegreesInPlace();
			void toRadiansInPlace();

			Vector3<real> toVector() const;

			std::string toString() const;
	};

	#include "gmEuler.hpp"

	typedef Euler<float> Eulerf;
	typedef Euler<double> Eulerd;
}


#endif // GMEULER_H
