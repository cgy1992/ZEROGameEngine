#ifndef INCLUDED_PHYSICS_PHYSICSWORLD_H
#define INCLUDED_PHYSICS_PHYSICSWORLD_H

#include "Particle.h"
#include "Constraints.h"

namespace ZERO
{
namespace Physics
{
	class PhysicsWorld
	{
	public:
		struct Settings
		{
			Math::Vector3 gravity{ 0.0f, -9.8f, 0.0f };
			float timeStep{ 1.0f / 60.0f };
			uint32_t iterations{ 1 };
		};


		PhysicsWorld();
		~PhysicsWorld();

		void Setup(const Settings& settings);
		void AddParticle(Particle* p);
		void AddConstraints(Constraint* c);
		void AddPlane(Math::Plane* plane);

		void Update(float deltaTime);
		void ClearAll();

		void DebugDraw() const;

	private:
		void AccumulateForce();
		void Integrate(); //Verlet Integration
		void SatisfyConstraints();

		std::vector<Particle*> mParticles;
		std::vector<Constraint*> mConstraints;
		std::vector<Math::Plane*> mPlanes;

		Settings mSettings;
		float mtimer;
	};

}
}



#endif // !INCLUDED_PHYSICS_PHYSICSWORLD_H

