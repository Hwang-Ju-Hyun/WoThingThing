#pragma once
#include "header.h"

class BaseComponent;

class GameObject
{
public:
	GameObject() = delete;
	GameObject(std::string _name);
	~GameObject();
private:
	std::string m_sName;		
public:
	void SetName(const std::string& _name) { m_sName = _name; }
	const std::string& GetName()const { return m_sName; }
private:
	std::map<std::string, BaseComponent*> m_mapComp;
public:
	BaseComponent* AddComponent(const std::string& _name, BaseComponent* _comp);
	BaseComponent* FindComponent(const std::string& _name);	
	void DeleteComponent(const std::string& _name);
public:
	std::map<std::string, BaseComponent*> GetAllComp()
	{
		return m_mapComp;
	}
public:
	friend class BaseComponent;
};

