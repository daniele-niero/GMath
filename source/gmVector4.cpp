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

#include "gmVector4.h"

using namespace std;

namespace gmath {
    /*-----------------------------------------------------------------------------------------------------------------*/
    /*------ Constructors ------*/
    Vector4::Vector4()
    {
        x=0.0;
        y=0.0;
        z=0.0;
        w=0.0;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    Vector4::Vector4(double inX, double inY, double inZ, double inW)
    {
        x = inX;
        y = inY;
        z = inZ;
        w = inW;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    Vector4::Vector4(const Vector4 & other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    Vector4::Vector4(const double* list)
    {
        x = list[0];
        y = list[1];
        z = list[2];
        w = list[3];
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    /*------ Coordinates access ------*/
    double Vector4::operator[] (int i) const
    {
        if (i>3){
            throw out_of_range("gVector4: index out of range");
        }
        return *(&x+i);
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    double& Vector4::operator[] (int i)
    {
        if (i==0){
            throw out_of_range("gVector4: index out of range");
        }
        return *(&x+i);
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    double* Vector4::data()
    {
    	return &x;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    const double* Vector4::data() const
    {
    	return &x;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    /*------ Arithmetic operations ------*/
    Vector4 Vector4::operator + (const Vector4 & other) const
    {
        Vector4 newVector4(x+other.x, y+other.y, z+other.z, w+other.w);

        return newVector4;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    Vector4 Vector4::operator - (const Vector4 & other) const
    {
        Vector4 newVector4(x-other.x, y-other.y, z-other.z, w-other.w);
        return newVector4;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    Vector4 Vector4::operator - () const
    {
        Vector4 newVector4(-x, -y, -z, -w);
        return newVector4;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    Vector4 Vector4::operator * (double scalar) const
    {
        Vector4 newVector4(x*scalar, y*scalar, z*scalar, w*scalar);

        return newVector4;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    Vector4 Vector4::operator / (double scalar) const
    {
        Vector4 newVector4;
        if (scalar == 0.0)
        {
            newVector4.x = NAN;
            newVector4.y = NAN;
            newVector4.z = NAN;
            newVector4.w = NAN;
        }
        else
        {
            newVector4.x = x/scalar;
            newVector4.y = y/scalar;
            newVector4.z = z/scalar;
            newVector4.w = w/scalar;
        }

        return newVector4;
    }
    /*------ Arithmetic updates ------*/
    /*-----------------------------------------------------------------------------------------------------------------*/
    Vector4& Vector4::operator += (const Vector4 & other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    Vector4& Vector4::operator -= (const Vector4 & other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    Vector4& Vector4::operator *= (double scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    Vector4& Vector4::operator /= (double scalar)
    {
        if (scalar == 0.0)
        {
            x = NAN;
            y = NAN;
            z = NAN;
            w = NAN;
        }
        else
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            w /= scalar;
        }
        return *this;
    }
    /*------ Comparisons ------*/
    /*-----------------------------------------------------------------------------------------------------------------*/
    bool Vector4::operator == (const Vector4 & other) const
    {
        return (fabs(x-other.x) < gmath::EPSILON && 
                fabs(y-other.y) < gmath::EPSILON && 
                fabs(z-other.z) < gmath::EPSILON &&
                fabs(w-other.w) < gmath::EPSILON);
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    bool Vector4::operator != (const Vector4 & other) const
    {
        return (fabs(x-other.x) > gmath::EPSILON || 
                fabs(y-other.y) > gmath::EPSILON || 
                fabs(z-other.z) > gmath::EPSILON ||
                fabs(w-other.w) < gmath::EPSILON);
    }
    /*------ Assignments ------*/
    /*-----------------------------------------------------------------------------------------------------------------*/
    void Vector4::operator = (const Vector4 & other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.z;
    }
    /*------ Methods ------*/
    void Vector4::set(double inX, double inY, double inZ, double inW)
    {
        x = inX;
        y = inY;
        z = inZ;
        w = inW;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    double Vector4::dot(const Vector4 & other) const
    {
        return x*other.x + y*other.y + z*other.z + w*other.w;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    double Vector4::length() const
    {
        double dot = x*x + y*y + z*z + w*w;
        return sqrt( dot );
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    double Vector4::squaredLength() const
    {
        return x*x + y*y + z*z + w*w;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    Vector4 Vector4::normalize() const
    {
        double len = length();

        double nlen;
        if (len < gmath::EPSILON)
        {
            nlen = 1.0;
        }
        else
        {
            nlen = 1.0/len;
        }

        return Vector4(x*nlen, y*nlen, z*nlen, w*nlen);
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    void Vector4::normalizeInPlace()
    {
        double len = length();
        
        double nlen;
        if (len < gmath::EPSILON)
        {
            nlen = 1.0;
        }
        else
        {
            nlen = 1.0/len;
        }

        x *= nlen;
        y *= nlen;
        z *= nlen;
        w *= nlen;
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
    std::string Vector4::toString() const
    {
        std::stringstream oss;
        oss << "gmath::Vector4(" << x << ", " << y << ", " << z << ", " << w << ");";

        return oss.str();
    }
    /*-----------------------------------------------------------------------------------------------------------------*/
}