#include "Chase.h"
#include"IDLE.h"
#include"GameObject.h"
#include"TransComponent.h"
#include"EnemyStateManager.h"
#include"ColliderManager.h"
#include"TimeManager.h"
#include"TestLevel.h"

void ESM::Chase::Init()
{
	std::cout << "Chase Init" << std::endl;
}

void ESM::Chase::Update()
{
	if (ColliderManager::GetInst()->PlayerSearch(Chase_enemy, Player, dir_state))
	{
		std::cout << "Chase" << std::endl;
	}
	else 
	{
		std::cout << "Chase Fail" << std::endl;
	}

}

void ESM::Chase::Exit()
{
}

ESM::Chase::Chase(GameObject* _enemy, GameObject* _player, bool dir)
{
	Chase_enemy = _enemy;
	Player = _player;
	dir_state = dir;
}

