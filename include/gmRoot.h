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
}


#endif // GMROOT_H
