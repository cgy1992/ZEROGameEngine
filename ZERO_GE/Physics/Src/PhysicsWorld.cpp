#include "Precompiled.h"
#include "PhysicsWorld.h"

using namespace ZERO;
using namespace ZERO::Physics;

PhysicsWorld::PhysicsWorld()
	:mtimer(0.0f)
{

}
PhysicsWorld::~PhysicsWorld()
{

}

void PhysicsWorld::AddParticle(Particle* p)
{
	mParticles.push_back(p);
}

void PhysicsWorld::AddConstraints(Constraint* c)
{
	mConstraints.push_back(c);
}

void ZERO::Physics::PhysicsWorld::AddPlane(Math::Plane * plane)
{
	mPlanes.push_back(plane);
}


void PhysicsWorld::Update(float deltaTime)
{
	mtimer += deltaTime;
	while (mtimer >= mSettings.timeStep)
	{
		mtimer -= mSettings.timeStep;
		AccumulateForce();
		Integrate();
		SatisfyConstraints();
	}
}

void PhysicsWorld::ClearAll()
{
	for (auto p : mParticles)
	{
		SafeDelete(p);
	}
	for (auto c : mConstraints)
	{
		SafeDelete(c);
	}
	for (auto pl : mPlanes)
	{
		SafeDelete(pl);
	}
	mParticles.clear();
	mConstraints.clear();
	mPlanes.clear();
}

void PhysicsWorld::DebugDraw() const
{
	for (auto p : mParticles)
	{
		p->DebugDraw();
	}

	for (auto c : mConstraints)
	{
		c->DebugDraw();
	}
}

void PhysicsWorld::AccumulateForce()
{
	for (auto p : mParticles)
	{
		p->acceleration = mSettings.gravity;
	}
}

void PhysicsWorld::Integrate()
{
	const float timeStepSqr = Math::Sqr(mSettings.timeStep);
	for (auto p : mParticles)
	{
		Math::Vector3 displacement = (p->position - p->positionOld) + (p->acceleration * timeStepSqr);
		p->positionOld = p->position;
		p->position = p->position + displacement;
	}
}

void PhysicsWorld::SatisfyConstraints()
{
	for (auto c : mConstraints)
	{
		c->Apply();
	}

	for (auto p : mParticles)
	{
		
		for (auto pl : mPlanes)
		{	
			Math::Ray ray;
			ray.org = p->positionOld;
			ray.dir = p->position - p->positionOld; //Distance

			float distance = 0.0f;
			Math::Intersect(ray, *pl, distance);

			float sinPosition = Math::Dot(p->position, pl->n);
			/*float sinPositionOld = Math::Dot(p->positionOld, pl->n);
			float sinRayDir = sin(Math::Dot(ray.dir, pl->n));*/

			if (sinPosition <= 0.0f)
			{
				Math::Vector3 contactPoint{ ray.org + ray.dir * distance };
				Math::Vector3 penetrationVector = p->position - contactPoint;

				Math::Vector3 reflectionVector = Math::Reflect(ray.dir, pl->n);
				Math::Vector3 velocity = Math::Normalize(reflectionVector) * Math::Magnitude(penetrationVector);

				p->SetPosition(p->positionOld);
				p->SetVelocity(velocity);

			}
		}
	}

	
}

void PhysicsWorld::Setup(const Settings& settings)
{
	mSettings = settings;
}