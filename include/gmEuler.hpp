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


/*-----------------------------------------------------------------------------------*/
template<typename real>
Euler<real>::Euler()
{
    x=(real)0.0;
    y=(real)0.0;
    z=(real)0.0;
}
/*-----------------------------------------------------------------------------------*/
template<typename real>
Euler<real>::Euler(const Euler<real>& other)
{
	memcpy(&x, &other.x, 3*sizeof(real));
}
/*-----------------------------------------------------------------------------------*/
template<typename real>
Euler<real>::Euler(const real inX, const real inY, const real inZ)
{
	x=inX; y=inY; z=inZ;
}
/*-----------------------------------------------------------------------------------*/
template<typename real>
Euler<real>::Euler(const Vector3<real>& vec)
{
	memcpy(&x, vec.ptr(), 3*sizeof(real));
}

/*------ Coordinate access ------*/
template <typename real>
real Euler<real>::operator[] (int i) const
{
    if (i>2) {
        throw out_of_range("gmath::Euler:\n\t index out of range");
    }
    return *(&x+i);
}
/*-----------------------------------------------------------------------------------------------------------------*/
template <typename real>
real& Euler<real>::operator[] (int i)
{
    if (i>2) {
        throw out_of_range("gmath::Euler:\n\t index out of range");
    }
    return *(&x+i);
}

/*-----------------------------------------------------------------------------------*/
template <typename real>
bool Euler<real>::operator == (const Euler<real> &other) const
{
    return (
		fabs(x-other.x)<Math<real>::EPSILON &&
		fabs(y-other.y)<Math<real>::EPSILON &&
		fabs(z-other.z)<Math<real>::EPSILON );
}
/*-----------------------------------------------------------------------------------*/
template <typename real>
bool Euler<real>::operator != (const Euler<real> &other) const
{
	return (
		fabs(x-other.x)>Math<real>::EPSILON ||
		fabs(y-other.y)>Math<real>::EPSILON ||
		fabs(z-other.z)>Math<real>::EPSILON );
}

/*-----------------------------------------------------------------------------------*/
template<typename real>
void Euler<real>::set(const real inX, const real inY, const real inZ)
{
	x=inX; y=inY; z=inZ;
}
/*-----------------------------------------------------------------------------------*/
template<typename real>
Euler<real> Euler<real>::toDegrees() const
{
	return Euler<real>(
			Math<real>::toDegrees(x),
			Math<real>::toDegrees(y),
			Math<real>::toDegrees(z)
			);
}
/*-----------------------------------------------------------------------------------*/
template<typename real>
Euler<real> Euler<real>::toRadians() const
{
	return Euler<real>(
			Math<real>::toRadians(x),
			Math<real>::toRadians(y),
			Math<real>::toRadians(z)
			);
}
/*-----------------------------------------------------------------------------------*/
template<typename real>
void Euler<real>::toDegreesInPlace()
{
	x = Math<real>::toDegrees(x);
	y = Math<real>::toDegrees(y);
	z = Math<real>::toDegrees(z);
}
/*-----------------------------------------------------------------------------------*/
template<typename real>
void Euler<real>::toRadiansInPlace()
{
	x = Math<real>::toRadians(x);
	y = Math<real>::toRadians(y);
	z = Math<real>::toRadians(z);
}
/*-----------------------------------------------------------------------------------*/
template<typename real>
Vector3<real> Euler<real>::toVector() const
{
	return Vector3<real>(x, y, z);
}
/*-----------------------------------------------------------------------------------*/
template <typename real>
std::string Euler<real>::toString() const
{
    std::stringstream oss;
    oss << "gmath::Euler(" << x << ", " << y << ", " << z << ");";

    return oss.str();
}
