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
	//�ӽ��ڵ� �Լ�RemoveObj(const std::string& _name);�� �������� �̸��� ã�Ƽ�
	//m_vecObj�� �����ϰڴ�
	//��, ã�Ƽ� ���� �����ϰڴ�.
	void RemoveObj(const std::string& _name);
	GameObject* GetLastObj();	
	std::vector<GameObject*> Allobj() 
	{
		m_vecObj;

		return m_vecObj; 
	}

};

