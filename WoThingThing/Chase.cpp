#include "Chase.h"
#include"IDLE.h"
#include"GameObject.h"
#include"TransComponent.h"
#include"EnemyStateManager.h"
#include"ColliderManager.h"
#include"TimeManager.h"
#include"TestLevel.h"
#include "EnemyAttack.h"
#include"AiComponent.h"
#include"GoManager.h"
#include"EventManager.h"

void ESM::Chase::Init()
{
	std::cout << "Chase Init" << std::endl;
	//TimeManager::GetInst()->SetAccTime(0.0f);
	//Chase_time = 0.f;
	m_fDt = 0.f;
	Chase_outTime = 0.f;
	Subscriber.Enemy_Chase = this;
	EventManager::GetInst()->AddEntity("EnemyPlatformCollisionEvent", &Subscriber);
}

void ESM::Chase::Update()
{
	float dt = AEFrameRateControllerGetFrameTime();//시간 느려지게하는 용

	//밖에다가 해주기
	TransComponent* player_trs = (TransComponent*)Player->FindComponent("Transform");
	TransComponent* enemy_trs = (TransComponent*)Chase_enemy->FindComponent("Transform");
	playerPos = player_trs->GetPos();
	enemyPos = enemy_trs->GetPos();
	chaseVec.x = playerPos.x - enemyPos.x;
	chaseVec.y = playerPos.y - enemyPos.y;

	if (!(ColliderManager::GetInst()->isFacingtheSameDirection(chaseVec, dir_state)))
	{
		//Chase_outTime = 0.0f;
		dir_state = !(dir_state);
	}


	m_fDt = (f32)AEFrameRateControllerGetFrameTime();
	Chase_outTime += m_fDt;

	bool isEnemyNotOnPlatformEdge = ColliderManager::GetInst()->PlayerSearch(Chase_enemy, PlatForm, dir_state, 3.f, -1.f, 2.f);
	bool isPlayerInsideTheRadar = ColliderManager::GetInst()->PlayerSearch(Chase_enemy, Player, dir_state, 16.f, 8.f, 1.f);
	bool ShouldSlowTime = AEInputCheckCurr(AEVK_LSHIFT);
	
	if (isPlayerInsideTheRadar)
	{
		m_fDt = 0.f;
		Chase_outTime = 0.0f;
		//std::cout << "Chase" << std::endl;//쫓아간다는 구문 pos값을 조정해주면서 움직임
		TransComponent* player_trs = (TransComponent*)Player->FindComponent("Transform");
		TransComponent* enemy_trs = (TransComponent*)Chase_enemy->FindComponent("Transform");
		playerPos = player_trs->GetPos();
		enemyPos = enemy_trs->GetPos();
		chaseVec.x = playerPos.x - enemyPos.x;
		chaseVec.y = playerPos.y - enemyPos.y;
		AEVec2Normalize(&unitChaseVec, &chaseVec);

		//PLATFORM 양끝을 벗어나지 않게 하는곳을 체크 

		if (ShouldSlowTime)
		{
			// 속도를 줄이기 위해 0.5배로 느리게 이동하도록 설정
			if (isEnemyNotOnPlatformEdge)
			{
				slowChase.x = unitChaseVec.x * 0.98f * dt * 5.f;
				slowChase.y = unitChaseVec.y * 0.98f * dt * 5.f;
				enemy_trs->AddPos(slowChase);
			}
			else
			{
				//std::cout << "Stop" << std::endl;
				StopVec.x = 0;
				StopVec.y = 0;
				enemy_trs->AddPos(StopVec);
			}
		}
		else
		{
			//이 부분 다시 물어보기
			if (isEnemyNotOnPlatformEdge)
			{
				enemy_trs->AddPos(unitChaseVec);
				
			}
			else 
			{
				//std::cout << "Stop" << std::endl;
				StopVec.x = 0;
				StopVec.y = 0;
				enemy_trs->AddPos(StopVec);
			}
		}
		//if (AEInputCheckCurr(AEVK_LSHIFT))
		//{
		//	// 속도를 줄이기 위해 0.5배로 느리게 이동하도록 설정
		//	slowChase.x = unitChaseVec.x * 0.98f * dt * 5.f;
		//	slowChase.y = unitChaseVec.y * 0.98f * dt * 5.f;
		//	enemy_trs->AddPos(slowChase);
		//
		//}
		//else 
		//{
		//	//이 부분 다시 물어보기
		//	enemy_trs->AddPos(unitChaseVec);
		//}

		if (ColliderManager::GetInst()->MeleeEnemyAttack(Chase_enemy, Player, dir_state))
		{
			AiComponent* enemy_ai = (AiComponent*)Chase_enemy->FindComponent("Ai");
			ESM::EnemyAttack* p = new ESM::EnemyAttack(Chase_enemy, Player, dir_state, dir_Time, PlatForm, e_state_name);
			//ESM::EnemyStateManager::GetInst()->ChangeState(p);
			enemy_ai->Change_State(p);
		}
	}
	else
	{
		if (Chase_outTime < 5.0f)
		{
			//std::cout << Chase_outTime << std::endl;
			TransComponent* player_trs = (TransComponent*)Player->FindComponent("Transform");
			TransComponent* enemy_trs = (TransComponent*)Chase_enemy->FindComponent("Transform");
			playerPos = player_trs->GetPos();
			enemyPos = enemy_trs->GetPos();
			chaseVec.x = playerPos.x - enemyPos.x;
			chaseVec.y = playerPos.y - enemyPos.y;
			AEVec2Normalize(&unitChaseVec, &chaseVec);
			if (ShouldSlowTime)
			{
				// 속도를 줄이기 위해 0.5배로 느리게 이동하도록 설정
				if (isEnemyNotOnPlatformEdge)
				{
					slowChase.x = unitChaseVec.x * 0.98f * dt * 5.f;
					slowChase.y = unitChaseVec.y * 0.98f * dt * 5.f;
					enemy_trs->AddPos(slowChase);
				}
				else
				{
					//std::cout << "Stop" << std::endl;
					StopVec.x = 0;
					StopVec.y = 0;
					enemy_trs->AddPos(StopVec);
				}
			}
			else 
			{
				if (isEnemyNotOnPlatformEdge)
				{
					enemy_trs->AddPos(unitChaseVec);
				}
				else
				{
					//std::cout << "Stop" << std::endl;
					StopVec.x = 0;
					StopVec.y = 0;
					enemy_trs->AddPos(StopVec);
				}
			}
			//std::cout << "Chase" << std::endl;
			//AEVec2Normalize(&unitChaseVec, &chaseVec);
			//enemy_trs->AddPos(unitChaseVec.x * dt, unitChaseVec.y);
		}
		else
		{
			m_fDt = 0.f;
			Chase_outTime = 0.0f;
			std::cout << "Chase Fail" << std::endl;
			AiComponent* enemy_ai = (AiComponent*)Chase_enemy->FindComponent("Ai");
			ESM::IDLE* p = new ESM::IDLE(Chase_enemy, Player, dir_state, dir_Time, PlatForm, e_state_name);
			enemy_ai->Change_State(p);
			//ESM::EnemyStateManager::GetInst()->ChangeState(p);
		}
	}

}

void ESM::Chase::Exit()
{
}

ESM::Chase::Chase(GameObject* _enemy, GameObject* _player, bool dir, float Time, GameObject* _platform, std::string state_name)
{
	Chase_enemy = _enemy;
	Player = _player;
	dir_state = dir;
	dir_Time = Time;
	PlatForm = _platform;
	e_state_name = state_name;
}

