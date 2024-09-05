#include "TargetAim_Sniper.h"
#include "IDLE_Sniper.h"
#include"GameObject.h"
#include"TransComponent.h"
#include"SpriteComponent.h"
#include"EnemyStateManager.h"
#include"ColliderManager.h"
#include"TimeManager.h"
#include"AiComponent.h"
#include"PlayerComponent.h"
#include"GoManager.h"
#include "AudioResource.h"
#include "ResourceManager.h"
#include "Bullet.h"
#include "BulletComponent.h"
#include"EnemyAnimationComponent.h"

void ESM::TargetAim_Sniper::Init()
{
	EnemyAnimationComponent* Enemy_sniperani = (EnemyAnimationComponent*)TargetAim_enemy->FindComponent("EnemyAnimation");
	Enemy_sniperani->ChangeAnimation("SniperShootIdle", 1, 1, 1, 0.1);
	bullet_Vec = { 0.f, 0.f };
	bullet_const = { 50.f, 50.f };

	m_fDt = 0;
	AttackDelay = 0;
	TimeManager::GetInst()->SetAccTime(0.0f);

	//TargetOn_Time = 0;
	m_fDt_Target = 0;
	nor_dVec = { 0,0 };
}

void ESM::TargetAim_Sniper::Update()
{
	// �� �κ��� �Ѿ�� ����Ǵ� �κ�
	TransComponent* player_trs = (TransComponent*)Player->FindComponent("Transform");
	TransComponent* enemy_trs = (TransComponent*)TargetAim_enemy->FindComponent("Transform");
	PlayerComponent* player_comp = (PlayerComponent*)Player->FindComponent("PlayerComp");
	EnemyAnimationComponent* Enemy_sniperani = (EnemyAnimationComponent*)TargetAim_enemy->FindComponent("EnemyAnimation");

	playerPos = player_trs->GetPos();
	enemyPos = enemy_trs->GetPos();
	chaseVec.x = playerPos.x - enemyPos.x;
	chaseVec.y = playerPos.y - enemyPos.y;

	if (!(ColliderManager::GetInst()->isFacingtheSameDirection(chaseVec, dir_state)))
	{
		dir_state = !(dir_state);
		Enemy_sniperani->SetEnemyDir(dir_state);
	}

	//�Ѿ� Noramlize
	AEVec2Normalize(&nor_dVec, &chaseVec);
	bool ShouldSlowTime = AEInputCheckCurr(AEVK_LSHIFT);
	//�������� �κ�
	if (ColliderManager::GetInst()->PlayerSearch(TargetAim_enemy, Player, dir_state, 18.f, 18.f, 10.f))
	{
		Enemy_sniperani->ChangeAnimation("SniperShoot", 1, 5, 5, 0.1);
		m_fDt_Target = 0.0f;
		Search_outTime = 0.0f;

		//���� �����̴� ���� �ð��� ����ؼ� ���� �������
		m_fDt = (f32)AEFrameRateControllerGetFrameTime();
		

		if (ShouldSlowTime) 
		{
			AttackDelay += m_fDt * 0.1;
		}
		else 
		{
			AttackDelay += m_fDt;
		}
		
		if (AttackDelay >= 0.5f)//���� ������
		{
			//bulletComp
			auto res_EnemyGun = ResourceManager::GetInst()->Get("sfx_EnemyGunShot", "Assets/GunShot.mp3");
			AudioResource* bgm_res = static_cast<AudioResource*>(res_EnemyGun);
			bgm_res->SetSFXorMusic(Sound::SFX);
			auto bgm_audio = bgm_res->GetAudio();
			auto bgm_audioGroup = bgm_res->GetAudioGroup();
			AEAudioPlay(bgm_audio, bgm_audioGroup, 1.f, 1.f, 0);
			CreateBullet(enemy_trs->GetPos(), nor_dVec, "EnemyBullet", true);
			AttackDelay = 0.f;
		}

		//bullet_trs->AddPos(bullet_Vec); // �Ѿ��� �̵���Ŵ
		//�� �κ� �ٽ� �����
		if ((ColliderManager::GetInst()->isFacingtheSameDirection(chaseVec, dir_state)))
		{
			dir_state = !(dir_state);
			Enemy_sniperani->SetEnemyDir(dir_state);
		}
	}
	else
	{
		Enemy_sniperani->ChangeAnimation("SniperShootIdle", 1, 1, 1, 0.1);
		m_fDt_Target = (f32)AEFrameRateControllerGetFrameTime();
		Search_outTime += m_fDt_Target;
		if (Search_outTime < 2.0f)
		{
			//���� �κп� ������ �Ȱ��� Ÿ���ϰ� �����ϴ� ��� �ֱ�
			m_fDt = (f32)AEFrameRateControllerGetFrameTime();
			if (ShouldSlowTime)
			{
				AttackDelay += m_fDt * 0.1;
			}
			else
			{
				AttackDelay += m_fDt;
			}
			if (AttackDelay >= 0.5f) // 3�ʸ��� �Ѿ� �߻�
			{

				CreateBullet(enemy_trs->GetPos(), nor_dVec, "EnemyBullet", true);
				AttackDelay = 0.f;
			}
		}
		else
		{
			Search_outTime = 0.0f;
			m_fDt_Target = 0.0f;
			AiComponent* enemy_ai = (AiComponent*)TargetAim_enemy->FindComponent("Ai");
			ESM::IDLE_Sniper* p = new ESM::IDLE_Sniper(TargetAim_enemy, Player, dir_state, dir_Time);
			//ESM::EnemyStateManager::GetInst()->ChangeState(p);
			enemy_ai->Change_State(p);
		}
	}


}

void ESM::TargetAim_Sniper::Exit()
{
}

ESM::TargetAim_Sniper::TargetAim_Sniper(GameObject* _enemy, GameObject* _player, bool dir, float Time)
{
	TargetAim_enemy = _enemy;
	Player = _player;
	dir_state = dir;
	dir_Time = Time;
}

AEVec2 ESM::TargetAim_Sniper::GetEnemyDvec()
{
	return nor_dVec;
}
