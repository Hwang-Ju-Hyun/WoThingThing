#pragma once
#include "header.h"
#include "BaseRTTI.h"

class GameObject;

class BaseComponent
	:public BaseRTTI
{
	std::string m_sName;
public:
	BaseComponent() = delete;
	BaseComponent(GameObject* _owner);
	virtual ~BaseComponent();

	virtual void SetName(const std::string& _name)	{ m_sName = _name; }
	virtual std::string GetName()const				{ return m_sName; }
	virtual void Update() = 0;

	GameObject* GetOwner();

	GameObject* m_pOwner;

	virtual void LoadFromJson(const json& str);
	virtual json SaveToJson(const json& str);
};

