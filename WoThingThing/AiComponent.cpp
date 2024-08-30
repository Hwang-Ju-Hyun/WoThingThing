#include "AiComponent.h"
#include"GameObject.h"
#include "TransComponent.h"
#include"EnemyStateManager.h"
#include"IDLE.h"
#include"ColliderManager.h"
#include"IDLE_Sniper.h"
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

void AiComponent::SetState(const std::string& state_name, const std::string& enemyCategories)
{
	e_state_name = state_name;
	e_Categories = enemyCategories;
	if (e_Categories == "Melee")
	{
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

	if (e_Categories == "Sniper")
	{
		if (e_state_name == "IDLE_Sniper")
		{
			std::cout << "Aicomp" << std::endl;
			ESM::IDLE_Sniper* p = new ESM::IDLE_Sniper(m_pOwner, Player, set_dir, Time_dir, Bullet);//���⼭ �Ѿ˿�����Ʈ �߰�
			esm->ChangeState(p);//p�� �Ѱ��ָ� �ڱ��ڽ��� m_pOwner�� �Ѱ��ִ°Ŵ� ���� �Ѵٴ°Ŵ�
		}
	
	}

	if (e_Categories == "Boss") 
	{

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

void AiComponent::SetSniper_bullet(GameObject* _bullet)
{
	Bullet = _bullet;
}




void AiComponent::LoadFromJson(const json& str)
{
}

json AiComponent::SaveToJson()
{
	return json();
}
