#include "IDLE_Sniper.h"
#include"GameObject.h"
#include"TransComponent.h"
#include"EnemyStateManager.h"
#include"ColliderManager.h"
#include"TimeManager.h"
#include "TargetAim_Sniper.h"
#include"SpriteComponent.h"

void ESM::IDLE_Sniper::Init()
{
	accumulatedTime = 0;
	TimeManager::GetInst()->SetAccTime(0.0f);
}

void ESM::IDLE_Sniper::Update()
{
	accumulatedTime = TimeManager::GetInst()->GetAccTime();

	if (dir_Time != 0)
	{
		//방향만 달라지게
		if (accumulatedTime >= dir_Time)//5.0f느낌
		{
			// 시간 초기화
			TimeManager::GetInst()->SetAccTime(0.0f);
			// 추가로 필요한 로직을 여기에 작성
			std::cout << dir_Time << " Turn Dir" << std::endl;
			dir = !(dir);
		}
	}

	
	if (ColliderManager::GetInst()->PlayerSearch(enemy, player, dir, 20.f, 10.f,10.f))//여기에 감지범위 조정
	{
		//스나이퍼는 바로 공격모드로 들어가게한다.
		ESM::TargetAim_Sniper* p = new ESM::TargetAim_Sniper(enemy, player, dir, dir_Time, bullet);
		ESM::EnemyStateManager::GetInst()->ChangeState(p);
	}

}

void ESM::IDLE_Sniper::Exit()
{
}

ESM::IDLE_Sniper::IDLE_Sniper(GameObject* _enemy, GameObject* _player, bool dir_num, float Time, GameObject* _bullet)
{
	enemy = _enemy;//enemyobject
	player = _player;//Playerobject
	dir = dir_num;
	dir_Time = Time;
	bullet = _bullet;
}
