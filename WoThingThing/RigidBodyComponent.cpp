#include "RigidBodyComponent.h"
#include "BaseComponent.h"
#include "TransComponent.h"
#include "CompManager.h"
#include "GameObject.h"
#include "GoManager.h"

RigidBodyComponent::RigidBodyComponent(GameObject* _owner) : BaseComponent(_owner)	
{	
	m_vVelocity = { 0.f, 0.f };
	m_vGravity = { 0.f, 600.f };
}

RigidBodyComponent::~RigidBodyComponent()
{
}


void RigidBodyComponent::Update()
{
	
}

void RigidBodyComponent::LoadFromJson(const json& str)
{
	return;
}

json RigidBodyComponent::SaveToJson()
{
	return json();
}
