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


void ESM::TargetAim_Sniper::Init()
{
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
	// 이 부분은 넘어가면 적용되는 부분
	TransComponent* player_trs = (TransComponent*)Player->FindComponent("Transform");
	TransComponent* enemy_trs = (TransComponent*)TargetAim_enemy->FindComponent("Transform");
	PlayerComponent* player_comp = (PlayerComponent*)Player->FindComponent("PlayerComp");

	playerPos = player_trs->GetPos();
	enemyPos = enemy_trs->GetPos();
	chaseVec.x = playerPos.x - enemyPos.x;
	chaseVec.y = playerPos.y - enemyPos.y;

	if (!(ColliderManager::GetInst()->isFacingtheSameDirection(chaseVec, dir_state)))
	{
		dir_state = !(dir_state);
	}

	//총알 Noramlize
	AEVec2Normalize(&nor_dVec, &chaseVec);

	//실질적인 부분
	if (ColliderManager::GetInst()->PlayerSearch(TargetAim_enemy, Player, dir_state, 30.f, 30.f, 10.f))
	{
		m_fDt_Target = 0.0f;
		Search_outTime = 0.0f;

		//공격 딜레이는 따로 시간을 줘야해서 따로 만들어줌
		m_fDt = (f32)AEFrameRateControllerGetFrameTime();
		AttackDelay += m_fDt;
		if (AttackDelay >= 0.5f)//공격 딜레이
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

		//bullet_trs->AddPos(bullet_Vec); // 총알을 이동시킴
		//이 부분 다시 물어보기
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

			//여기 부분에 위에랑 똑같이 타켓하고 공격하는 기능 넣기
			m_fDt = (f32)AEFrameRateControllerGetFrameTime();
			AttackDelay += m_fDt;
			if (AttackDelay >= 0.5f) // 3초마다 총알 발사
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
