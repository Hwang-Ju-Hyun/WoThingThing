#include "IDLE.h"
#include"GameObject.h"
#include"TransComponent.h"
#include"EnemyStateManager.h"
#include"ColliderManager.h"
#include"TimeManager.h"
#include"TestLevel.h"//보는 방향 업데이트를 위해서(나중에는 사용될 스테이지에서 사용할 예정)
//나중에 보는값을 고정시키지말고 내가 직접 입력하여 방향 정하기
#include"Chase.h"
#include "EnemyAttack.h"

//위치값과 속도제어 부분
//게임 오브젝트 자기자신을 받아야함

void ESM::IDLE::Init()
{
	accumulatedTime = 0;
	TimeManager::GetInst()->SetAccTime(0.0f);
}

void ESM::IDLE::Update()
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



	if (ColliderManager::GetInst()->PlayerSearch(enemy, player, dir, 16.f, 8.f, 1.f))
	{
		//std::cout << "ChaseMode" << std::endl;
		ESM::Chase* p = new ESM::Chase(enemy, player, dir, dir_Time);
		ESM::EnemyStateManager::GetInst()->ChangeState(p);
	}

}

void ESM::IDLE::Exit()
{
	//delete enemy;
	//obj를 다 날리면 남아있는지 죽어있는지?
}

ESM::IDLE::IDLE(GameObject* _enemy, GameObject* _player, bool dir_num, float Time)
{
	enemy = _enemy;//enemyobject
	player = _player;//Playerobject
	dir = dir_num;
	dir_Time = Time;
}
