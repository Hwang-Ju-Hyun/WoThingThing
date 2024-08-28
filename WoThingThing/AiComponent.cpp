#include "AiComponent.h"
#include"GameObject.h"
#include "TransComponent.h"
#include"EnemyStateManager.h"
#include"IDLE.h"
void AiComponent::Update()
{
	//e_state_name에 들어온 이름에 따라
	//EnemyStateManager에서 ChangeState를 해주는데 State자체는 IDle과 Patrol
	//IDLE과 Patrol은 직접 헤더를 include해서 접근하게 시킨다.
	if (e_state_name == "IDLE") 
	{
		//esm->ChangeState(new ESM::IDLE);
		//esm->Update();
	}
	else if (e_state_name == "Patrol") 
	{
		//ESM::EnemyStateManager::GetInst()->ChangeState(); Patrol을 넣는다.
	}
}

void AiComponent::SetState(const std::string& state_name)
{
	e_state_name = state_name;
}
