#include "AiComponent.h"
#include"GameObject.h"
#include "TransComponent.h"
#include"EnemyStateManager.h"
#include"IDLE.h"
void AiComponent::Update()
{
	//e_state_name�� ���� �̸��� ����
	//EnemyStateManager���� ChangeState�� ���ִµ� State��ü�� IDle�� Patrol
	//IDLE�� Patrol�� ���� ����� include�ؼ� �����ϰ� ��Ų��.
	if (e_state_name == "IDLE") 
	{
		//esm->ChangeState(new ESM::IDLE);
		//esm->Update();
	}
	else if (e_state_name == "Patrol") 
	{
		//ESM::EnemyStateManager::GetInst()->ChangeState(); Patrol�� �ִ´�.
	}
}

void AiComponent::SetState(const std::string& state_name)
{
	e_state_name = state_name;
}
