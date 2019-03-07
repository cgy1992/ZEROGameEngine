#ifndef INCLUDED_PHYSICS_CONSTRAINTS_H
#define INCLUDED_PHYSICS_CONSTRAINTS_H

namespace ZERO
{
namespace Physics
{
	class Particle;

	class Constraint
	{
	public:
		virtual ~Constraint() {}
		virtual void Apply() const = 0;
		virtual void DebugDraw() const {}
	};


	class Spring : public Constraint 
	{
	public:

		Spring(Particle* a, Particle* b, float restLength = -1.0f);
		void Apply() const override;
		void DebugDraw() const override;

	protected:
		Particle* mParticleA;
		Particle* mParticleB;
		float mRestLength;
	};

	class Fixed : public Constraint
	{
	public:

		Fixed(Particle* a, float sideLength = 1.0f);
		void Apply() const override;
		void DebugDraw() const override;

	protected:
		Particle * mParticleA;
		Math::Vector3 mPosition;
		float mSideLength;
	};

}
}


#endif // !INCLUDED_PHYSICS_CONSTRAINTS_H
