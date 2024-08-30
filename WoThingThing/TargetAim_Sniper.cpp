#include "TargetAim_Sniper.h"
#include "IDLE_Sniper.h"
#include"GameObject.h"
#include"TransComponent.h"
#include"SpriteComponent.h"
#include"EnemyStateManager.h"
#include"ColliderManager.h"
#include"TimeManager.h"

void ESM::TargetAim_Sniper::Init()
{
	bullet_Vec = { 0.f, 0.f };
	bullet_const = { 40.f, 40.f };

	AttackDelay = 0;
	std::cout << "Chase Init" << std::endl;
	TimeManager::GetInst()->SetAccTime(0.0f);
}

void ESM::TargetAim_Sniper::Update()
{
	// �� �κ��� �Ѿ�� ����Ǵ� �κ�
	TransComponent* player_trs = (TransComponent*)Player->FindComponent("Transform");
	TransComponent* enemy_trs = (TransComponent*)TargetAim_enemy->FindComponent("Transform");
	//TransComponent* bullet_trs = (TransComponent*)bullet->FindComponent("Transform");
	//���� �����ؾ��ϴ� �κ�
	//bullet_trs->SetScale({ 0,0 });
	playerPos = player_trs->GetPos();
	enemyPos = enemy_trs->GetPos();
	//bulletPos = bullet_trs->GetPos();
	chaseVec.x = playerPos.x - enemyPos.x;
	chaseVec.y = playerPos.y - enemyPos.y;
	//AEVec2Normalize(&nor_dVec_bullet, &chaseVec);
	if (!(ColliderManager::GetInst()->isFacingtheSameDirection(chaseVec, dir_state)))
	{
		dir_state = !(dir_state);
	}



	//�������� �κ�
	if (ColliderManager::GetInst()->PlayerSearch(TargetAim_enemy, Player, dir_state, 20.f, 10.f, 10.f))
	{
		TimeManager::GetInst()->SetAccTime(0.0f);
		Search_outTime = 0.0f;
	    
		//���� �����̴� ���� �ð��� ����ؼ� ���� �������
		m_fDt = (f32)AEFrameRateControllerGetFrameTime();
		AttackDelay += m_fDt;

		if (AttackDelay >= 3.0f)//���� ������
		{
			//std::cout << " Shoot" << std::endl;
			//bullet_Vec.x = nor_dVec_bullet.x * bullet_const.x;
			//bullet_Vec.y = nor_dVec_bullet.y * bullet_const.y;
			//SpriteComponent* bullet_spr = (SpriteComponent*)bullet->FindComponent("Sprite");
			//bullet_trs->SetPos(enemy_trs->GetPos());
			//bullet_trs->SetScale({ 10, 10 });
			std::cout << "Shoot" << std::endl;
			AttackDelay = 0.f;
		}

		//�� �κ� �ٽ� �����
		if ((ColliderManager::GetInst()->isFacingtheSameDirection(chaseVec, dir_state)))
		{
			dir_state = !(dir_state);
		}
	}
	else
	{
		Search_outTime = TimeManager::GetInst()->GetAccTime();
		if (Search_outTime < 2.0f)
		{
			//���� �κп� ������ �Ȱ��� Ÿ���ϰ� �����ϴ� ��� �ֱ�
			std::cout << "TargetOn" << std::endl;
		}
		else
		{
			Search_outTime = 0.0f;
			std::cout << "Target on Fail" << std::endl;
			ESM::IDLE_Sniper* p = new ESM::IDLE_Sniper(TargetAim_enemy, Player, dir_state, dir_Time, bullet);
			ESM::EnemyStateManager::GetInst()->ChangeState(p);

		}
	}
}

void ESM::TargetAim_Sniper::Exit()
{
}

ESM::TargetAim_Sniper::TargetAim_Sniper(GameObject* _enemy, GameObject* _player, bool dir, float Time, GameObject* _bullet)
{
	TargetAim_enemy = _enemy;
	Player = _player;
	dir_state = dir;
	dir_Time = Time;
	bullet = _bullet;
}
