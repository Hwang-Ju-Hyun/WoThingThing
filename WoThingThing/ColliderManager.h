#pragma once
#include "header.h"

class GameObject;

class ColliderManager
{
public:
	SINGLE(ColliderManager);
public:
	bool IsCollision(GameObject* _obj1, GameObject* _obj2);
	bool PlayerSearch(GameObject* _obj1, GameObject* _obj2);
	int enemy_dir; //0이 왼쪽, 1이 오른쪽
};

