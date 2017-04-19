#pragma once

#include <math.h>
#include <float.h>
#include <limits.h>
#include <iostream>

#ifdef LINUX
#include <memory.h>
#endif

namespace gmath
{
	template <typename real>
	struct Math
	{
		public:
			/** The acos and asin
			    functions clamp the input argument to [-1,1] to avoid NaN issues
			    when the input is slightly larger than 1 or slightly smaller than -1.
			*/
			static real acos(real x);
			static real asin(real x);
			static real toRadians(real x);
			static real toDegrees(real x);

			static const real EPSILON;
			static const real PI;
			static const real HALFPI;
			static const real MAX;
			static const real MIN;
			static const real SMALLEST;
	};
}
