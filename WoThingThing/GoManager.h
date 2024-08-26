#pragma once
#include "header.h"

class GameObject;

class GoManager
{
public:
	SINGLE(GoManager);
public:
	std::vector<GameObject*> m_vecObj;
public:
	GameObject* AddObject(GameObject* _obj);
	void RemoveAllObj();
	GameObject* GetLastObj();	
	std::vector<GameObject*> Allobj() { return m_vecObj; }

};

