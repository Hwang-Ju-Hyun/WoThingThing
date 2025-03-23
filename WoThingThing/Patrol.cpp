#include "Patrol.h"
#include"GameObject.h"
#include"TransComponent.h"
#include"EnemyStateManager.h"
#include"ColliderManager.h"
#include"TimeManager.h"
#include"AiComponent.h"
#include"Chase.h"
#include "EnemyAttack.h"

void ESM::Patrol::Init()
{
}

void ESM::Patrol::Update()
{
}

void ESM::Patrol::Exit()
{
}

ESM::Patrol::Patrol(GameObject* _enemy, GameObject* _player, bool dir_num, float Time, GameObject* _platform, std::string state_name)
{
	enemy = _enemy;
	player = _player;
	dir = dir_num;
	dir_Time = Time;
	platform = _platform;
	e_state_name = state_name;
}


