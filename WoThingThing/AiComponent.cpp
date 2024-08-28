#include "AiComponent.h"
#include"GameObject.h"
#include "TransComponent.h"
#include"EnemyStateManager.h"
#include"IDLE.h"
AiComponent::~AiComponent()
{
}
void AiComponent::Update()
{
	//e_state_name�� ���� �̸��� ����
	//EnemyStateManager���� ChangeState�� ���ִµ� State��ü�� IDle�� Patrol
	//IDLE�� Patrol�� ���� ����� include�ؼ� �����ϰ� ��Ų��.
	if (e_state_name == "IDLE") 
	{
		ESM::IDLE* p = new ESM::IDLE(m_pOwner);
		esm->ChangeState(p);//p�� �Ѱ��ָ� �ڱ��ڽ��� m_pOwner�� �Ѱ��ִ°Ŵ� ���� �Ѵٴ°Ŵ�
		esm->Update();
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

void AiComponent::LoadFromJson(const json& str)
{
}

json AiComponent::SaveToJson()
{
	return json();
}
