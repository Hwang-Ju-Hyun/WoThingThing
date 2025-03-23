#include "IDLE_Sniper.h"
#include"GameObject.h"
#include"TransComponent.h"
#include"EnemyStateManager.h"
#include"ColliderManager.h"
#include"TimeManager.h"
#include "TargetAim_Sniper.h"
#include"SpriteComponent.h"
#include"AiComponent.h"
#include"EnemyAnimationComponent.h"
void ESM::IDLE_Sniper::Init()
{
	EnemyAnimationComponent* Enemy_sniperani = (EnemyAnimationComponent*)enemy->FindComponent("EnemyAnimation");
	Enemy_sniperani->ChangeAnimation("SniperIdle", 1, 12, 12, 0.1);

	accumulatedTime = 0;
	//TimeManager::GetInst()->SetAccTime(0.0f);
	m_fDt = 0;
}

void ESM::IDLE_Sniper::Update()
{
	EnemyAnimationComponent* Enemy_sniperani = (EnemyAnimationComponent*)enemy->FindComponent("EnemyAnimation");

	//accumulatedTime = TimeManager::GetInst()->GetAccTime();
	m_fDt = (f32)AEFrameRateControllerGetFrameTime();
	accumulatedTime += m_fDt;
	if (dir_Time != 0)
	{
		//방향만 달라지게
		if (accumulatedTime >= dir_Time)//5.0f느낌
		{
			// 시간 초기화
			m_fDt = 0.f;
			accumulatedTime = 0.f;
			// 추가로 필요한 로직을 여기에 작성
			//std::cout << dir_Time << " Turn Dir" << std::endl;
			dir = !(dir);
			Enemy_sniperani->SetEnemyDir(dir);
		}
	}

	
	if (ColliderManager::GetInst()->PlayerSearch(enemy, player, dir, 18.f, 18.f,10.f))//여기에 감지범위 조정
	{
		//스나이퍼는 바로 공격모드로 들어가게한다.
		AiComponent* enemy_ai = (AiComponent*)enemy->FindComponent("Ai");
		ESM::TargetAim_Sniper* p = new ESM::TargetAim_Sniper(enemy, player, dir, dir_Time);
		//ESM::EnemyStateManager::GetInst()->ChangeState(p);
		enemy_ai->Change_State(p);
	}

}

void ESM::IDLE_Sniper::Exit()
{
}

ESM::IDLE_Sniper::IDLE_Sniper(GameObject* _enemy, GameObject* _player, bool dir_num, float Time)
{
	enemy = _enemy;//enemyobject
	player = _player;//Playerobject
	dir = dir_num;
	dir_Time = Time;
}
