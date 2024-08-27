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
};

