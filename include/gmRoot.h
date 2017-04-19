/**
@author Daniele Niero
@copyright (c) 2010-17, Daniele Niero

@mainpage

@b GMath is a math library written in C++ with Python wrappers made with [**SWIG**](http://www.swig.org/).

It has been designed with Computer Graphic technical directors in mind, especially Character TDs.
It's primary goal is not to be super fast (although it's not slow) but to be easy to understand and use.


#### License
Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this 
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND @n
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES @n
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. @n
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, @n
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, @n
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) @n
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, @n
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, @n
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE @n
*/

#pragma once

#include <float.h>
#include <math.h>
#include <sstream>
#include <exception>

#ifdef _MSC_VER
	#ifndef INFINITY 
		#define INFINITY (DBL_MAX+DBL_MAX)
	#endif
	#ifndef NAN
		#define NAN (INFINITY-INFINITY)
	#endif
#endif

#ifdef LINUX
	#include <memory.h>
#endif

namespace gmath
{

	class GMathError : public std::exception
	{
	public: 
		static std::string prefix;

	private:
		std::string message;

	public:
		explicit GMathError( const std::string& m ) { message = GMathError::prefix+m; }
		virtual ~GMathError() throw() {};

		virtual const char* what()  const throw()
		{
			return message.c_str();
		}

		std::string getMessage()
		{
			return this->message;
		}

		std::string getPrefix()
		{
			return GMathError::prefix;
		}
		
		void setPrefix(std::string inPref)
		{
			GMathError::prefix = inPref;
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

	double acos(double x);
	double asin(double x);
	double toRadians(double x);
	double toDegrees(double x);

	const double EPSILON = 	1e-08;
    const double PI = 		4.0*atan(1.0);
    const double HALFPI = 	PI*0.5;
    const double MAX = 		DBL_MAX;
    const double MIN = 		-DBL_MAX;
    const double SMALLEST = DBL_MIN;;
}
