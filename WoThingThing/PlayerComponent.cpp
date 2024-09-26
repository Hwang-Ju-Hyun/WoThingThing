#include "PlayerComponent.h"
#include "TransComponent.h"
#include "SpriteComponent.h"
#include "CameraManager.h"

#include "Bullet.h"
#include "BulletComponent.h"

#include "GameObject.h"
#include "GoManager.h"
#include "ResourceManager.h"
#include "AudioResource.h"
#include "ImageResource.h"

#include "AEEngine.h"

PlayerComponent::PlayerComponent(GameObject* _owner) : BaseComponent(_owner)
{
	m_vVelocity = { 0.f, 0.f };

	dashVelocity = { 0.f, 0.f };
	dash_const = { 400.f, 400.f };
	jumpVelocity = { 0.f, 400.f };
	m_vGravity = { 0.f, 600.f };

	mouseAim = new GameObject("mouseAim");
	GoManager::GetInst()->AddObject(mouseAim);
	mouseAim->AddComponent("Transform", new TransComponent(mouseAim));
	mouseAim->AddComponent("Sprite", new SpriteComponent(mouseAim));
	ResourceManager::GetInst()->Get("Aim", "Assets/Aim_1.png");
	TransComponent* aim_trs = (TransComponent*)mouseAim->FindComponent("Transform");
	aim_trs->SetScale({ 50,50 });
	SpriteComponent* aim_spr = (SpriteComponent*)mouseAim->FindComponent("Sprite");
	ImageResource* aimResource = (ImageResource*)ResourceManager::GetInst()->FindRes("Aim");
	aim_spr->SetTexture(aimResource->GetImage());

	aim_line = new GameObject("AimLine");
	GoManager::GetInst()->AddObject(aim_line);
	aim_line->AddComponent("Transform", new TransComponent(aim_line));
	aim_line->AddComponent("Sprite", new SpriteComponent(aim_line));

	//
	gauge = new GameObject("Gauge");
	GoManager::GetInst()->AddObject(gauge);
	gauge->AddComponent("Transform", new TransComponent(gauge));
	gauge->AddComponent("Sprite", new SpriteComponent(gauge));
	//
	
	melee = nullptr;
	meleeState = false;
	meleeCooldown = 0.f;
	
	maniCapacity = 7.f;
	timeManipul = maniCapacity;
	manipulActive = false;	
	
	jumpCnt = 0;
	meleeAction = true;
	shotAction = false;
	obtainGun = false;
	
	invincibility = false;
	
	playerhealth = 1e9;
}

//About Player's movement
void PlayerComponent::Jump(float jumpVal)
{
	TransComponent* player_trs = static_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));
	AEVec2 pos = static_cast<TransComponent*>(player_trs)->GetPos();
	float dt = AEFrameRateControllerGetFrameTime();
	jumpVelocity.y = jumpVal;
	pos.y += jumpVelocity.y * dt;
	static_cast<TransComponent*>(player_trs)->SetPos(pos);
}
void PlayerComponent::Dash(AEVec2 directVec)
{
	TransComponent* player_trs = static_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));
	AEVec2 pos = static_cast<TransComponent*>(player_trs)->GetPos();

	float dt = AEFrameRateControllerGetFrameTime();

	dashVelocity.x = directVec.x * dash_const.x;
	dashVelocity.y = directVec.y * dash_const.y;


}
void PlayerComponent::MoveMent()
{
	TransComponent* player_trs = static_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));
	float dt = AEFrameRateControllerGetFrameTime();
	//D 와 SHIFT를 눌렀을때만 적용 됨 --> 그냥 SHIFT를 누르고 있으면 전체적으로 적용되게 변경	
	if (DoNotMove==false)
	{
		if (AEInputCheckCurr(AEVK_LSHIFT))
		{
			manipulActive = true;
			timeManipul -= dt;
			//std::cout << timeManipul << std::endl;

			if (timeManipul <= 0.f)
			{
				manipulActive = false; //게이지가 0이면 누르는 동안에도 Manipulate가 안되게
				timeManipul = 0.f;
			}
		}
		if (!AEInputCheckCurr(AEVK_LSHIFT))
		{
			manipulActive = false;
			if (timeManipul < maniCapacity)
				timeManipul += dt;
			//std::cout << timeManipul << std::endl;
		}
	}

	//Jump
	if (DoNotMove == false)
	{
		if (AEInputCheckTriggered(AEVK_W))
		{
			jumpCnt++;
			if (jumpCnt <= 2)
				Jump(550);
			if (jumpCnt == 1)
			{
				auto res = ResourceManager::GetInst()->Get("sfx_jump1", "Assets/jump1.mp3");
				AudioResource* bgm_res = static_cast<AudioResource*>(res);
				bgm_res->SetSFXorMusic(Sound::SFX);
				auto bgm_audio = bgm_res->GetAudio();
				auto bgm_audioGroup = bgm_res->GetAudioGroup();
				AEAudioPlay(bgm_audio, bgm_audioGroup, 1.f, 1.f, 0);
			}
			else if (jumpCnt == 2)
			{
				auto res = ResourceManager::GetInst()->Get("sfx_jump2", "Assets/jump2.mp3");
				AudioResource* bgm_res = static_cast<AudioResource*>(res);
				bgm_res->SetSFXorMusic(Sound::SFX);
				auto bgm_audio = bgm_res->GetAudio();
				auto bgm_audioGroup = bgm_res->GetAudioGroup();
				AEAudioPlay(bgm_audio, bgm_audioGroup, 1.f, 1.f, 0);
			}
		}
		//Landing	
		// 황주현 코드 수정 -> 밑에 코드를 setjumpcntzero ::Stage01 handleCollision에서 구현
		if (AEInputCheckCurr(AEVK_W) && AEInputCheckCurr(AEVK_D) && AEInputCheckTriggered(AEVK_SPACE))
			Dash({ 1, 1 });

		if (AEInputCheckCurr(AEVK_A))
		{

			//player_trs->AddPos(-5.f, 0.f);
			player_trs->MovePos(-10.f, 0.f, manipulActive, dt);
			//Dash
			if (AEInputCheckCurr(AEVK_W) && AEInputCheckTriggered(AEVK_SPACE))
			{
				AccTime += AEFrameRateControllerGetFrameTime();
				auto res = ResourceManager::GetInst()->Get("sfx_dash1", "Assets/dash.mp3");
				AudioResource* bgm_res = static_cast<AudioResource*>(res);
				bgm_res->SetSFXorMusic(Sound::SFX);
				auto bgm_audio = bgm_res->GetAudio();
				auto bgm_audioGroup = bgm_res->GetAudioGroup();
				AEAudioPlay(bgm_audio, bgm_audioGroup, 1.f, 1.f, 0);
				if (AccTime > 1.5)
				{
					AEAudioStopGroup(bgm_audioGroup);
					AccTime = 0;
				}
				Dash({ -1, 1 });
			}

			else if (AEInputCheckTriggered(AEVK_SPACE))
			{
				AccTime += AEFrameRateControllerGetFrameTime();
				auto res = ResourceManager::GetInst()->Get("sfx_dash2", "Assets/dash.mp3");
				AudioResource* bgm_res = static_cast<AudioResource*>(res);
				bgm_res->SetSFXorMusic(Sound::SFX);
				auto bgm_audio = bgm_res->GetAudio();
				auto bgm_audioGroup = bgm_res->GetAudioGroup();
				AEAudioPlay(bgm_audio, bgm_audioGroup, 1.f, 1.f, 0);
				if (AccTime > 1.5)
				{
					AEAudioStopGroup(bgm_audioGroup);
					AccTime = 0;
				}
				Dash({ -1, 0 });
			}

		}

		//Right
		if (AEInputCheckCurr(AEVK_D))
		{
			//player_trs->AddPos(5.f, 0.f);
			player_trs->MovePos(10.f, 0.f, manipulActive, dt);
			//Dash
			if (AEInputCheckCurr(AEVK_W) && AEInputCheckTriggered(AEVK_SPACE))
			{
				AccTime += AEFrameRateControllerGetFrameTime();
				auto res = ResourceManager::GetInst()->Get("sfx_dash3", "Assets/dash.mp3");
				AudioResource* bgm_res = static_cast<AudioResource*>(res);
				bgm_res->SetSFXorMusic(Sound::SFX);
				auto bgm_audio = bgm_res->GetAudio();
				auto bgm_audioGroup = bgm_res->GetAudioGroup();
				AEAudioPlay(bgm_audio, bgm_audioGroup, 1.f, 1.f, 0);
				if (AccTime > 1.5)
				{
					AEAudioStopGroup(bgm_audioGroup);
					AccTime = 0;
				}
				Dash({ 1, 1 });
			}
			else if (AEInputCheckTriggered(AEVK_SPACE))
			{
				AccTime += AEFrameRateControllerGetFrameTime();
				auto res = ResourceManager::GetInst()->Get("sfx_dash4", "Assets/dash.mp3");
				AudioResource* bgm_res = static_cast<AudioResource*>(res);
				bgm_res->SetSFXorMusic(Sound::SFX);
				auto bgm_audio = bgm_res->GetAudio();
				auto bgm_audioGroup = bgm_res->GetAudioGroup();
				AEAudioPlay(bgm_audio, bgm_audioGroup, 1.f, 1.f, 0);
				if (AccTime > 1.5)
				{
					AEAudioStopGroup(bgm_audioGroup);
					AccTime = 0;
				}
				Dash({ 1, 0 });
			}

		}
	}


	AEVec2 pos = static_cast<TransComponent*>(player_trs)->GetPos();

	//left shift : time manipulation
	if (AEInputCheckCurr(AEVK_LSHIFT) && manipulActive)
		//if (manipulActive)
		dt *= 0.1f;

	//if dash velocity is too low. set to 0 (dash ended)
	if (AEVec2Length(&dashVelocity) <= 300.f)
	{
		AEVec2Zero(&dashVelocity);
	}

	//dash
	dashVelocity.x = dashVelocity.x * (1 - dt);
	dashVelocity.y = dashVelocity.y * (1 - dt);
	pos.x += (dashVelocity.x) * (2 * dt);
	pos.y += (dashVelocity.y) * (1.f * dt);

	//Gravity
	float accelGravity = 1.f;
	if (AEInputCheckCurr(AEVK_LCTRL))
	{
		accelGravity = 2.5f;
	}

	jumpVelocity.y -= m_vGravity.y * dt * accelGravity;
	pos.y = pos.y + jumpVelocity.y * dt;
	static_cast<TransComponent*>(player_trs)->SetPos(pos);
}

bool PlayerComponent::GetManiActive()
{
	return manipulActive;
}

bool PlayerComponent::GetInvincible()
{
	return invincibility;
}
void PlayerComponent::SetInvincible(bool sw)
{
	invincibility = sw;
}

//About mouse
void PlayerComponent::MouseAim()
{
	//Mouse Position
	TransComponent* aim_trs = (TransComponent*)mouseAim->FindComponent("Transform");
	s32 mouseX, mouseY;
	AEInputGetCursorPosition(&mouseX, &mouseY);
	mouseX -= 800;              //mouse X position lerp
	mouseY -= 450, mouseY *= -1;//mouse Y position lerp

	mousePos.x = mouseX, mousePos.y = mouseY;
	AEVec2 player_Cam = CameraManager::GetInst()->GetLookAt();
	aim_trs->SetPos(mousePos);
	aim_trs->AddPos({ player_Cam.x,player_Cam.y });

	//Mouse Position Lerp
	//mousePos == mouse position in world coord
	//player_Cam == player position in camera coord
	//so, mousePos += player_Cam == World coord mouse position to Camera coord mouse position.
	mousePos.x += player_Cam.x;
	mousePos.y += player_Cam.y;	

	DrawAim();
}
void PlayerComponent::DrawAim()
{
	ImageResource* tempResource = (ImageResource*)ResourceManager::GetInst()->FindRes("Aim");
	AEGfxTexture* pTex = tempResource->GetImage();


}
void PlayerComponent::MouseTraceLine()
{
	TransComponent* aimTrace_trs = (TransComponent*)aim_line->FindComponent("Transform");
	AEVec2 player_Cam = CameraManager::GetInst()->GetLookAt();

	aimTrace_trs->SetPos((mousePos.x + player_Cam.x) / 2.f, (mousePos.y + player_Cam.y) / 2.f);

	AEVec2 lineDirection = { mousePos.x - player_Cam.x, mousePos.y - player_Cam.y };
	//scale
	float dis = AEVec2Length(&lineDirection);
	aimTrace_trs->SetScale({ dis, 1 });
	//rotation
	AEVec2 nor_lineDirection = { 0,0 };
	AEVec2Normalize(&nor_lineDirection, &lineDirection);

	//if mouse position in sector 3, 4 : reverse line
	if (nor_lineDirection.y < 0)
		nor_lineDirection.x *= -1;
	//////////////////////////////////////////////////

	aimTrace_trs->SetRot(AEACos(nor_lineDirection.x));
	//aim_trs->AddPos({ player_Cam.x,player_Cam.y });
}
AEVec2 PlayerComponent::GetMousePos()
{
	return mousePos;
}

//About Player's attack
void PlayerComponent::Attack()
{
	//melee attack
	if (IsTutorialStage == false || IsAttackTutorial == true)
	{
		if (AEInputCheckTriggered(AEVK_1))
			meleeAction = true, shotAction = false;
		//shot attack
		else if (AEInputCheckTriggered(AEVK_2) && obtainGun)
			meleeAction = false, shotAction = true;

		TransComponent* player_trs = static_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));

		AEVec2 player_Cam = CameraManager::GetInst()->GetLookAt();

		//Direction Vector between player and mouse
		AEVec2 dVec = { (mousePos.x - player_trs->GetPos().x), (mousePos.y - player_trs->GetPos().y) }; //direction Vector
		AEVec2 nor_dVec{ 0,0 }; //Normailize direction Vector
		AEVec2Normalize(&nor_dVec, &dVec);
		SetNorVec(nor_dVec);

		if (meleeAction)
		{
			//Remove about shotAttack
			TransComponent* aimTrace_spr = (TransComponent*)aim_line->FindComponent("Transform");
			aimTrace_spr->SetScale({ 0,0 });
			/////////////////////////

			if (AEInputCheckTriggered(AEVK_LBUTTON) && !meleeState)
			{
				if (melee == nullptr)
				{
					meleeState = true;
					meleeCooldown = 0.f;

					melee = new GameObject("Melee");
					GoManager::GetInst()->AddObject(melee); //GetInst() == GetPtr()
					melee->AddComponent("Transform", new TransComponent(melee));
					//melee->AddComponent("Sprite", new SpriteComponent(melee));


				}
			}
			else
			{
				if (melee != nullptr)
				{
					TransComponent* melee_trs = static_cast<TransComponent*>(melee->FindComponent("Transform"));
					melee_trs->SetPos(player_trs->GetPos().x + (nor_dVec.x * 50.f), player_trs->GetPos().y + (nor_dVec.y * 50.f));
					melee_trs->SetScale({ 100,100 });
				}

				meleeCooldown += (f32)AEFrameRateControllerGetFrameTime();
				if (manipulActive)
				{
					if (meleeCooldown >= 3.f)
					{
						meleeState = false;
					}
				}
				else
				{
					if (meleeCooldown >= 0.35f)
					{
						meleeState = false;
					}

				}
				if (melee != nullptr && !meleeState)
				{
					//delete melee;
					melee->SetActive(false); //Set false means DELETE AND REMOVE GO.
					melee = nullptr; //I dont have a melee anymore
				}
			}
		}
		else if (shotAction)
		{
			MouseTraceLine();
			if (AEInputCheckTriggered(AEVK_LBUTTON))
			{
				AccTime += AEFrameRateControllerGetFrameTime();
				auto res = ResourceManager::GetInst()->Get("sfx_gun", "Assets/PlayerGun.mp3");
				AudioResource* bgm_res = static_cast<AudioResource*>(res);
				bgm_res->SetSFXorMusic(Sound::SFX);
				auto bgm_audio = bgm_res->GetAudio();
				auto bgm_audioGroup = bgm_res->GetAudioGroup();
				AEAudioPlay(bgm_audio, bgm_audioGroup, 1.f, 1.f, 0);
				if (AccTime > 1.3)
				{
					AEAudioStopGroup(bgm_audioGroup);
					AccTime = 0;
				}
				CreateBullet(player_trs->GetPos(), nor_dVec, "PlayerBullet", false);
			}
		}
	}
}
GameObject* PlayerComponent::GetMelee()
{
	return melee;
}

bool PlayerComponent::GetObtain()
{
	return obtainGun;
}
void PlayerComponent::SetObtain()
{
	obtainGun = true;
}

bool PlayerComponent::GetMeleeAction()
{
	return meleeAction;
}

bool PlayerComponent::GetMeleeState()
{
	return meleeState;
}

bool PlayerComponent::GetShotAction()
{
	return shotAction;
}

void PlayerComponent::SetNorVec(AEVec2 norV)
{
	norVec = norV;
}

AEVec2 PlayerComponent::GetNorVec()
{
	return norVec;
}


// 황주현 코드 추가
void PlayerComponent::SetJumpCntZero()
{
	jumpCnt = 0;
}
void PlayerComponent::SetJumpVelocityZero()
{
	jumpVelocity.y = 0.f;
}

int PlayerComponent::GetHealth()
{
	return playerhealth;
}

void PlayerComponent::TakeDamge()
{
	playerhealth -= 1;
}

bool PlayerComponent::IsAlive()
{
	if (playerhealth > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void PlayerComponent::Gauge()
{
	TransComponent* player_trs = static_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));
	TransComponent* gauge_trs = (TransComponent*)gauge->FindComponent("Transform");
	AEVec2 player_Cam = CameraManager::GetInst()->GetLookAt();
	gauge_trs->SetScale({ timeManipul * 20.f, 15 });
	float len = maniCapacity * 20.f;
	float curLen = timeManipul * 20.f;
	gauge_trs->SetPos(player_trs->GetPos().x - 700 - ((len - curLen)/2.f), player_trs->GetPos().y + 400);

}


void PlayerComponent::Update()
{
	MoveMent();
	MouseAim();
	Attack();
	Gauge();
}

void PlayerComponent::LoadFromJson(const json& str)
{
	return;
}
json PlayerComponent::SaveToJson(const json& str)
{
	return json();
}
