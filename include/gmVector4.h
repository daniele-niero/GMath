#pragma once

#include <string>
#include <stdexcept>
#include <math.h>
#include "gmRoot.h"

using namespace std;

namespace gmath
{
	class Vector4
	{
	public:
		/*------ constructors ------*/
		Vector4();
		Vector4(double inX, double inY, double inZ, double inW);
		Vector4(const Vector4 & other);
		Vector4(const double* list);

		/*------ properties ------*/
		double x, y, z, w;

		/*------ coordinate access ------*/
		double operator[] (int i) const;
		double& operator[] (int i);

		/** Pointer access for direct copying. */
		double* data();
		const double* data() const;

		/*------ Arithmetic operations ------*/
		Vector4 operator + (const Vector4 & other) const;
		Vector4 operator - (const Vector4 & other) const;
		Vector4 operator - () const;
		Vector4 operator * (double scalar) const;
		Vector4 operator / (double scalar) const;

		/*------ Arithmetic updates ------*/
		Vector4& operator += (const Vector4 & other);
		Vector4& operator -= (const Vector4 & other);
		Vector4& operator *= (double scalar);
		Vector4& operator /= (double scalar);

		/*------ Arithmetic comparisons ------*/
		bool operator == (const Vector4 & other) const;
		bool operator != (const Vector4 & other) const;

		/*------ Arithmetic assignment ------*/
		void operator = (const Vector4 & other);

		/*------ methods ------*/

		/** Set the three properties (x, y, z, w), with the given arguments
			@param inX The wanted value for x
			@param inY The wanted value for y
			@param inZ The wanted value for z
			@param inW The wanted value for w */
		void set(double inX, double inY, double inZ, double inW);

		/** Perform the dot product between this vector and the given vector */
		double dot(const Vector4 & other) const;

		/** Calculate the length of this vector */
		double length() const;
		double squaredLength() const;

		Vector4 normalize() const;
		void normalizeInPlace();

		std::string toString() const;
	};
}
