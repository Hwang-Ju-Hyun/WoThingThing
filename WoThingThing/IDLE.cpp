#include "IDLE.h"
#include"GameObject.h"
#include"TransComponent.h"
#include"EnemyStateManager.h"
#include"ColliderManager.h"
#include"TimeManager.h"
#include"TestLevel.h"//보는 방향 업데이트를 위해서


//위치값과 속도제어 부분
//게임 오브젝트 자기자신을 받아야함
bool ESM::IDLE::SearchPlayer = false;

void ESM::IDLE::Init()
{
	accumulatedTime = 0;
}

void ESM::IDLE::Update()
{
	accumulatedTime = TimeManager::GetInst()->GetAccTime();
	if (accumulatedTime >= 5.0f)
	{
		// 시간 초기화
		TimeManager::GetInst()->SetAccTime(0.0f);
		// 추가로 필요한 로직을 여기에 작성
		std::cout << "5 seconds passed, resetting timer." << std::endl;

		Level::TestLevel::enemy_dir = !(Level::TestLevel::enemy_dir);
	}

	if (SearchPlayer) 
	{
		//ESM::EnemyStateManager::GetInst()->ChangeState(new ESM::); Chase 추가 
		//std::cout << "ChaseMode" << std::endl;
	}

}

void ESM::IDLE::Exit()
{
	//obj를 다 날리면 남아있는지 죽어있는지?
}

ESM::IDLE::IDLE(GameObject* _owner)
{
	enemy = _owner;
}
