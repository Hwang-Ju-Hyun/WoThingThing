#include "IDLE.h"
#include"GameObject.h"
#include"TransComponent.h"
#include"EnemyStateManager.h"
#include"ColliderManager.h"
#include"TimeManager.h"
#include"AiComponent.h"
#include"Chase.h"
#include "EnemyAttack.h"

//��ġ���� �ӵ����� �κ�
//���� ������Ʈ �ڱ��ڽ��� �޾ƾ���

void ESM::IDLE::Init()
{
	//accumulatedTime = 0;
	idle_time = 0.f;

}

bool isOnFirstPlace(AEVec2 nowPos, AEVec2 FirstPos) 
{
	float epsilon = 1.f;
	float dx = nowPos.x - FirstPos.x;

	if (fabs(dx) < epsilon)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void ESM::IDLE::Update()
{
	//accumulatedTime = TimeManager::GetInst()->GetAccTime();

	TransComponent* enemy_trs = (TransComponent*)enemy->FindComponent("Transform");

	if (!(isOnFirstPlace(enemy_trs->GetPos(), FirstPlacePos))) 
	{
		//std::cout << FirstPlacePos.x << std::endl;
		enemyPos = enemy_trs->GetPos();
		returnVec.x = FirstPlacePos.x - enemyPos.x;
		returnVec.y = FirstPlacePos.y - enemyPos.y;
		AEVec2Normalize(&unitReturnVec, &returnVec);
		if (!(ColliderManager::GetInst()->isFacingtheSameDirection(returnVec, dir)))
		{
			//Chase_outTime = 0.0f;
			dir = !(dir);
		}
		enemy_trs->AddPos(unitReturnVec);
		//std::cout << enemy_trs->GetPos().x << std::endl;
	}
	else 
	{
		m_fDt = (f32)AEFrameRateControllerGetFrameTime();
		idle_time += m_fDt;

		if (dir_Time != 0)
		{
			//���⸸ �޶�����
			if (idle_time >= dir_Time)//5.0f����
			{
				// �ð� �ʱ�ȭ
				//TimeManager::GetInst()->SetAccTime(0.0f);
				idle_time = 0.f;
				m_fDt = 0.f;
				// �߰��� �ʿ��� ������ ���⿡ �ۼ�
				//std::cout << dir_Time << " Turn Dir" << std::endl;
				dir = !(dir);
			}
		}
	}


	if (ColliderManager::GetInst()->PlayerSearch(enemy, player, dir, 16.f, 8.f, 1.f))
	{
		//std::cout << "ChaseMode" << std::endl;
		AiComponent* enemy_ai = (AiComponent*)enemy->FindComponent("Ai");

		ESM::Chase* p = new ESM::Chase(enemy, player, dir, dir_Time, platform, e_state_name, FirstPlacePos);
		//ESM::EnemyStateManager::GetInst()->ChangeState(p);
		enemy_ai->Change_State(p);
	}

}

void ESM::IDLE::Exit()
{
	//delete enemy;
	//obj�� �� ������ �����ִ��� �׾��ִ���?
}

ESM::IDLE::IDLE(GameObject* _enemy, GameObject* _player, bool dir_num, float Time, GameObject* _platform, std::string state_name, AEVec2 _FirstPlacePos)
{
	enemy = _enemy;//enemyobject
	player = _player;//Playerobject
	dir = dir_num;
	dir_Time = Time;
	platform = _platform;
	e_state_name = state_name;
	FirstPlacePos = _FirstPlacePos;
}
