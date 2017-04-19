#pragma once

#include "gmRoot.h"
#include "gmVector3.h"

namespace gmath
{
	class Euler
	{
	public:
		enum Unit {
			degrees,
			radians
		};

		Euler(Unit inUnit=radians);
		Euler(const Euler& other);
		Euler(const double inX, const double inY, const double inZ, Unit inUnit=radians);
		Euler(const Vector3& vec, Unit inUnit=radians);

		double x, y, z;

		/** Pointer access for direct copying. */
		double* data();
		const double* data() const;

		/*------ coordinate access ------*/
		double operator[] (int i) const;
		double& operator[] (int i);

		/*------ Comparisons ------*/
		bool operator == (const Euler &other) const;
		bool operator != (const Euler &other) const;

		void set(const double inX, const double inY, const double inZ);

		Unit getUnit() const;
		/**
		 set the unit and change the data accordingly, in place
		 */
		void setUnit(Unit inUnit);

		Euler toDegrees() const;
		Euler toRadians() const;

		Vector3 toVector() const;

		std::string toString() const;

	private:
		Unit unit;
	};
}