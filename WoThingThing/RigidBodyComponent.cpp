#include "RigidBodyComponent.h"
#include "BaseComponent.h"
#include "TransComponent.h"
#include "CompManager.h"
#include "GameObject.h"

RigidBodyComponent::RigidBodyComponent(GameObject* _owner)
	:BaseComponent(_owner)	
{	
	m_vVelocity = { 500.f,-100.f };
	m_vGravity = { 0.f,0.f };
}

RigidBodyComponent::~RigidBodyComponent()
{
}

void RigidBodyComponent::Update()
{
	auto trans = GetOwner()->FindComponent("Transform");
	
	//auto trans= CompManager::GetInst()->FindComponent("Transform");
	
	AEVec2 pos = static_cast<TransComponent*>(trans)->GetPos();
	
	float dt = AEFrameRateControllerGetFrameTime();
	
//	m_vVelocity.x += m_vGravity.x * dt;
	m_vVelocity.y += m_vGravity.y * dt;

	/*pos.x = pos.x + m_vVelocity.x * dt;
	pos.y = pos.y + m_vVelocity.y * dt;*/

	static_cast<TransComponent*>(trans)->SetPos(pos);

}
