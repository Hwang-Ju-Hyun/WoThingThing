#pragma once
#include "header.h"
class GameObject;

class BaseComponent
{
public:
	BaseComponent() = delete;
	BaseComponent(GameObject* _owner);
	virtual ~BaseComponent();
private:
	std::string m_sName;
public:
	virtual void SetName(const std::string& _name)	{ m_sName = _name; }
	virtual std::string GetName()const				{ return m_sName; }
public:
	virtual void Update() = 0;
	GameObject* GetOwner();
public:
	GameObject* m_pOwner;
};

