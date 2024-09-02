#pragma once
#include "BaseComponent.h"
#include "AEVec2.h"


class BulletComponent : public BaseComponent
{
	GameObject* bullet;

	AEVec2 bullet_Vec;
	AEVec2 bullet_const;
public:
	BulletComponent(GameObject* _owner);
	~BulletComponent() {};

	void SetBulletVec(AEVec2 dVec);


	void DestroyBullet();

	virtual void Update() override;
};