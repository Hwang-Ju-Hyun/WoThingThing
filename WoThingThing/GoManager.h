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
	//임시코드 함수RemoveObj(const std::string& _name);는 오브젝의 이름을 찾아서
	//m_vecObj를 삭제하겠다
	//즉, 찾아서 직접 삭제하겠다.
	void RemoveObj(const std::string& _name);
	GameObject* GetLastObj();	
	std::vector<GameObject*> Allobj() 
	{
		m_vecObj;

		return m_vecObj; 
	}

};

