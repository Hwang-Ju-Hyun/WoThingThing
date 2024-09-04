#include "EnemyAttack.h"
#include "Chase.h"
#include"IDLE.h"
#include"GameObject.h"
#include"TransComponent.h"
#include"EnemyStateManager.h"
#include"ColliderManager.h"
#include"TimeManager.h"
#include"TestLevel.h"
#include"AiComponent.h"

void ESM::EnemyAttack::Init()
{
	melee_DelayAtk = 0.f;
	m_fDt = 0.f;
}

void ESM::EnemyAttack::Update()
{

	//melee_DelayAtk = TimeManager::GetInst()->GetAccTime();
	m_fDt = (f32)AEFrameRateControllerGetFrameTime();
	melee_DelayAtk += m_fDt;
	//TransComponent* player_trs = (TransComponent*)Player->FindComponent("Transform");
	if (ColliderManager::GetInst()->MeleeEnemyAttack(Attack_enemy, Player, dir_state))
	{
		if (melee_DelayAtk > 0.3f)
		{
			//std::cout << "Attack Player" << std::endl;
			m_fDt = 0.0f;
			melee_DelayAtk = 0.f;
		}
	}
	else 
	{
		AiComponent* enemy_ai = (AiComponent*)Attack_enemy->FindComponent("Ai");
		ESM::Chase* p = new ESM::Chase(Attack_enemy, Player, dir_state, dir_Time, PlatForm, e_state_name);
		//ESM::EnemyStateManager::GetInst()->ChangeState(p);
		enemy_ai->Change_State(p);
	}
}

void ESM::EnemyAttack::Exit()
{
}

ESM::EnemyAttack::EnemyAttack(GameObject* _enemy, GameObject* _player, bool dir, float Time, GameObject* _platform, std::string _state_name)
{
	Attack_enemy = _enemy;
	Player = _player;
	dir_state = dir;
	dir_Time = Time;
	PlatForm = _platform;
	e_state_name = _state_name;
}
