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
#include "gmXfo.h"

using namespace std;

namespace gmath
{
	/*------ Constructors ------*/
	Xfo::Xfo()
	{
		ori = Quaternion();
		tr = Vector3();
		sc = Vector3(1.0, 1.0, 1.0);
	}

	Xfo::Xfo(const Xfo& other) 
	{
		ori = other.ori;
		tr = other.tr;
		sc = other.sc;
	}

	Xfo::Xfo(const Vector3 & tr)
	{
		this->ori = Quaternion();
		this->tr = tr;
		this->sc = Vector3();
	}

	Xfo::Xfo(const Quaternion & ori)
	{
		this->ori = ori;
		this->tr = Vector3();
		this->sc = Vector3();
	}

	Xfo::Xfo(const Vector3 & tr, const Quaternion & ori)
	{
		this->ori = ori;
		this->tr = tr;
		this->sc = Vector3();
	}

	Xfo::Xfo(const Quaternion & ori, const Vector3 & tr, const Vector3 & sc)
	{
		this->ori = ori;
		this->tr = tr;
		this->sc = sc;
	}

	Xfo::Xfo(const Matrix4 & mat)
	{
		ori = mat.toQuaternion();
		tr = mat.getPosition();
		sc = mat.getScale();
	}

	Xfo::Xfo(const double & eulerX, const double & eulerY, const double & eulerZ, 
	         const double & trX, const double & trY, const double & trZ,
	         const double & scX, const double & scY, const double & scZ)
	{
		ori = Quaternion(eulerX, eulerY, eulerZ);
		tr = Vector3(trX, trY, trZ);
		sc = Vector3(scX, scY, scZ);
	}

	/*------ Arithmetic operations ------*/
	Xfo Xfo::operator * (const Xfo & other) const
	{
		if(this->sc.x != this->sc.y || this->sc.x != this->sc.z)
		{
			double relativePrecision = abs(this->sc.x)*EPSILON*10.0;
			if( abs(this->sc.x - this->sc.y) > relativePrecision || abs(this->sc.x - this->sc.z) > relativePrecision ) 
				throw GMathError("Xfo operator *: Cannot multiply to xfos when having non-uniform scaling without causing shearing. Use Matrix4s instead.");
		}

		Xfo result;
		result.tr = this->tr + other.ori * (this->sc * other.tr);
		result.ori = this->ori * other.ori;
		result.ori.normalizeInPlace();
		result.sc = this->sc * other.sc;
		return result;
	}

	/*------ Arithmetic updates ------*/
	Xfo& Xfo::operator *= (const Xfo & other)
	{
		if(this->sc.x != this->sc.y || this->sc.x != this->sc.z)
		{
			double relativePrecision = abs(this->sc.x)*EPSILON*10.0;
			if( abs(this->sc.x - this->sc.y) > relativePrecision || abs(this->sc.x - this->sc.z) > relativePrecision ) 
				throw GMathError("Xfo operator *: Cannot multiply to xfos when having non-uniform scaling without causing shearing. Use Matrix4s instead.");
		}

		this->tr += other.ori * (this->sc * other.tr);
		this->ori *= other.ori;
		this->ori.normalizeInPlace();
		this->sc *= other.sc;
		return *this;
	}

	/*------ Arithmetic comparisons ------*/
	bool Xfo::operator == (const Xfo & other) const
	{
		return (ori==other.ori && tr==other.tr && sc==other.sc);
	}

	bool Xfo::operator != (const Xfo & other) const
	{
		return (ori!=other.ori && tr!=other.tr && sc!=other.sc);
	}

	/*------ Arithmetic assignment ------*/
	void Xfo::operator = (const Xfo & other) 
	{
		ori = other.ori;
		tr = other.tr;
		sc = other.sc;
	}

	/*------ methods ------*/
	void Xfo::setToIdentity()
	{
		ori.set(0.0, 0.0, 0.0, 1.0);
		tr.set(0.0, 0.0, 0.0);
		sc.set(1.0, 1.0, 1.0);
	}

	void Xfo::fromMatrix4(const Matrix4 & mat)
	{
		ori = mat.toQuaternion();
		tr = mat.getPosition();
		sc = mat.getScale();
	}

	Matrix4 Xfo::toMatrix4() const
	{
		Matrix4 result(ori, tr);
		result.setScale(sc);
		return result;
	}

	Vector3 Xfo::transformVector(const Vector3 & vec) const
	{
		return ori * (vec*sc) + tr;
	}

	Xfo Xfo::inverse() const
	{
		if(this->sc.x != this->sc.y || this->sc.x != this->sc.z)
		{
			double relativePrecision = abs(this->sc.x)*EPSILON*10.0;
			if( abs(this->sc.x - this->sc.y) > relativePrecision || abs(this->sc.x - this->sc.z) > relativePrecision ) 
				throw GMathError("Xfo operator *: Cannot multiply to xfos when having non-uniform scaling without causing shearing. Use Matrix4s instead.");
		}

		Xfo result;
		result.ori = ori.inverse();
		result.tr = tr * -1.0;
		result.sc = sc * -1.0;
		return result;
	}

	Xfo& Xfo::inverseInPlace()
	{
		if(this->sc.x != this->sc.y || this->sc.x != this->sc.z)
		{
			double relativePrecision = abs(this->sc.x)*EPSILON*10.0;
			if( abs(this->sc.x - this->sc.y) > relativePrecision || abs(this->sc.x - this->sc.z) > relativePrecision ) 
				throw GMathError("Xfo operator *: Cannot multiply to xfos when having non-uniform scaling without causing shearing. Use Matrix4s instead.");
		}

		ori.inverseInPlace();
		tr *= -1.0;
		sc *= -1.0;
		return *this;
	}

	Vector3 Xfo::inverseTransformVector(const Vector3 & vec) const
	{
		return this->inverse().transformVector(vec);
	}

	Xfo Xfo::slerp(const Xfo & other, const double & t) const
	{
		Xfo result;
		result.ori = ori.slerp(other.ori, t);
		result.tr = tr.linearInterpolate(other.tr, t);
		result.sc = sc.linearInterpolate(other.sc, t);
		return result;
	}

	Xfo& Xfo::slerpInPlace(const Xfo & other, const double & t)
	{
		Xfo result;
		ori.slerpInPlace(ori, other.ori, t);
		tr.linearInterpolateInPlace(other.tr, t);
		sc.linearInterpolateInPlace(other.sc, t);
		return *this;
	}

	double Xfo::distanceTo(const Xfo & other) const
	{
		return tr.distance(other.tr);
	}

	std::string Xfo::toString() const
	{
		std::stringstream oss;
		oss << "gmath::Xfo(ori:" << ori.x << ", " << ori.y << ", " << ori.z << ", " << ori.w << std::endl;
		oss << "           tr :" << tr.x  << ", " << tr.y  << ", " << tr.z  << std::endl;
		oss << "           sc :" << sc.x  << ", " << sc.y  << ", " << sc.z  << ");";

		return oss.str();
	}
}