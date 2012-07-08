/*
A math library for 3D graphic.
Copyright (C) 2010-2012 Daniele Niero

Author contact: daniele . niero @ gmail . com

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 3
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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
    oss << "gmath::Euler(" << x << ", " << y << ", " << z << ");" << std::endl;

    return oss.str();
}
