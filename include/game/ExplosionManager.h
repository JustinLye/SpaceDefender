#ifndef EXPLOSION_MANAGER_HEADER_INCLUDED
#define EXPLOSION_MANAGER_HEADER_INCLUDED
#include<random>
#ifdef ENGINE_DEBUG
#include"engine/util//DebugFunctions.h"
#endif
#include"engine/objects/TexRenderer.h"
#include"engine/containers/ObjectManager.h"
#include"game/Explosion.h"

using namespace Constants::Types;

class ExplosionManager :
	public Subject,
	public Observer,
	public ObjectManager<Explosion>
{
public:
	ExplosionManager(DrawableObject*, ShaderProgram*);
	~ExplosionManager();
	int MaxCapacity();
	int MaxActiveCapacity();
	void OnNotify(const GameObject&, const event_t&);
	void AddObserver(Observer*) override;
	void RemoveObserver(Observer*) override;

	void ExpansionSpeed(float);
	void MinExpansion(float);
	void MaxExpansion(float);
	void InitScale(float);

	float ExpansionSpeed() const;
	float MaxExpansion() const;
	float MinExpansion() const;
	float InitScale() const;

protected:
	Transform mTransform;
	DrawableObject* mShape;
	ShaderProgram* mShaderProg;
	Renderer* mRenderer;
	float mSpeed;
	float mInitScale;
	std::random_device mRd;
	std::mt19937 mGen;
	std::uniform_real_distribution<> mExpansionDist;


	Explosion* ConstructObject();
	void CustomAllocOps(unsigned int) override;
	void CustomInitOps() override;
	bool DestructionPred(Explosion*) const override;
};

#endif