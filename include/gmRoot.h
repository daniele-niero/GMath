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


#ifndef GMROOT_H
#define GMROOT_H

#ifdef _MSC_VER
#define INFINITY (DBL_MAX+DBL_MAX)
#define NAN (INFINITY-INFINITY)
#endif

#include <math.h>
#include <sstream>
#include <exception>


namespace gmath
{

	class GMathError : public std::exception
	{
	private:
		std::string message;

	public:
		explicit GMathError( const std::string& m ) { message = m; }
		virtual ~GMathError() throw() {};

		virtual const char* what()  const throw()
		{
			return message.c_str();
		}
	};


	enum RotationOrder{
		XYZ = 0,
		XZY = 1,
		YXZ = 2,
		YZX = 3,
		ZXY = 4,
		ZYX = 5
	};


	enum Axis{
		NEGX = -1,
		NEGY = -2,
		NEGZ = -3,
		POSX = 1,
		POSY = 2,
		POSZ = 3
	};
}


#endif // GMROOT_H
