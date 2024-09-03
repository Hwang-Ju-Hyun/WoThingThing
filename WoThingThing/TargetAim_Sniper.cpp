#include "TargetAim_Sniper.h"
#include "IDLE_Sniper.h"
#include"GameObject.h"
#include"TransComponent.h"
#include"SpriteComponent.h"
#include"EnemyStateManager.h"
#include"ColliderManager.h"
#include"TimeManager.h"
#include"AiComponent.h"

void ESM::TargetAim_Sniper::Init()
{
	bullet_Vec = { 0.f, 0.f };
	bullet_const = { 50.f, 50.f };

	m_fDt = 0;
	AttackDelay = 0;
	std::cout << "Chase Init" << std::endl;
	TimeManager::GetInst()->SetAccTime(0.0f);

	//TargetOn_Time = 0;
	m_fDt_Target = 0;


	TransComponent* bullet_trs = (TransComponent*)bullet->FindComponent("Transform");
	bullet_trs->SetScale({ 0, 0 }); // �Ѿ��� ó������ ������ �ʵ��� ũ�� 0���� ����

}

void ESM::TargetAim_Sniper::Update()
{
	// �� �κ��� �Ѿ�� ����Ǵ� �κ�
	TransComponent* player_trs = (TransComponent*)Player->FindComponent("Transform");
	TransComponent* enemy_trs = (TransComponent*)TargetAim_enemy->FindComponent("Transform");
	playerPos = player_trs->GetPos();
	enemyPos = enemy_trs->GetPos();
	chaseVec.x = playerPos.x - enemyPos.x;
	chaseVec.y = playerPos.y - enemyPos.y;
	if (!(ColliderManager::GetInst()->isFacingtheSameDirection(chaseVec, dir_state)))
	{
		dir_state = !(dir_state);
	}


	//Bullet
	TransComponent* bullet_trs = (TransComponent*)bullet->FindComponent("Transform");
	SpriteComponent* bullet_spr = (SpriteComponent*)bullet->FindComponent("Sprite");

	//�������� �κ�
	if (ColliderManager::GetInst()->PlayerSearch(TargetAim_enemy, Player, dir_state, 20.f, 10.f, 10.f))
	{
		m_fDt_Target = 0.0f;
		Search_outTime = 0.0f;

		//���� �����̴� ���� �ð��� ����ؼ� ���� �������
		m_fDt = (f32)AEFrameRateControllerGetFrameTime();
		AttackDelay += m_fDt;
		if (AttackDelay >= 3.0f)//���� ������
		{
			// �Ѿ� ��ġ �� ���� �ʱ�ȭ
			bullet_trs->SetPos(enemy_trs->GetPos());
			bulletPos = bullet_trs->GetPos();
			bullet_enemy_sub.x = playerPos.x - bulletPos.x;
			bullet_enemy_sub.y = playerPos.y - bulletPos.y;
			AEVec2Normalize(&nor_dVec_bullet, &bullet_enemy_sub);

			// �Ѿ� �ӵ� �� ���� ����
			if (AEInputCheckCurr(AEVK_LSHIFT)) 
			{
				bullet_Vec.x = nor_dVec_bullet.x * (bullet_const.x * 0.3f);
				bullet_Vec.y = nor_dVec_bullet.y * (bullet_const.y * 0.3f);
				//bullet_Vec.x = nor_dVec_bullet.x * (bullet_const.x * m_fDt);
				//bullet_Vec.y = nor_dVec_bullet.y * (bullet_const.y * m_fDt);
			}
			else
			{
				bullet_Vec.x = nor_dVec_bullet.x * bullet_const.x;
				bullet_Vec.y = nor_dVec_bullet.y * bullet_const.y;
			}
			// �Ѿ��� ���̰� �ϰ�, ������ ����
			bullet_trs->SetScale({ 10, 10 }); // �Ѿ��� ���̰� ����
			std::cout << "Shoot" << std::endl;
			AttackDelay = 0.f;
		}
		bullet_trs->AddPos(bullet_Vec); // �Ѿ��� �̵���Ŵ
		//�� �κ� �ٽ� �����
		if ((ColliderManager::GetInst()->isFacingtheSameDirection(chaseVec, dir_state)))
		{
			dir_state = !(dir_state);
		}
	}
	else
	{
		m_fDt_Target = (f32)AEFrameRateControllerGetFrameTime();
		Search_outTime += m_fDt_Target;
		if (Search_outTime < 2.0f)
		{

			//���� �κп� ������ �Ȱ��� Ÿ���ϰ� �����ϴ� ��� �ֱ�
			std::cout << "TargetOn" << std::endl;
			m_fDt = (f32)AEFrameRateControllerGetFrameTime();
			AttackDelay += m_fDt;
			if (AttackDelay >= 3.0f) // 3�ʸ��� �Ѿ� �߻�
			{
				// �Ѿ��� ��ġ�� ���� ��ġ�� �ʱ�ȭ
				bullet_trs->SetPos(enemy_trs->GetPos());
				bulletPos = bullet_trs->GetPos();

				// �÷��̾��� ������ ��ġ�κ��� ���� ���͸� ���
				bullet_enemy_sub.x = playerPos.x - bulletPos.x;
				bullet_enemy_sub.y = playerPos.y - bulletPos.y;
				AEVec2Normalize(&nor_dVec_bullet, &bullet_enemy_sub);


				// �Ѿ� �ӵ� ���� ���
				bullet_Vec.x = nor_dVec_bullet.x * bullet_const.x;
				bullet_Vec.y = nor_dVec_bullet.y * bullet_const.y;

				// �Ѿ��� ���̰� �ϰ�, ���� �����Ӻ��� �̵� ����
				bullet_trs->SetScale({ 10, 10 }); // �Ѿ��� ���̰� ����

				AttackDelay = 0.f; // ���� ������ �ʱ�ȭ
			}
			if (AEInputCheckCurr(AEVK_LSHIFT)) 
			{
				bullet_trs->AddPos(bullet_Vec.x * m_fDt, bullet_Vec.y * m_fDt);
			}
			else 
			{
				bullet_trs->AddPos(bullet_Vec);
			}
		}
		else
		{
			Search_outTime = 0.0f;
			m_fDt_Target = 0.0f;
			std::cout << "Target on Fail" << std::endl;
			AiComponent* enemy_ai = (AiComponent*)TargetAim_enemy->FindComponent("Ai");
			ESM::IDLE_Sniper* p = new ESM::IDLE_Sniper(TargetAim_enemy, Player, dir_state, dir_Time, bullet);
			//ESM::EnemyStateManager::GetInst()->ChangeState(p);
			enemy_ai->Change_State(p);
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
