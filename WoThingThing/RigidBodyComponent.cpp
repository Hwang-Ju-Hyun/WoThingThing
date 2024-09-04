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
	jumpVelocity = { 0.f,400.f };
}

RigidBodyComponent::~RigidBodyComponent()
{
}


void RigidBodyComponent::Update()
{
	TransComponent* obj = dynamic_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));	
	if (obj == nullptr)
	{
		//std::cout << "RigidBodyComponent Update Error! : can't find TransformComponent" << std::endl;
		return;
	}
	//Landing	
	// Ȳ���� �ڵ� ���� -> �ؿ� �ڵ带 setjumpcntzero' ::Stage01 handleCollision���� ����
	//if (player_trs->GetPos().y <= -379.f)
	//	jumpCnt = 0;
	
	//Left
	//if (AEInputCheckCurr(AEVK_A))
	//{
	//	obj->AddPos(-5.f, 0.f);
	//	//if (player_trs->GetPos().x > -770)
	//}

	////Right
	//if (AEInputCheckCurr(AEVK_D))
	//{
	//	obj->AddPos(5.f, 0.f);
	//	//if (player_trs->GetPos().x < 770)
	//}
	AEVec2 pos = static_cast<TransComponent*>(obj)->GetPos();
	float dt = AEFrameRateControllerGetFrameTime();
	//left shift : time manipulation
	
	//if (AEInputCheckCurr(AEVK_LSHIFT))
	//{
	//	dt *= 0.1f;
	//}			
	
	//auto trans= CompManager::GetInst()->FindComponent("Transform");


	jumpVelocity.y -= m_vGravity.y * dt;//�߷�
	/*if (pos.y <= -380)
	{
		jumpVelocity.y = 0;
		pos.y = -380.f;
	}
	else
	{
		jumpVelocity.y -= m_vGravity.y * dt;
	}*/

	pos.y = pos.y + jumpVelocity.y * dt;
	static_cast<TransComponent*>(obj)->SetPos(pos);

}

void RigidBodyComponent::LoadFromJson(const json& str)
{
	return;
}

json RigidBodyComponent::SaveToJson()
{
	return json();
}

void RigidBodyComponent::jump(float jumpVal)
{
	TransComponent* EnemyTEST_trs = static_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));
	AEVec2 pos = static_cast<TransComponent*>(EnemyTEST_trs)->GetPos();
	float dt = AEFrameRateControllerGetFrameTime();
	jumpVelocity.y = jumpVal;
	pos.y += jumpVelocity.y * dt;
	static_cast<TransComponent*>(EnemyTEST_trs)->SetPos(pos);
}
