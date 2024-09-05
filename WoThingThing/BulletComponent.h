#pragma once
#include "BaseComponent.h"
#include "AEVec2.h"


class BulletComponent : public BaseComponent
{
	AEVec2 bullet_Vec;
	AEVec2 bullet_const;

	bool isParrying;
public:
	BulletComponent(GameObject* _owner);
	~BulletComponent() {};

	void SetBulletVec(AEVec2 dVec);
	AEVec2 GetBulletVec();
	void DestroyBullet();

	void SetState();
	bool GetState();

	bool EnemyShoot;//true면 enemy가 shoot 했다는거임
	virtual void Update() override;
};