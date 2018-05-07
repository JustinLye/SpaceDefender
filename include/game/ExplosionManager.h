#ifndef EXPLOSION_MANAGER_HEADER_INCLUDED
#define EXPLOSION_MANAGER_HEADER_INCLUDED

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

	void ExpansionSpeed(const float&);
	void MaxExpansion(const float&);
	void InitScale(const float&);

	const float& ExpansionSpeed() const;
	const float& MaxExpansion() const;
	const float& InitScale() const;

protected:
	Transform mTransform;
	DrawableObject* mShape;
	ShaderProgram* mShaderProg;
	Renderer* mRenderer;
	float mSpeed;
	float mMaxExpansion;
	float mInitScale;

	Explosion* ConstructObject();
	void CustomAllocOps(const unsigned int&) override;
	void CustomInitOps() override;
	bool DestructionPred(Explosion*) const override;
};

#endif