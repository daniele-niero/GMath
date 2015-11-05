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

#include "gmEuler.h"

using namespace std;

namespace gmath {
    /*-----------------------------------------------------------------------------------*/
    Euler::Euler(Unit inUnit)
    {
        x=0.0;
        y=0.0;
        z=0.0;

		unit = inUnit;
    }
    /*-----------------------------------------------------------------------------------*/
    Euler::Euler(const Euler& other)
    {
    	memcpy(&x, &other.x, 3*sizeof(double));
		unit = other.unit;
    }
    /*-----------------------------------------------------------------------------------*/
    Euler::Euler(const double inX, const double inY, const double inZ, Unit inUnit)
    {
		x = inX; y = inY; z = inZ;
		unit = inUnit;
    }
    /*-----------------------------------------------------------------------------------*/
    Euler::Euler(const Vector3& vec, Unit inUnit)
    {
    	memcpy(&x, vec.data(), 3*sizeof(double));
		unit = inUnit;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    double* Euler::data()
    {
        return &x;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    const double* Euler::data() const
    {
        return &x;
    }
    /*------ Coordinate access ------*/
    double Euler::operator[] (int i) const
    {
        if (i>2) {
            throw out_of_range("gEuler:\n\t index out of range");
        }
        return *(&x+i);
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    double& Euler::operator[] (int i)
    {
        if (i>2) {
            throw out_of_range("gEuler:\n\t index out of range");
        }
        return *(&x+i);
    }

    /*-----------------------------------------------------------------------------------*/
    bool Euler::operator == (const Euler &other) const
    {
        return (
    		fabs(x-other.x)<EPSILON &&
    		fabs(y-other.y)<EPSILON &&
    		fabs(z-other.z)<EPSILON );
    }
    /*-----------------------------------------------------------------------------------*/
    bool Euler::operator != (const Euler &other) const
    {
    	return (
    		fabs(x-other.x)>EPSILON ||
    		fabs(y-other.y)>EPSILON ||
    		fabs(z-other.z)>EPSILON );
    }

    /*-----------------------------------------------------------------------------------*/
    void Euler::set(const double inX, const double inY, const double inZ)
    {
    	x=inX; y=inY; z=inZ;
    }
    /*-----------------------------------------------------------------------------------*/
    Euler::Unit Euler::getUnit() const
    {
        return unit;
    }
    /*-----------------------------------------------------------------------------------*/
    void Euler::setUnit(Unit inUnit)
    {
        if (unit!=inUnit)
        {
            unit = inUnit;
            if (inUnit==degrees)
            {
                x = gmath::toDegrees(x);
                y = gmath::toDegrees(y);
                z = gmath::toDegrees(z);
            }
            else
            {
                x = gmath::toRadians(x);
                y = gmath::toRadians(y);
                z = gmath::toRadians(z);
            }
        }
    }
    /*-----------------------------------------------------------------------------------*/
    Euler Euler::toDegrees() const
    {
        if (unit==degrees)
        {
            return Euler( (*this) );
        }
        else
        {
    	   return Euler(
    			gmath::toDegrees(x),
			    gmath::toDegrees(y),
			    gmath::toDegrees(z),
                degrees
    			);
        }
    }
    /*-----------------------------------------------------------------------------------*/
    Euler Euler::toRadians() const
    {
    	if (unit==radians)
        {
            return Euler( (*this) );
        }
        else
        {
            return Euler(
			    gmath::toRadians(x),
			    gmath::toRadians(y),
			    gmath::toRadians(z),
                radians
    			);
        }
    }
    /*-----------------------------------------------------------------------------------*/
    Vector3 Euler::toVector() const
    {
    	return Vector3(x, y, z);
    }
    /*-----------------------------------------------------------------------------------*/
    std::string Euler::toString() const
    {
        std::stringstream oss;
        oss << "gmath::Euler(" << x << ", " << y << ", " << z << ");";
        if (unit==degrees)
            oss << " - degrees -";
        else
            oss << " - radians -"; 

        return oss.str();
    }
}