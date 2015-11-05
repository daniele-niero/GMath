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

#include "gmRoot.h"

namespace gmath
{
	std::string GMathError::prefix = "GMathError: ";

    // const double EPSILON = 1e-08;
    // const double PI = 4.0*atan(1.0);
    // const double HALFPI = PI*0.5;
    // const double MAX = DBL_MAX;
    // const double MIN = -DBL_MAX;
    // const double SMALLEST = DBL_MIN;


    double acos (double x)
    {
        if (-(double)1 < x) {
            if (x < (double)1) {
                return (double) ::acos((double)x);
            }
            else {
                return (double)0;
            }
        }
        else {
            return PI;
        }
    }

    double asin (double x)
    {
        if (-(double)1 < x) {
            if (x < (double)1) {
                return (double) ::asin((double)x);
            }
            else {
                return HALFPI;
            }
        }
        else {
            return -HALFPI;
        }
    }

    double toRadians(double x)
    {
        return x*(PI/(double)180.0);
    }

    double toDegrees(double x)
    {
        return x*((double)180.0/PI);
    }
}