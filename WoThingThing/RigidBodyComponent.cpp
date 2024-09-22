#include "RigidBodyComponent.h"
#include "BaseComponent.h"
#include "TransComponent.h"
#include "CompManager.h"
#include "GameObject.h"
#include "GoManager.h"
//
#include"StageBoss_Lvl.h"
//
RigidBodyComponent::RigidBodyComponent(GameObject* _owner) : BaseComponent(_owner)	
{	
	m_vVelocity = { 0.f, 0.f };
	m_vGravity = { 0.f, 600.f };
	jumpVelocity = { 0.f,400.f };

	//실험
	maniCapacity = 7.f;
	timeManipul = maniCapacity;
	manipulActive = false;
}

RigidBodyComponent::~RigidBodyComponent()
{
}


void RigidBodyComponent::Update()
{
	TransComponent* obj = dynamic_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));	
	if (obj == nullptr)
	{
		return;
	}
	//Landing	
	// 황주현 코드 수정 -> 밑에 코드를 setjumpcntzero' ::Stage01 handleCollision에서 구현
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
	bool ShouldSlowTime = AEInputCheckCurr(AEVK_LSHIFT);
	timeManipul = maniCapacity;
	if (ShouldSlowTime) 
	{
		manipulActive = true;
		timeManipul -= dt;
		if (timeManipul <= 0.f)
	    {
			manipulActive = false; //게이지가 0이면 누르는 동안에도 Manipulate가 안되게
			timeManipul = 0.f;
	    }
	}
	if (!AEInputCheckCurr(AEVK_LSHIFT))
	{
		manipulActive = false;
		if (timeManipul < maniCapacity)
			timeManipul += dt;
	}


	if (Level::StageBoss_Lvl::Stage2 && manipulActive)
	{
		dt *= 0.1f;  // 시간 조작이 활성화되면 dt를 절반으로 줄여서 점프 속도만 느리게 함
	}
	//if (AEInputCheckCurr(AEVK_LSHIFT))
	//{
	//	dt *= 0.1f;
	//}			
	
	//auto trans= CompManager::GetInst()->FindComponent("Transform");


	jumpVelocity.y -= m_vGravity.y * dt;//중력
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
