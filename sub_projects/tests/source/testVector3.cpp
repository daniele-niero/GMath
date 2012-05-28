/*
A math library for 3D graphic.
Copyright (C) 2010-2012 Daniele Niero

Author contact: daniele . niero @ gmail . com

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 3
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <math.h>
#include <iostream>
#include "testVector3.h"
#include "gmMath.h"
#include "gmVector3.h"

using namespace std;

void testVec3_Constructors()
{
	// explicit constructor
	gmath::Vector3f vec1(1.1, 2.2, 3.3);
	ASSERT (vec1.x==1.1f);
	ASSERT (vec1[1]==2.2f);
	ASSERT (vec1[2]==3.3f);

	// construct with a list
	float list[3] = {0.0, 1.0, 2.0};
	gmath::Vector3f vec2(list);
	ASSERT (vec2[0]==0.0f);
	ASSERT (vec2[1]==1.0f);
	ASSERT (vec2[2]==2.0f);

	// copy constructor
	gmath::Vector3f vec3(vec1);
	ASSERT (vec3 == vec1);
}

void testVec3_CoordianteAccess()
{
	gmath::Vector3f vec(0.2, 1.0, 2.0);

	ASSERT (vec[0]==0.2f); ASSERT (vec.x==0.2f);
	ASSERT (vec[1]==1.0f); ASSERT (vec.y==1.0f);
	ASSERT (vec[2]==2.0f); ASSERT (vec.z==2.0f);
}

void testVec3_ArithmeticOperations()
{
	gmath::Vector3d vec1(0.0, 1.0, 2.0);
	gmath::Vector3d vec2(0.5, 1.5, 2.5);
	gmath::Vector3d vec3;

	vec3 = vec1+vec2;
	ASSERT(vec3.x==0.5); ASSERT(vec3.y==2.5); ASSERT(vec3.z==4.5);

	vec3.set(0.0, 0.0, 0.0);
	vec3 = vec1-vec2;
	ASSERT(vec3.x==-0.5); ASSERT(vec3.y==-0.5); ASSERT(vec3.z==-0.5);

	vec3.set(0.0, 0.0, 0.0);
	vec3 = vec2*3.0;
	ASSERT(vec3.x==1.5); ASSERT(vec3.y==4.5); ASSERT(vec3.z==7.5);

	vec3.set(0.0, 0.0, 0.0);
	vec3 = vec2/2.0;
	ASSERT(vec3.x==0.25); ASSERT(vec3.y==0.75); ASSERT(vec3.z==1.25);
	vec3 = vec1/0.0;
	ASSERT(isnan(vec3.x)); ASSERT(isnan(vec3.y)); ASSERT(isnan(vec3.z));
}

void testVec3_ArithmeticUpdates()
{
	gmath::Vector3d vec1(1.1, 2.2, 3.3);
	gmath::Vector3d vec2(2.0, 2.0, 2.0);

	vec1 += vec2;
	ASSERT(vec1.x==3.1); ASSERT(vec1.y==4.2); ASSERT(vec1.z==5.3);

	vec1 -= vec2;
	ASSERT(vec1.x==1.1); ASSERT(vec1.y==2.2); ASSERT(vec1.z==3.3);

	vec1 *= 2.0;
	ASSERT(vec1.x==2.2); ASSERT(vec1.y==4.4); ASSERT(vec1.z==6.6);

	vec1 /= 2.0;
	ASSERT(vec1.x==1.1); ASSERT(vec1.y==2.2); ASSERT(vec1.z==3.3);
	vec1 /= 0.0f;
	ASSERT(isnan(vec1.x)); ASSERT(isnan(vec1.y)); ASSERT(isnan(vec1.z));
}

void testVec3_Comparisons()
{
	gmath::Vector3f vec1(0.0, 1.0, 2.0);
	gmath::Vector3f vec2(0.0, 1.0, 2.0);
	gmath::Vector3f vec3(0.123, 1.0, 2.0);

	ASSERT(vec1==vec2);
	ASSERT(vec1!=vec3);
}

void testVec3_Assignment()
{
	gmath::Vector3f vec1(0.0, 1.0, 2.0);
	gmath::Vector3f vec2;

	vec2 = vec1;
	ASSERT(vec2==vec1)

	vec1.x = 100.0;
	ASSERT(vec2!=vec1);
}

void testVec3_Set()
{
	gmath::Vector3<float> vec;
	vec.set(1.0f, 3.5f, 5.23f);
	ASSERT(vec.x==1.0f); ASSERT(vec.y==3.5f); ASSERT(vec.z==5.23f);
}

void testVec3_Duplicate()
{
	gmath::Vector3d vec1(0.0, 1.0, 2.0);
	gmath::Vector3d vec2;

	vec2 = vec1.duplicate();
	ASSERT (vec1.x == vec2.x);
	ASSERT (vec1.y == vec2.y);
	ASSERT (vec1.z == vec2.z);

	vec1.x = 123456789.123456789;
	ASSERT (vec1.x != vec2.x);
}

void testVec3_Cross()
{
	gmath::Vector3d vec1(0.5, 0.5, 0.0);
	gmath::Vector3d vec2(0.0, 0.0, 0.5);

	gmath::Vector3d crossVec;
	crossVec = vec1.cross(vec2);
	ASSERT(crossVec.x==0.25); ASSERT(crossVec.y==-0.25); ASSERT(crossVec.z==0.0);

	crossVec = vec2.cross(vec1);
	ASSERT(crossVec.x==-0.25); ASSERT(crossVec.y==0.25); ASSERT(crossVec.z==0.0);
}

void testVec3_CrossNormalized()
{
	gmath::Vector3d vec1(0.5, 0.5, 0.0);
	gmath::Vector3d vec2(0.0, 0.0, 0.5);
	gmath::Vector3d checkVec(1.0, -1.0, 0.0);
	checkVec.normalizeInPlace();

	gmath::Vector3d crossVec;
	crossVec = vec1.crossNormalized(vec2);
	ASSERT(crossVec==checkVec);

	checkVec *= -1.0;
	crossVec = vec2.crossNormalized(vec1);
	ASSERT(crossVec==checkVec);
}

void testVec3_Dot()
{
	gmath::Vector3<float> vec1(1.0, 1.0, 0.0);
	gmath::Vector3<float> vec2(1.0, 0.0, 0.0);

	float dot = vec1.dot(vec2);
	ASSERT(dot==1.0f);

	gmath::Vector3f checkVec(1.0f, 1.0f, 0.0f);
	checkVec.normalizeInPlace();
	dot = vec1.normalize().dot(vec2);
	ASSERT(dot==checkVec.x);
}


void testVec3_Reflection()
{
	gmath::Vector3d vec1(0.0, 1.0, 0.0);
	gmath::Vector3d vec2(1.0, 1.0, 1.0);
	gmath::Vector3d reflection = vec2.reflect(vec1);

	ASSERT( reflection.x == -1.0 );
	ASSERT( reflection.y == 1.0 );
	ASSERT( reflection.z == -1.0 );

	reflection.reflectInPlace(vec1);

	ASSERT( reflection.x == 1.0 );
	ASSERT( reflection.y == 1.0 );
	ASSERT( reflection.z == 1.0 );
}

void testVec3_Refraction()
{
	gmath::Vector3d vec1(0.0, 1.0, 0.0);
	gmath::Vector3d vec2(1.0, 1.0, 1.0);
	gmath::Vector3d ref = vec2.refract(vec1, 0.5);

	ASSERT( ref.x == 0.5 );
	ASSERT( ref.y == -1.0 );
	ASSERT( ref.z == 0.5 );

	vec2.refractInPlace(vec1, 0.5);

	ASSERT( vec2.x == 0.5 );
	ASSERT( vec2.y == -1.0 );
	ASSERT( vec2.z == 0.5 );
}


void testVec3_SpecialVectors()
{
	ASSERT( gmath::Vector3d::XAXIS == gmath::Vector3d(1.0, 0.0, 0.0) );
	ASSERT( gmath::Vector3d::YAXIS == gmath::Vector3d(0.0, 1.0, 0.0) );
	ASSERT( gmath::Vector3d::ZAXIS == gmath::Vector3d(0.0, 0.0, 1.0) );

	ASSERT( gmath::Vector3f::XAXIS == gmath::Vector3f(1.0f, 0.0f, 0.0f) );
	ASSERT( gmath::Vector3f::YAXIS == gmath::Vector3f(0.0f, 1.0f, 0.0f) );
	ASSERT( gmath::Vector3f::ZAXIS == gmath::Vector3f(0.0f, 0.0f, 1.0f) );
}


void testVector3()
{
	cout << endl << "--- Test Vector3 ---" << endl;
	TEST_CHECK(testVec3_Constructors);
	TEST_CHECK(testVec3_CoordianteAccess);
	TEST_CHECK(testVec3_ArithmeticOperations);
	TEST_CHECK(testVec3_ArithmeticUpdates);
	TEST_CHECK(testVec3_Comparisons);
	TEST_CHECK(testVec3_Assignment);
	TEST_CHECK(testVec3_Set);
	TEST_CHECK(testVec3_Duplicate);
	TEST_CHECK(testVec3_Cross);
	TEST_CHECK(testVec3_CrossNormalized);
	TEST_CHECK(testVec3_Dot);
	TEST_CHECK(testVec3_Reflection);
	TEST_CHECK(testVec3_Refraction);
	TEST_CHECK(testVec3_SpecialVectors);
}




