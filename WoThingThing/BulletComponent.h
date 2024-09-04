#pragma once
#include "BaseComponent.h"
#include "AEVec2.h"


class BulletComponent : public BaseComponent
{
	AEVec2 bullet_Vec;
	AEVec2 bullet_const;
public:
	BulletComponent(GameObject* _owner);
	~BulletComponent() {};

	void SetBulletVec(AEVec2 dVec);
	AEVec2 GetBulletVec();
	void DestroyBullet();
	bool EnemyShoot;//true면 enemy가 shoot 했다는거임
	virtual void Update() override;
	bool Bullet_manipulActive;
};