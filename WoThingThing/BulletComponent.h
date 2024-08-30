#pragma once
#include "BaseComponent.h"
#include "PlayerComponent.h"

class BulletComponent : public BaseComponent
{
	GameObject* bullet;
	PlayerComponent* player;
public:
	BulletComponent(GameObject* _owner);
	~BulletComponent();

	virtual void Update() override;
};