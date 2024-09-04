#include "AiComponent.h"
#include"GameObject.h"
#include "TransComponent.h"
#include"EnemyStateManager.h"
#include"IDLE.h"
#include"ColliderManager.h"
#include"IDLE_Sniper.h"
//
AiComponent::AiComponent(GameObject* _owner) :BaseComponent(_owner), e_state_name("E") 
{
	esm = new ESM::EnemyStateManager();
}
AiComponent::~AiComponent()
{
	delete esm;
}
void AiComponent::Update()
{
	//e_state_name에 들어온 이름에 따라
	//EnemyStateManager에서 ChangeState를 해주는데 State자체는 IDle과 Patrol
	//IDLE과 Patrol은 직접 헤더를 include해서 접근하게 시킨다.
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
			//std::cout << "Aicomp" << std::endl;
			ESM::IDLE* p = new ESM::IDLE(m_pOwner, Player, set_dir, Time_dir, PlatForm, e_state_name, FirstPlacePos);
			esm->ChangeState(p);//p를 넘겨주면 자기자신을 m_pOwner를 넘겨주는거니 참조 한다는거다
		}
		else if (e_state_name == "Patrol")
		{
			//ESM::EnemyStateManager::GetInst()->ChangeState(); Patrol을 넣는다.
		}
	}

	if (e_Categories == "Sniper")
	{
		if (e_state_name == "IDLE_Sniper")
		{
			//std::cout << "Aicomp" << std::endl;
			ESM::IDLE_Sniper* p = new ESM::IDLE_Sniper(m_pOwner, Player, set_dir, Time_dir);//여기서 총알오브젝트 추가
			esm->ChangeState(p);//p를 넘겨주면 자기자신을 m_pOwner를 넘겨주는거니 참조 한다는거다
		}
	
	}
	//여기 언제든 주석가능 BossPattern부분과
	if (e_Categories == "Boss") 
	{	}

}

void AiComponent::SetTarget(GameObject* _player)
{
	Player = _player;
}

void AiComponent::Setdir(bool dir)//true가 왼쪽, false가 오른쪽
{
	set_dir = dir;
}


void AiComponent::Setdir_time(float Time)//고개돌리는 시간 정해주기
{
	Time_dir = Time;
}

void AiComponent::Change_State(ESM::BaseEnemyState* newstate)
{
	esm->ChangeState(newstate);
}

void AiComponent::SetPlatform(GameObject* platform)
{
	PlatForm = platform;
}

void AiComponent::SetFirstPlace(AEVec2 _FirstPlacePos)
{
	FirstPlacePos = _FirstPlacePos;
}




void AiComponent::LoadFromJson(const json& str)
{
}

json AiComponent::SaveToJson()
{
	return json();
}
