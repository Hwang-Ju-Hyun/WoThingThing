#pragma once
#include "header.h"
#include "BaseRTTI.h"

class GameObject;

class BaseComponent
	:public BaseRTTI
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
public:
	virtual void LoadFromJson(const json& str);
	virtual json SaveToJson();
};

