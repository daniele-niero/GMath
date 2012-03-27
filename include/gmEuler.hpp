/*
A math library for 3D graphic.
Copyright (C) 2010 Daniele Niero

Author contact: nieroinfo@gmail.com

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
template<class TypeReal>
Euler<TypeReal>::Euler()
{}
/*-----------------------------------------------------------------------------------*/
template<class TypeReal>
Euler<TypeReal>::Euler(const Euler<TypeReal>& other)
{
	memcpy(&x, &other.x, 3*sizeof(TypeReal));
}
/*-----------------------------------------------------------------------------------*/
template<class TypeReal>
Euler<TypeReal>::Euler(const TypeReal inX, const TypeReal inY, const TypeReal inZ)
{
	x=inX; y=inY; z=inZ;
}
/*-----------------------------------------------------------------------------------*/
template<class TypeReal>
Euler<TypeReal>::Euler(const Vector3<TypeReal>& vec)
{
	memcpy(&x, vec.ptr(), 3*sizeof(TypeReal));
}

/*-----------------------------------------------------------------------------------*/
template <class TypeReal>
bool Euler<TypeReal>::operator == (const Euler<TypeReal> &other) const
{
    return (
		fabs(x-other.x)<Math<TypeReal>::EPSILON &&
		fabs(y-other.y)<Math<TypeReal>::EPSILON &&
		fabs(z-other.z)<Math<TypeReal>::EPSILON );
}
/*-----------------------------------------------------------------------------------*/
template <class TypeReal>
bool Euler<TypeReal>::operator != (const Euler<TypeReal> &other) const
{
	return (
		fabs(x-other.x)>Math<TypeReal>::EPSILON ||
		fabs(y-other.y)>Math<TypeReal>::EPSILON ||
		fabs(z-other.z)>Math<TypeReal>::EPSILON );
}

/*-----------------------------------------------------------------------------------*/
template<class TypeReal>
void Euler<TypeReal>::set(const TypeReal inX, const TypeReal inY, const TypeReal inZ)
{
	x=inX; y=inY; z=inZ;
}
/*-----------------------------------------------------------------------------------*/
template<class TypeReal>
Euler<TypeReal> Euler<TypeReal>::toDegrees() const
{
	return Euler<TypeReal>(
			Math<TypeReal>::toDegrees(x),
			Math<TypeReal>::toDegrees(y),
			Math<TypeReal>::toDegrees(z)
			);
}
/*-----------------------------------------------------------------------------------*/
template<class TypeReal>
Euler<TypeReal> Euler<TypeReal>::toRadians() const
{
	return Euler<TypeReal>(
			Math<TypeReal>::toRadians(x),
			Math<TypeReal>::toRadians(y),
			Math<TypeReal>::toRadians(z)
			);
}
/*-----------------------------------------------------------------------------------*/
template<class TypeReal>
void Euler<TypeReal>::toDegreesInPlace()
{
	x = Math<TypeReal>::toDegrees(x);
	y = Math<TypeReal>::toDegrees(y);
	z = Math<TypeReal>::toDegrees(z);
}
/*-----------------------------------------------------------------------------------*/
template<class TypeReal>
void Euler<TypeReal>::toRadiansInPlace()
{
	x = Math<TypeReal>::toRadians(x);
	y = Math<TypeReal>::toRadians(y);
	z = Math<TypeReal>::toRadians(z);
}
/*-----------------------------------------------------------------------------------*/
template<class TypeReal>
Vector3<TypeReal> Euler<TypeReal>::toVector() const
{
	return Vector3<TypeReal>(x, y, z);
}
/*-----------------------------------------------------------------------------------*/
template <class TypeReal>
std::string Euler<TypeReal>::toString() const
{
    char buffer[200];
    sprintf( buffer, "gmath::Euler(%f, %f, %f);", x, y, z );
    return buffer;
}
