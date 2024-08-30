#include "Chase.h"
#include"IDLE.h"
#include"GameObject.h"
#include"TransComponent.h"
#include"EnemyStateManager.h"
#include"ColliderManager.h"
#include"TimeManager.h"
#include"TestLevel.h"
#include "EnemyAttack.h"

void ESM::Chase::Init()
{
	std::cout << "Chase Init" << std::endl;
	TimeManager::GetInst()->SetAccTime(0.0f);
}

void ESM::Chase::Update()
{
	//�ۿ��ٰ� ���ֱ�
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

	if (ColliderManager::GetInst()->PlayerSearch(Chase_enemy, Player, dir_state, 16.f, 8.f,1.f))
	{
		TimeManager::GetInst()->SetAccTime(0.0f);
		Chase_outTime = 0.0f;
		//std::cout << "Chase" << std::endl;//�Ѿư��ٴ� ���� pos���� �������ָ鼭 ������
		TransComponent* player_trs = (TransComponent*)Player->FindComponent("Transform");
		TransComponent* enemy_trs = (TransComponent*)Chase_enemy->FindComponent("Transform");
		playerPos = player_trs->GetPos();
		enemyPos = enemy_trs->GetPos();
		chaseVec.x = playerPos.x - enemyPos.x;
		chaseVec.y = playerPos.y - enemyPos.y;
		AEVec2Normalize(&unitChaseVec, &chaseVec);

		//�� �κ� �ٽ� �����
		enemy_trs->AddPos(unitChaseVec);
		//if�� �������̸� dir_state�� �ȹٲٴٰ�.
		// else if�� ���� false�� ������
		//dir_state = !(dir_state); �̰ɻ���Ѵ�. 


		if (ColliderManager::GetInst()->MeleeEnemyAttack(Chase_enemy, Player, dir_state)) 
		{
			ESM::EnemyAttack* p = new ESM::EnemyAttack(Chase_enemy, Player, dir_state, dir_Time);
			ESM::EnemyStateManager::GetInst()->ChangeState(p);
		}
	}
	else 
	{
		Chase_outTime = TimeManager::GetInst()->GetAccTime();
		if (Chase_outTime < 5.0f)
		{
			std::cout << Chase_outTime << std::endl;
			TransComponent* player_trs = (TransComponent*)Player->FindComponent("Transform");
			TransComponent* enemy_trs = (TransComponent*)Chase_enemy->FindComponent("Transform");
			playerPos = player_trs->GetPos();
			enemyPos = enemy_trs->GetPos();
			chaseVec.x = playerPos.x - enemyPos.x;
			chaseVec.y = playerPos.y - enemyPos.y;
			AEVec2Normalize(&unitChaseVec, &chaseVec);
			enemy_trs->AddPos(unitChaseVec);
			std::cout << "Chase" << std::endl;
		}
		else 
		{
			Chase_outTime = 0.0f;
			std::cout << "Chase Fail" << std::endl;
			ESM::IDLE* p = new ESM::IDLE(Chase_enemy, Player, dir_state, dir_Time);
			ESM::EnemyStateManager::GetInst()->ChangeState(p);
		}
	}

}

void ESM::Chase::Exit()
{
}

ESM::Chase::Chase(GameObject* _enemy, GameObject* _player, bool dir,float Time)
{
	Chase_enemy = _enemy;
	Player = _player;
	dir_state = dir;
	dir_Time = Time;
}

