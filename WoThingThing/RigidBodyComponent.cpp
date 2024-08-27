#include "RigidBodyComponent.h"
#include "BaseComponent.h"
#include "TransComponent.h"
#include "CompManager.h"
#include "GameObject.h"

RigidBodyComponent::RigidBodyComponent(GameObject* _owner)
	:BaseComponent(_owner)	
{	
	m_vVelocity = { 0.f, 0.f };
	m_vGravity = { 0.f, 500.f };
}

RigidBodyComponent::~RigidBodyComponent()
{
}

void RigidBodyComponent::Jump(float yPos)
{
	auto trans = GetOwner()->FindComponent("Transform");
	AEVec2 pos = static_cast<TransComponent*>(trans)->GetPos();
	float dt = AEFrameRateControllerGetFrameTime();
	m_vVelocity.y = yPos;
	pos.y += m_vVelocity.y * dt;
	static_cast<TransComponent*>(trans)->SetPos(pos);
}

void RigidBodyComponent::Update()
{
	float dt = AEFrameRateControllerGetFrameTime();

	auto trans = GetOwner()->FindComponent("Transform");
	AEVec2 pos = static_cast<TransComponent*>(trans)->GetPos();
	pos.x = pos.x + m_vVelocity.x * dt;

	//auto trans= CompManager::GetInst()->FindComponent("Transform");

	if (pos.y <= -380)
	{
		m_vVelocity.y = 0;
	}
	else
	{
		m_vVelocity.y -= m_vGravity.y * dt;
	}
	pos.y = pos.y + m_vVelocity.y * dt;
	static_cast<TransComponent*>(trans)->SetPos(pos);

}

void RigidBodyComponent::LoadFromJson(const json& str)
{
	return;
}

json RigidBodyComponent::SaveToJson()
{
	return json();
}
