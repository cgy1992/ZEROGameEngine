#include "stdafx.h"
#include "CppUnitTest.h"


#include <Math/Inc/ZeroMath.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ZERO::Math;

namespace MathTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Vector3Addition)
		{
			// TODO: Your test code here
			Vector3 a{ 0.0f, 1.0f, 0.0f };
			Vector3 b{ 1.0f, 0.0f, 1.0f };
			Vector3 c = a + b;

			Assert::IsTrue(c.x == 1.0f);
			Assert::IsTrue(c.y == 1.0f);
			Assert::IsTrue(c.z == 1.0f);
		}
	};

	TEST_CLASS(QuaternionTest)
	{
	public:
		TEST_METHOD(AdditionTest)
		{
			Quaternion q1{ 1.0f, 1.0f, 1.0f, 1.0f };
			Quaternion q2{ 2.0f, 3.0f, 1.0f, -4.0f };

			Quaternion q3 = q1 + q2;

			Assert::IsTrue(q3.x == 3.0f);
			Assert::IsTrue(q3.y == 4.0f);
			Assert::IsTrue(q3.z == 2.0f);
			Assert::IsTrue(q3.w == -3.0f);
		}
		TEST_METHOD(SubtractionTest)
		{
			Quaternion q1{ 1.0f, 1.0f, 1.0f, 1.0f };
			Quaternion q2{ 2.0f, 3.0f, 1.0f, -4.0f };

			Quaternion q3 = q1 - q2;

			Assert::IsTrue(q3.x == -1.0f);
			Assert::IsTrue(q3.y == -2.0f);
			Assert::IsTrue(q3.z == 0.0f);
			Assert::IsTrue(q3.w == 5.0f);
		}
		TEST_METHOD(MultiplicationTest)
		{
			Quaternion q1{ 1.0f, 1.0f, 1.0f, 1.0f };
			Quaternion q2{ 2.0f, 3.0f, 1.0f, -4.0f };

			Quaternion q3 = q1 * q2;

			//Result from wolphram
			Assert::IsTrue(q3.x == -4.0f);
			Assert::IsTrue(q3.y == 0.0f);
			Assert::IsTrue(q3.z == -2.0f);
			Assert::IsTrue(q3.w == -10.0f);
		}
		TEST_METHOD(MultiplicationScalarTest)
		{
			Quaternion q1{ 1.0f, 1.0f, 1.0f, 1.0f };
			float scalar = 2.0f;

			Quaternion q3 = q1 * scalar;

			//Result from wolphram
			Assert::IsTrue(q3.x == 2.0f);
			Assert::IsTrue(q3.y == 2.0f);
			Assert::IsTrue(q3.z == 2.0f);
			Assert::IsTrue(q3.w == 2.0f);
		}
		TEST_METHOD(DivisionScalarTest)
		{
			Quaternion q1{ 1.0f, 1.0f, 1.0f, 1.0f };
			float scalar = 2.0f;

			Quaternion q3 = q1 / scalar;

			//Result from wolphram
			Assert::IsTrue(q3.x == 0.5f);
			Assert::IsTrue(q3.y == 0.5f);
			Assert::IsTrue(q3.z == 0.5f);
			Assert::IsTrue(q3.w == 0.5f);
		}
		TEST_METHOD(QuaternionFromMatrixTest)
		{
			Matrix4 m{	-1.0f,  0.0f, 0.0f, 0.0f,
						0.0f,  -1.0f,  0.0f, 0.0f,
						0.0f,  0.0f,  1.0f, 0.0f,
						0.0f, 0.0f,  0.0f, 1.0f };

			Quaternion q = QuaternionFromMatrix(m);

			//Result from wolphram
			Assert::IsTrue(q.x == 0.0f);
			Assert::IsTrue(q.y == 0.0f);
			Assert::IsTrue(q.z == 1.0f);
			Assert::IsTrue(q.w == 0.0f);

		}
		TEST_METHOD(LookRotationTest)
		{

		}
		TEST_METHOD(FromToTest)
		{

		}
		TEST_METHOD(ZeroTest)
		{
			Quaternion q = Quaternion::Zero();

			//Result from wolphram
			Assert::IsTrue(q.x == 0.0f);
			Assert::IsTrue(q.y == 0.0f);
			Assert::IsTrue(q.z == 0.0f);
			Assert::IsTrue(q.w == 0.0f);
		}
		TEST_METHOD(IdentityTest)
		{
			Quaternion q = Quaternion::Identity();

			//Result from wolphram
			Assert::IsTrue(q.x == 0.0f);
			Assert::IsTrue(q.y == 0.0f);
			Assert::IsTrue(q.z == 0.0f);
			Assert::IsTrue(q.w == 1.0f);
		}
		TEST_METHOD(MagnitudeTest)
		{
			Quaternion q1{ 2.0f, 2.0f, 2.0f, 2.0f };

			float m = Magnitude(q1);

			//Result from wolphram
			Assert::IsTrue(m == 4.0f);
		}
		TEST_METHOD(MagnitudeSQRTest)
		{
			Quaternion q1{ 2.0f, 2.0f, 2.0f, 1.0f };

			float m2 = MagnitudeSqr(q1);

			//Result from wolphram
			Assert::IsTrue(m2 == 13.0f);
		}
		TEST_METHOD(NormalizeTest)
		{
			Quaternion q{ 7.0f, 8.0f, 2.0f, 5.0f };
			Quaternion q2 = Normalize(q);
			float m = Magnitude(q2);

			Assert::IsTrue(m == 1.0f);
		}
		TEST_METHOD(ConjugateTest)
		{
			Quaternion q1{ 3.0f, 4.0f, 3.0f, 1.0f };

			Quaternion q2 = Conjugate(q1);

			//Result from wolphram
			Assert::IsTrue(q2.x == -3.0f);
			Assert::IsTrue(q2.y == -4.0f);
			Assert::IsTrue(q2.z == -3.0f);
			Assert::IsTrue(q2.w ==  1.0f);
		}
		TEST_METHOD(InverseTest)
		{
			Quaternion q1{ 2.0f, 2.0f, 2.0f, 2.0f };
			Quaternion q2{ Inverse(q1) };

			//Result from wolphram
			Assert::IsTrue(q2.x == -0.125f);
			Assert::IsTrue(q2.y == -0.125f);
			Assert::IsTrue(q2.z == -0.125f);
			Assert::IsTrue(q2.w ==  0.125f);
		}
		TEST_METHOD(QuaternionToMatrixTest)
		{

			Quaternion q{0.0f, 0.0f, 1.0f, 0.0f};
			Matrix4 m {QuaternionToMatrix(q)};


			//Result from wolphram
			Assert::IsTrue(m._11 == -1.0f);
			Assert::IsTrue(m._12 == 0.0f);
			Assert::IsTrue(m._13 == 0.0f);
			Assert::IsTrue(m._14 == 0.0f);

			Assert::IsTrue(m._21 == 0.0f);
			Assert::IsTrue(m._22 == -1.0f);
			Assert::IsTrue(m._23 == 0.0f);
			Assert::IsTrue(m._24 == 0.0f);

			Assert::IsTrue(m._31 == 0.0f);
			Assert::IsTrue(m._32 == 0.0f);
			Assert::IsTrue(m._33 == 1.0f);
			Assert::IsTrue(m._34 == 0.0f);

			Assert::IsTrue(m._41 == 0.0f);
			Assert::IsTrue(m._42 == 0.0f);
			Assert::IsTrue(m._43 == 0.0f);
			Assert::IsTrue(m._44 == 1.0f);
		}
		TEST_METHOD(SlerpTest)
		{

		}
		TEST_METHOD(EulerToQuaternionTest)
		{
			Quaternion q = EulerToQuaternion(30.0f, 40.0f, 50.0f);
			float e = 0.001f;
			Assert::IsTrue(q.x - 0.360f < e);
			Assert::IsTrue(q.y - 0.196f < e);
			Assert::IsTrue(q.z - 0.303f < e);
			Assert::IsTrue(q.w - 0.860f < e);
		}
		
		TEST_METHOD(QuaternionToEulerTest)
		{
			Quaternion q{ 1.0f, 1.0f, 1.0f, 1.0f };
			Vector3 eulerAngles = QuaternionToEuler(q);

			//float e = 0.1f;
			Assert::IsTrue(eulerAngles.x == 0.0);
			Assert::IsTrue(eulerAngles.y == 90.0f);
			Assert::IsTrue(eulerAngles.z == 90.0f);
		}
	};
}

/*QuaternionFromAxisAngle(Vector3 axis, float angleDegrees)
QuaternionFromMatrix(Matrix4 rotationMatrix)
LookRotation(Vector3 look, Vector3 up)
FromTo(Vector3 from, Vector3 to)
Zero()
Identity()
Magnitude(const Quaternion& q) 
MagnitudeSqr(const Quaternion& q)
Normalize(const Quaternion& q)
Conjugate(Quaternion q0)
Inverse(Quaternion q0)
Matrix4 MatrixRotationQuaternion(const Quaternion& q)
Quaternion Slerp(Quaternion q0, Quaternion q1, float t)
Quaternion EulerToQuaternion(float roll, float pitch, float yaw)
*/