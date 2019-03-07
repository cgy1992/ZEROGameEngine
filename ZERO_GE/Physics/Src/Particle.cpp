#include "Precompiled.h"
#include "Particle.h"

using namespace ZERO;
using namespace ZERO::Physics;

void Particle::DebugDraw() const
{
	Graphics::SimpleDraw::AddSphere(position, radius, Math::Vector4::Green(), 4, 2);
}

void Particle::SetPosition(const Math::Vector3& pos)
{
	position = pos;
	positionOld = pos;
}

void Particle::SetVelocity(const Math::Vector3& velocity)
{
	positionOld = position - velocity;
}