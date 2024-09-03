#include "IDLE.h"
#include"GameObject.h"
#include"TransComponent.h"
#include"EnemyStateManager.h"
#include"ColliderManager.h"
#include"TimeManager.h"
#include"AiComponent.h"
#include"Chase.h"
#include "EnemyAttack.h"

//위치값과 속도제어 부분
//게임 오브젝트 자기자신을 받아야함

void ESM::IDLE::Init()
{
	//accumulatedTime = 0;
	idle_time = 0.f;
}

void ESM::IDLE::Update()
{
	//accumulatedTime = TimeManager::GetInst()->GetAccTime();
	m_fDt = (f32)AEFrameRateControllerGetFrameTime();
	idle_time += m_fDt;
	if (dir_Time != 0) 
	{
		//방향만 달라지게
		if (idle_time >= dir_Time)//5.0f느낌
		{
			// 시간 초기화
			//TimeManager::GetInst()->SetAccTime(0.0f);
			idle_time = 0.f;
			m_fDt = 0.f;
			// 추가로 필요한 로직을 여기에 작성
			//std::cout << dir_Time << " Turn Dir" << std::endl;
			dir = !(dir);
		}
	}



	if (ColliderManager::GetInst()->PlayerSearch(enemy, player, dir, 16.f, 8.f, 1.f))
	{
		//std::cout << "ChaseMode" << std::endl;
		AiComponent* enemy_ai = (AiComponent*)enemy->FindComponent("Ai");

		ESM::Chase* p = new ESM::Chase(enemy, player, dir, dir_Time, platform, e_state_name);
		//ESM::EnemyStateManager::GetInst()->ChangeState(p);
		enemy_ai->Change_State(p);
	}

}

void ESM::IDLE::Exit()
{
	//delete enemy;
	//obj를 다 날리면 남아있는지 죽어있는지?
}

ESM::IDLE::IDLE(GameObject* _enemy, GameObject* _player, bool dir_num, float Time, GameObject* _platform, std::string state_name)
{
	enemy = _enemy;//enemyobject
	player = _player;//Playerobject
	dir = dir_num;
	dir_Time = Time;
	platform = _platform;
	e_state_name = state_name;

}
