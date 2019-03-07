#include "Precompiled.h"
#include "Constraints.h"
#include "Particle.h"

using namespace ZERO;
using namespace ZERO::Physics;

Spring::Spring(Particle* a, Particle* b, float rastLength)
	: mParticleA(a)
	, mParticleB(b)
	, mRestLength(rastLength)
{}

void Spring::Apply() const
{
	Math::Vector3 delta = mParticleB->position - mParticleA->position;
	float deltaLength = Math::Magnitude(delta);
	float diff = (deltaLength - mRestLength) / (deltaLength*(mParticleA->invMass + mParticleB->invMass));
	mParticleA->position += delta * mParticleA->invMass * diff;
	mParticleB->position -= delta * mParticleB->invMass * diff;
}

void Spring::DebugDraw() const
{
	Graphics::SimpleDraw::AddLine(mParticleA->position, mParticleB->position, Math::Vector4::Blue());
}


Fixed::Fixed(Particle* a, float sideLength)
	: mParticleA(a)
	, mPosition(a->position)
	, mSideLength(sideLength)
{}

void Fixed::Apply() const
{
	float halfLength = mSideLength * 0.5f;
	Math::Vector3 X = Math::Vector3::XAxis();
	Math::Vector3 Y = Math::Vector3::YAxis();
	Math::Vector3 Z = Math::Vector3::ZAxis();

	Math::Vector3 minBoundary = mPosition - (Y * halfLength) - (X * halfLength) - (Z * halfLength) + Math::Vector3(mParticleA->radius, mParticleA->radius, mParticleA->radius);
	Math::Vector3 maxBoundary = mPosition + (Y * halfLength) + (X * halfLength) + (Z * halfLength) - Math::Vector3(mParticleA->radius, mParticleA->radius, mParticleA->radius);
	mParticleA->position = Math::VecMin(Math::VecMax(mParticleA->position, minBoundary), maxBoundary);
}
void Fixed::DebugDraw() const
{
	float halfLength = mSideLength * 0.5f;
	Math::Vector3 X = Math::Vector3::XAxis();
	Math::Vector3 Y = Math::Vector3::YAxis();
	Math::Vector3 Z = Math::Vector3::ZAxis();

	Math::Vector3 p1 = mPosition + (Y * halfLength) - (X * halfLength) - (Z * halfLength);
	Math::Vector3 p2 = mPosition + (Y * halfLength) - (X * halfLength) + (Z * halfLength);
	Math::Vector3 p3 = mPosition + (Y * halfLength) + (X * halfLength) - (Z * halfLength);
	Math::Vector3 p4 = mPosition + (Y * halfLength) + (X * halfLength) + (Z * halfLength);
	Math::Vector3 p5 = mPosition - (Y * halfLength) - (X * halfLength) - (Z * halfLength);
	Math::Vector3 p6 = mPosition - (Y * halfLength) - (X * halfLength) + (Z * halfLength);
	Math::Vector3 p7 = mPosition - (Y * halfLength) + (X * halfLength) - (Z * halfLength);
	Math::Vector3 p8 = mPosition - (Y * halfLength) + (X * halfLength) + (Z * halfLength);

	Graphics::SimpleDraw::AddLine(p1, p2, Math::Vector4::Red());
	Graphics::SimpleDraw::AddLine(p2, p4, Math::Vector4::Red());
	Graphics::SimpleDraw::AddLine(p4, p3, Math::Vector4::Red());
	Graphics::SimpleDraw::AddLine(p3, p1, Math::Vector4::Red());
	Graphics::SimpleDraw::AddLine(p1, p5, Math::Vector4::Red());
	Graphics::SimpleDraw::AddLine(p5, p6, Math::Vector4::Red());
	Graphics::SimpleDraw::AddLine(p6, p2, Math::Vector4::Red());
	Graphics::SimpleDraw::AddLine(p6, p8, Math::Vector4::Red());
	Graphics::SimpleDraw::AddLine(p8, p4, Math::Vector4::Red());
	Graphics::SimpleDraw::AddLine(p8, p7, Math::Vector4::Red());
	Graphics::SimpleDraw::AddLine(p7, p5, Math::Vector4::Red());
	Graphics::SimpleDraw::AddLine(p3, p7, Math::Vector4::Red());

	Math::Reflect({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f });
}