#ifndef INCLUDED_PHYSICS_PARTICLES_H
#define INCLUDED_PHYSICS_PARTICLES_H

namespace ZERO
{
namespace Physics
{
	class Particle
	{
	public:
		Particle() = default;

		void DebugDraw() const;

		void SetPosition(const Math::Vector3& pos);
		void SetVelocity(const Math::Vector3& vel);

		Math::Vector3 position;
		Math::Vector3 positionOld;
		Math::Vector3 acceleration;
		float radius{ 1.0f };
		float invMass{ 0.1f };
	};
} // !namespace Physics
} // !namespace ZERO`

#endif // !INCLUDED_PHYSICS_PARTICLES_H

