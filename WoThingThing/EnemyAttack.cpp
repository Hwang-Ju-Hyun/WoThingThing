#include "EnemyAttack.h"
#include "Chase.h"
#include"IDLE.h"
#include"GameObject.h"
#include"TransComponent.h"
#include"EnemyStateManager.h"
#include"ColliderManager.h"
#include"TimeManager.h"
#include"TestLevel.h"

void ESM::EnemyAttack::Init()
{
	melee_DelayAtk = 0.f;
}

void ESM::EnemyAttack::Update()
{

	melee_DelayAtk = TimeManager::GetInst()->GetAccTime();
	//TransComponent* player_trs = (TransComponent*)Player->FindComponent("Transform");
	if (ColliderManager::GetInst()->MeleeEnemyAttack(Attack_enemy, Player, dir_state))
	{
		if (melee_DelayAtk > 0.3f)
		{
			std::cout << "Attack Player" << std::endl;
			TimeManager::GetInst()->SetAccTime(0.0f);
		}
	}
	else 
	{
		ESM::Chase* p = new ESM::Chase(Attack_enemy, Player, dir_state, dir_Time);
		ESM::EnemyStateManager::GetInst()->ChangeState(p);
	}
}

void ESM::EnemyAttack::Exit()
{
}

ESM::EnemyAttack::EnemyAttack(GameObject* _enemy, GameObject* _player, bool dir, float Time)
{
	Attack_enemy = _enemy;
	Player = _player;
	dir_state = dir;
	dir_Time = Time;
}
