#pragma once
#include "header.h"

class GameObject;

class ColliderManager
{
public:
	SINGLE(ColliderManager);
public:
	bool IsCollision(GameObject* _obj1, GameObject* _obj2);
	bool PlayerSearch(GameObject* _obj1, GameObject* _obj2, bool enemy_dir);
	bool MeleeEnemyAttack(GameObject* _obj1, GameObject* _obj2, bool enemy_dir);
	void DrawRect(float bottomleft_x, float bottomleft_y, float topRight_x, float topRight_y, float r, float g, float b);
};

