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

#include "../include/gmVector3.h"

namespace gmath
{
	template<> const Vector3<float> Vector3<float>::XAXIS(1.0f, 0.0f, 0.0f);
	template<> const Vector3<float> Vector3<float>::YAXIS(0.0f, 1.0f, 0.0f);
	template<> const Vector3<float> Vector3<float>::ZAXIS(0.0f, 0.0f, 1.0f);

	template<> const Vector3<double> Vector3<double>::XAXIS(1.0, 0.0, 0.0);
	template<> const Vector3<double> Vector3<double>::YAXIS(0.0, 1.0, 0.0);
	template<> const Vector3<double> Vector3<double>::ZAXIS(0.0, 0.0, 1.0);


	template<> const Vector3<float> Vector3<float>::N_XAXIS(-1.0f, 0.0f, 0.0f);
	template<> const Vector3<float> Vector3<float>::N_YAXIS(0.0f, -1.0f, 0.0f);
	template<> const Vector3<float> Vector3<float>::N_ZAXIS(0.0f, 0.0f, -1.0f);

	template<> const Vector3<double> Vector3<double>::N_XAXIS(-1.0, 0.0, 0.0);
	template<> const Vector3<double> Vector3<double>::N_YAXIS(0.0, -1.0, 0.0);
	template<> const Vector3<double> Vector3<double>::N_ZAXIS(0.0, 0.0, -1.0);


	template<> const Vector3<double> Vector3<double>::ZERO(0.0, 0.0, 0.0);
	template<> const Vector3<float> Vector3<float>::ZERO(0.0f, 0.0f, 0.0f);
}
