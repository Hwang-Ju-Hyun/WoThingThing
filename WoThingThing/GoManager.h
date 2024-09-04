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
	void RemoveDeathObj();
	void RemoveAllObj();
	void RemoveObj(const std::string& _name);

	GameObject* FindObj(const std::string& _name)const;

	GameObject* GetLastObj();	
	const std::vector<GameObject*>& Allobj() const
	{
		m_vecObj;

		return m_vecObj; 
	}

};

