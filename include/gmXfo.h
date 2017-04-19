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