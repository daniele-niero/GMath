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

#pragma once

#include "gmVector3.h"
#include "gmQuaternion.h"
#include "gmMatrix4.h"

namespace gmath
{	
	/** The Xfo type represents a 3D transform. 
		It uses a Vector3 for translation and scaling as well as a Quaternion for its rotation. 
		It was inspired by FabricEngine's own Xfo type 

		@seealso Quat, Vec3, Euler, Mat44, Mat33 */
	class Xfo
	{
	public:
		/*------ properties ------*/
		Quaternion ori;
		Vector3 tr;
		Vector3 sc;

		/*------ constructors ------*/
		Xfo();
		Xfo(const Xfo& other);
		Xfo(const Vector3 & tr);
		Xfo(const Quaternion & ori);
		Xfo(const Vector3 & tr, const Quaternion & ori);
		Xfo(const Quaternion & ori, const Vector3 & tr, const Vector3 & sc);
		Xfo(const Matrix4 & mat);
		Xfo(const double & eulerX, const double & eulerY, const double & eulerZ, 
		    const double & trX, const double & trY, const double & trZ,
		    const double & scX, const double & scY, const double & scZ);

		/*------ Arithmetic operations ------*/
		Xfo operator * (const Xfo & other) const;

		/*------ Arithmetic updates ------*/
		Xfo& operator *= (const Xfo & other);

		/*------ Arithmetic comparisons ------*/
		bool operator == (const Xfo & other) const;
		bool operator != (const Xfo & other) const;

		/*------ Arithmetic assignment ------*/
		void operator = (const Xfo & other);

		/*------ methods ------*/
		void setToIdentity();
		void fromMatrix4(const Matrix4 & mat);
		Matrix4 toMatrix4() const;
		Vector3 transformVector(const Vector3 & vec) const;
		Xfo inverse() const;
		Xfo& inverseInPlace();
		Vector3 inverseTransformVector(const Vector3 & vec) const;
		Xfo slerp(const Xfo & other, const double & t) const;
		Xfo& slerpInPlace(const Xfo & other, const double & t);
		double distanceTo(const Xfo & other) const;

		std::string toString() const;
	};
}