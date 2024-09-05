#include "EnemyAttack.h"
#include "Chase.h"
#include"IDLE.h"
#include"GameObject.h"
#include"TransComponent.h"
#include"EnemyStateManager.h"
#include"ColliderManager.h"
#include"TimeManager.h"
#include"TestLevel.h"
#include"AiComponent.h"
#include"PlayerComponent.h"
#include "ResourceManager.h"
#include "AudioResource.h"
#include"EnemyAnimationComponent.h"

void ESM::EnemyAttack::Init()
{
	EnemyAnimationComponent* Enemy_meleeani = (EnemyAnimationComponent*)Attack_enemy->FindComponent("EnemyAnimation");
	Enemy_meleeani->ChangeAnimation("MeleeAttack", 1, 5, 5, 0.04);
	melee_DelayAtk = 0.f;
	m_fDt = 0.f;
}

void ESM::EnemyAttack::Update()
{

	//melee_DelayAtk = TimeManager::GetInst()->GetAccTime();

	//TransComponent* player_trs = (TransComponent*)Player->FindComponent("Transform");

	PlayerComponent* player_comp = (PlayerComponent*)Player->FindComponent("PlayerComp");

	if (ColliderManager::GetInst()->MeleeEnemyAttack(Attack_enemy, Player, dir_state))
	{
		m_fDt = (f32)AEFrameRateControllerGetFrameTime();
		melee_DelayAtk += m_fDt;
		if (melee_DelayAtk > 0.2f)
		{
			auto res_EnemyMeleeAtk = ResourceManager::GetInst()->Get("sfx_EnemyMeleeAtk", "Assets/EnemyMeleeAttack.mp3");
			AudioResource* bgm_res = static_cast<AudioResource*>(res_EnemyMeleeAtk);
			bgm_res->SetSFXorMusic(Sound::SFX);
			auto bgm_audio = bgm_res->GetAudio();
			auto bgm_audioGroup = bgm_res->GetAudioGroup();
			AEAudioPlay(bgm_audio, bgm_audioGroup, 1.f, 1.f, 0);

			player_comp->TakeDamge();
			m_fDt = 0.0f;
			melee_DelayAtk = 0.f;

			auto resDead = ResourceManager::GetInst()->Get("sfx_PlayerDead", "Assets/Dead1.wav");
			AudioResource* bgm_resDead = static_cast<AudioResource*>(resDead);
			bgm_resDead->SetSFXorMusic(Sound::SFX);
			auto bgm_audioDead = bgm_resDead->GetAudio();
			auto bgm_audioGroupDead = bgm_resDead->GetAudioGroup();
			AEAudioPlay(bgm_audioDead, bgm_audioGroupDead, 1.f, 1.f, 0);
		}
	}
	else 
	{
		AiComponent* enemy_ai = (AiComponent*)Attack_enemy->FindComponent("Ai");
		ESM::Chase* p = new ESM::Chase(Attack_enemy, Player, dir_state, dir_Time, PlatForm, e_state_name, FirstPlacePos);
		//ESM::EnemyStateManager::GetInst()->ChangeState(p);
		enemy_ai->Change_State(p);
	}
}

void ESM::EnemyAttack::Exit()
{
}

ESM::EnemyAttack::EnemyAttack(GameObject* _enemy, GameObject* _player, bool dir, float Time, GameObject* _platform, std::string _state_name, AEVec2 _FirstPlacePos)
{
	Attack_enemy = _enemy;
	Player = _player;
	dir_state = dir;
	dir_Time = Time;
	PlatForm = _platform;
	e_state_name = _state_name;
	FirstPlacePos = _FirstPlacePos;
}
