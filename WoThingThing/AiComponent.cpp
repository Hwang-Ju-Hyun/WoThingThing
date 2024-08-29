#include "AiComponent.h"
#include"GameObject.h"
#include "TransComponent.h"
#include"EnemyStateManager.h"
#include"IDLE.h"
#include"ColliderManager.h"
AiComponent::~AiComponent()
{
}
void AiComponent::Update()
{
	//e_state_name�� ���� �̸��� ����
	//EnemyStateManager���� ChangeState�� ���ִµ� State��ü�� IDle�� Patrol
	//IDLE�� Patrol�� ���� ����� include�ؼ� �����ϰ� ��Ų��.
	esm->Update();


}

void AiComponent::SetState(const std::string& state_name)
{
	e_state_name = state_name;
	if (e_state_name == "IDLE")
	{
		std::cout << "Aicomp" << std::endl;
		ESM::IDLE* p = new ESM::IDLE(m_pOwner, Player, set_dir, Time_dir);
		esm->ChangeState(p);//p�� �Ѱ��ָ� �ڱ��ڽ��� m_pOwner�� �Ѱ��ִ°Ŵ� ���� �Ѵٴ°Ŵ�
	}
	else if (e_state_name == "Patrol")
	{
		//ESM::EnemyStateManager::GetInst()->ChangeState(); Patrol�� �ִ´�.
	}

}

void AiComponent::SetTarget(GameObject* _player)
{
	Player = _player;
}

void AiComponent::Setdir(bool dir)//true�� ����, false�� ������
{
	set_dir = dir;
}


void AiComponent::Setdir_time(float Time)//�������� �ð� �����ֱ�
{
	Time_dir = Time;
}




void AiComponent::LoadFromJson(const json& str)
{
}

json AiComponent::SaveToJson()
{
	return json();
}
