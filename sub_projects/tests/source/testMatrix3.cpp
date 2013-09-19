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

#include "tester.h"
#include "testMatrix3.h"
#include <iostream>
#include "gmMath.h"
#include "gmMatrix3.h"

using namespace std;
using namespace gmath;

void testMatrix3_Constructors()
{
	Matrix3<float> mat1(1.0, 0.0, 0.0,
						0.0, 1.0, 0.0,
						0.0, 0.0, 1.0);
	ASSERT(mat1==Matrix3f::IDENTITY);

	Matrix3<double> mat2(1.0, 0.0, 0.0,
						 0.0, 1.0, 0.0,
						 0.0, 0.0, 1.0);
	ASSERT(mat2==Matrix3d::IDENTITY);

	Matrix3<float> mat3(Vector3<float>(1.0, 0.0, 0.0),
						Vector3<float>(0.0, 1.0, 0.0),
						Vector3<float>(0.0, 0.0, 1.0));
	ASSERT(mat3==mat1);

	Matrix3<double> mat4(Vector3<double>(1.0, 0.0, 0.0),
						 Vector3<double>(0.0, 1.0, 0.0),
						 Vector3<double>(0.0, 0.0, 1.0));
	ASSERT(mat4==mat2);

	Matrix3f mat5(mat1);
	ASSERT(mat1==mat5);

	double list[9] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
	Matrix3d mat6(list);
	for (unsigned int i=0; i<9; i++)
	{
		ASSERT(mat6.data[i]==list[i]);
	}
}

void testMatrix3_ArithmeticOperations()
{
	Matrix3f m1(1.0, 2.0, 3.0,
				4.0, 5.0, 6.0,
				7.0, 8.0, 9.0);
	Matrix3f m2(2.0, 2.0, 2.0,
				2.0, 2.0, 2.0,
				2.0, 2.0, 2.0);
	Matrix3f m3;

	// Sum
	m3 = m1+m2;
	ASSERT(m3.data[0] == 3.0); ASSERT(m3.data[1] == 4.0);  ASSERT(m3.data[2] == 5.0);
	ASSERT(m3.data[3] == 6.0); ASSERT(m3.data[4] == 7.0);  ASSERT(m3.data[5] == 8.0);
	ASSERT(m3.data[6] == 9.0); ASSERT(m3.data[7] == 10.0); ASSERT(m3.data[8] == 11.0);

	m3 += m2;
	ASSERT(m3.data[0] == 5.0); ASSERT(m3.data[1] == 6.0); ASSERT(m3.data[2] == 7.0);
	ASSERT(m3.data[3] == 8.0); ASSERT(m3.data[4] == 9.0); ASSERT(m3.data[5] == 10.0);
	ASSERT(m3.data[6] == 11.0); ASSERT(m3.data[7] == 12.0); ASSERT(m3.data[8] == 13.0);

	m3 = m1+2.0;
	ASSERT(m3.data[0] == 3.0); ASSERT(m3.data[1] == 4.0);  ASSERT(m3.data[2] == 5.0);
	ASSERT(m3.data[3] == 6.0); ASSERT(m3.data[4] == 7.0);  ASSERT(m3.data[5] == 8.0);
	ASSERT(m3.data[6] == 9.0); ASSERT(m3.data[7] == 10.0); ASSERT(m3.data[8] == 11.0);

	m3 += 3.0;
	ASSERT(m3.data[0] == 6.0); ASSERT(m3.data[1] == 7.0); ASSERT(m3.data[2] == 8.0);
	ASSERT(m3.data[3] == 9.0); ASSERT(m3.data[4] == 10.0); ASSERT(m3.data[5] == 11.0);
	ASSERT(m3.data[6] == 12.0); ASSERT(m3.data[7] == 13.0); ASSERT(m3.data[8] == 14.0);

	// Subtraction
	m3 = m1-m2;
	ASSERT(m3.data[0] == -1.0); ASSERT(m3.data[1] == 0.0);  ASSERT(m3.data[2] == 1.0);
	ASSERT(m3.data[3] == 2.0); ASSERT(m3.data[4] == 3.0);  ASSERT(m3.data[5] == 4.0);
	ASSERT(m3.data[6] == 5.0); ASSERT(m3.data[7] == 6.0); ASSERT(m3.data[8] == 7.0);

	m3 -= m2;
	ASSERT(m3.data[0] == -3.0); ASSERT(m3.data[1] == -2.0); ASSERT(m3.data[2] == -1.0);
	ASSERT(m3.data[3] == 0.0); ASSERT(m3.data[4] == 1.0); ASSERT(m3.data[5] == 2.0);
	ASSERT(m3.data[6] == 3.0); ASSERT(m3.data[7] == 4.0); ASSERT(m3.data[8] == 5.0);

	m3 = m1-2.0;
	ASSERT(m3.data[0] == -1.0); ASSERT(m3.data[1] == 0.0);  ASSERT(m3.data[2] == 1.0);
	ASSERT(m3.data[3] == 2.0); ASSERT(m3.data[4] == 3.0);  ASSERT(m3.data[5] == 4.0);
	ASSERT(m3.data[6] == 5.0); ASSERT(m3.data[7] == 6.0); ASSERT(m3.data[8] == 7.0);

	m3 -= 3.0;
	ASSERT(m3.data[0] == -4.0); ASSERT(m3.data[1] == -3.0); ASSERT(m3.data[2] == -2.0);
	ASSERT(m3.data[3] == -1.0); ASSERT(m3.data[4] == 0.0); ASSERT(m3.data[5] == 1.0);
	ASSERT(m3.data[6] == 2.0); ASSERT(m3.data[7] == 3.0); ASSERT(m3.data[8] == 4.0);

	// Multiply
	m3 = m1*m2;
	ASSERT(m3.data[0] == 12.0); ASSERT(m3.data[1] == 12.0); ASSERT(m3.data[2] == 12.0);
	ASSERT(m3.data[3] == 30.0); ASSERT(m3.data[4] == 30.0); ASSERT(m3.data[5] == 30.0);
	ASSERT(m3.data[6] == 48.0); ASSERT(m3.data[7] == 48.0); ASSERT(m3.data[8] == 48.0);

	m3 = m1;
	m3 *= m2;
	ASSERT(m3.data[0] == 12.0); ASSERT(m3.data[1] == 12.0); ASSERT(m3.data[2] == 12.0);
	ASSERT(m3.data[3] == 30.0); ASSERT(m3.data[4] == 30.0); ASSERT(m3.data[5] == 30.0);
	ASSERT(m3.data[6] == 48.0); ASSERT(m3.data[7] == 48.0); ASSERT(m3.data[8] == 48.0);

	m3 = m1*3.0;
	ASSERT(m3.data[0] == 3.0); ASSERT(m3.data[1] == 6.0); ASSERT(m3.data[2] == 9.0);
	ASSERT(m3.data[3] == 12.0); ASSERT(m3.data[4] == 15.0); ASSERT(m3.data[5] == 18.0);
	ASSERT(m3.data[6] == 21.0); ASSERT(m3.data[7] == 24.0); ASSERT(m3.data[8] == 27.0);

	m3 *= 2.0;
	ASSERT(m3.data[0] == 6.0); ASSERT(m3.data[1] == 12.0); ASSERT(m3.data[2] == 18.0);
	ASSERT(m3.data[3] == 24.0); ASSERT(m3.data[4] == 30.0); ASSERT(m3.data[5] == 36.0);
	ASSERT(m3.data[6] == 42.0); ASSERT(m3.data[7] == 48.0); ASSERT(m3.data[8] == 54.0);

	// Division
	m3 = m1/2.0;
	ASSERT(m3.data[0] == 0.5); ASSERT(m3.data[1] == 1.0); ASSERT(m3.data[2] == 1.5);
	ASSERT(m3.data[3] == 2.0); ASSERT(m3.data[4] == 2.5); ASSERT(m3.data[5] == 3.0);
	ASSERT(m3.data[6] == 3.5); ASSERT(m3.data[7] == 4.0); ASSERT(m3.data[8] == 4.5);

	m3 /= 2.0;
	ASSERT(m3.data[0] == 0.25); ASSERT(m3.data[1] == 0.5); ASSERT(m3.data[2] == 0.75);
	ASSERT(m3.data[3] == 1.0); ASSERT(m3.data[4] == 1.25); ASSERT(m3.data[5] == 1.5);
	ASSERT(m3.data[6] == 1.75); ASSERT(m3.data[7] == 2.0); ASSERT(m3.data[8] == 2.25);
}

void testMatrix3_AssignmentAndComparison()
{
	Matrix3f m1(1.0, 2.0, 3.0,
				4.0, 5.0, 6.0,
				7.0, 8.0, 9.0);

	Matrix3f m2(2.0, 2.0, 2.0,
				2.0, 2.0, 2.0,
				2.0, 2.0, 2.0);

	m1 = m2;
	ASSERT(m1==m2);

	m2.setToIdentity();
	ASSERT(m1!=m2);
	ASSERT(m2==Matrix3f::IDENTITY);
}

void testMatrix3_Transpose()
{
	Matrix3d mat(
			0.707107, 0.0, 0.707107,
			0.0, 1.0, 0.0,
			-0.707107, 0.0, 0.707107
			);
	Matrix3d m = mat.transpose();
	ASSERT(m.data[0] == 0.707107); ASSERT(m.data[1] == 0); ASSERT(m.data[2] == -0.707107);
	ASSERT(m.data[3] == 0.0); ASSERT(m.data[4] == 1.0); ASSERT(m.data[5] == 0.0);
	ASSERT(m.data[6] == 0.707107); ASSERT(m.data[7] == 0.0); ASSERT(m.data[8] == 0.707107);

	mat.transposeInPlace();
	ASSERT(m==mat);
}

void testMatrix3_FromEuler()
{
	Matrix3f mat, supposedResult;
	Eulerf euler;

	euler.set(0.0, 45.0, 0.0);
	supposedResult.set(
		0.707107, 0.000000, -0.707107,
	    0.000000, 1.000000,  0.000000,
	    0.707107, 0.000000,  0.707107);
	mat.setFromEuler(euler.toRadians(), gmath::XYZ);
	ASSERT(mat==supposedResult);

	euler.set(45.0, 0.0, 0.0);
	supposedResult.set(
		1.000000,  0.000000, 0.000000,
		0.000000,  0.707107, 0.707107,
		0.000000, -0.707107, 0.707107);
	mat.setFromEuler(euler.toRadians(), gmath::XYZ);
	ASSERT(mat==supposedResult);

	euler.set(0.0, 0.0, 45.0);
	supposedResult.set(
		0.707107, 0.707107, 0.000000,
	   -0.707107, 0.707107, 0.000000,
		0.000000, 0.000000, 1.000000);
	mat.setFromEuler(euler.toRadians(), gmath::XYZ);
	ASSERT(mat==supposedResult);

	euler.set(45.0, 45.0, 45.0);
	supposedResult.set(
		0.5, 0.5, -0.707106781187,
	    -0.146446609407, 0.853553390593, 0.5,
		0.853553390593, -0.146446609407, 0.5);
	mat.setFromEuler(euler.toRadians(), gmath::XYZ);
	ASSERT(mat==supposedResult);

	euler.set(42.5, 24.75, 70.75);
	supposedResult.set(
		 0.299406, 0.857368, -0.418660,
		-0.602805, 0.510102,  0.613533,
		 0.739582, 0.068675,  0.669553);
	mat.setFromEuler(euler.toRadians(), gmath::XYZ);
	ASSERT(mat==supposedResult);
}

bool doToEulerTest(Matrix3d& m, Matrix3d& r, Eulerd& e, Eulerd& s)
{
	for (int i=0; i<6; i++)
	{
		bool result;
		r.setFromEuler(s.toRadians(), (RotationOrder)i);
		m = r;
		result = m.toEuler(e, (RotationOrder)i);
		e.toDegreesInPlace();
		ASSERT(e==s);
	}
}

void testMatrix3_ToEuler()
{
	Matrix3d m, r;
	Eulerd e, supposedResult;
	bool result;

	supposedResult.set(45.0, 45.0, 45.0);
	doToEulerTest(m, r, e, supposedResult);

	supposedResult.set(37.5, 20.75, 22.25);
	doToEulerTest(m, r, e, supposedResult);
}

void testMatrix3_Determinant()
{
	Matrix3f m(
		 0.299406, 0.857368, -0.418660,
		-0.602805, 0.510102,  0.613533,
		 0.739582, 0.068675,  0.669553);

	float det = m.determinant();
	ASSERT(fabs(det-1.0)<=Math<float>::EPSILON);
}

void testMatrix3_Inverse()
{
	Matrix3f m0(
		 0.299406, 0.857368, -0.418660,
		-0.602805, 0.510102,  0.613533,
		 0.739582, 0.068675,  0.669553);

	Matrix3f m1 = m0.inverse();
	ASSERT( (m0*m1)==Matrix3f::IDENTITY );

	m0.inverseInPlace();
	ASSERT(m0==m1);
}

void testMatrix3_Orthogonal()
{
	Matrix3f m(
		0.707107, 0.0, 0.707107,
		0.0, 1.0, 0.0,
		0.4, 0.6, 5.0
		);

	m.orthogonalInPlace();
		cout << m.toString() << endl;
}

void testMatrix3()
{
	cout << endl << "--- Test Matrix3 ---" << endl;
	TEST_CHECK(testMatrix3_Constructors);
	TEST_CHECK(testMatrix3_AssignmentAndComparison);
	TEST_CHECK(testMatrix3_ArithmeticOperations);
	TEST_CHECK(testMatrix3_Transpose);
	TEST_CHECK(testMatrix3_FromEuler);
	TEST_CHECK(testMatrix3_ToEuler);
	TEST_CHECK(testMatrix3_Determinant);
	TEST_CHECK(testMatrix3_Inverse);
	TEST_CHECK(testMatrix3_Orthogonal);
}




