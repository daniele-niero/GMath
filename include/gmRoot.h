/**
@author Daniele Niero
@copyright (c) 2010-17, Daniele Niero

@mainpage

@b GMath is a math library written in C++ with Python wrappers made with [**SWIG**](http://www.swig.org/).

It has been designed with Computer Graphic technical directors in mind, especially Character TDs.
It's primary goal is not to be super fast (although it's not slow) but to be easy to understand and use.


#### License

MIT License 

Copyright (c) 2013-2017 Daniele Niero

Permission is hereby granted, free of charge, to any person obtaining a copy @n
of this software and associated documentation files (the "Software"), to deal @n
in the Software without restriction, including without limitation the rights @n
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell @n
copies of the Software, and to permit persons to whom the Software is @n
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all @n
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR @n
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, @n
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE @n
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER @n
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, @n
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE @n
SOFTWARE.
*/

#pragma once

#include <float.h>
#include <cmath>
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
    // const double EPSILON   =  1e-08;
    const double PRECISION =  1e-09;
    const double PI        =  4.0*atan(1.0);
    const double HALFPI    =  PI*0.5;
    const double MAX       =  DBL_MAX;
    const double MIN       = -DBL_MAX;
    const double SMALLEST  =  DBL_MIN;

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
    
    enum class Unit {
        degrees,
        radians
    };

    enum class RotationOrder {
        XYZ = 0,
        XZY = 1,
        YXZ = 2,
        YZX = 3,
        ZXY = 4,
        ZYX = 5
    };

    enum class Axis {
        NEGX = -1,
        NEGY = -2,
        NEGZ = -3,
        POSX = 1,
        POSY = 2,
        POSZ = 3
    };

    enum class CartesianPlane {
        XY = 0,
        YZ = 1,
        ZX = 2,

        YX = XY,
        ZY = YZ,
        XZ = ZX
    };

    bool isAxisX(Axis axis);
    bool isAxisY(Axis axis);
    bool isAxisZ(Axis axis);

    double acos(double x);
    double asin(double x);
    double toRadians(double x);
    double toDegrees(double x);

    inline double min(double a, double b)
    {
        return a < b ? a : b;
    }

    inline double max(double a, double b)
    {
        return a > b ? a : b;
    }

    inline double clamp(double value, double lowerBound, double upperBound)
    {
        return min(max(value, lowerBound), upperBound);
    }

    // Taken straight from python math.isclose
    inline bool almostEqual(double x, double y, double relativePrecision=1e-09, double absolutePrecision=0.0)
    {
        return std::fabs(x-y) <= max(relativePrecision * max(std::fabs(x), std::fabs(y)), absolutePrecision);
    }

    inline bool isCloseToZero(double x)
    {
        return almostEqual(x, 0.0);
    }

}
