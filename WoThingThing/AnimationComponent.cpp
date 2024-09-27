#include "AnimationComponent.h"
#include "GameObject.h"
#include "GoManager.h"
#include "TransComponent.h"
#include "ImageResource.h"
#include "ResourceManager.h"
#include "PlayerComponent.h"

//Test
#include "BulletAnimationComponent.h"


void AnimationComponent::Initialize()
{
	animation_timer = 0.f;
	current_sprite_index = 0; // start from first sprite
	current_sprite_uv_offset_x = 0.f;
	current_sprite_uv_offset_y = 0.f;
}

void AnimationComponent::ChangeAnimation(std::string _name, u32 rows, u32 cols, u32 max, f32 duration)
{

	if (this->current != _name)
	{
		ImageResource* tempResource = (ImageResource*)ResourceManager::GetInst()->FindRes(_name);
		this->pTex = tempResource->GetImage();

		this->current = _name; //change current

		Initialize();

		spritesheet_rows = rows;
		spritesheet_cols = cols;
		spritesheet_max_sprites = max;
		sprite_uv_width = 1.f / spritesheet_cols;
		sprite_uv_height = 1.f / spritesheet_rows;
		animation_duration_per_frame = duration;

		if (mesh != nullptr)
			AEGfxMeshFree(mesh);
		//=====================================================================//
		AEGfxMeshStart();
		AEGfxTriAdd(
			-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, sprite_uv_height, // bottom left
			0.5f, -0.5f, 0xFFFFFFFF, sprite_uv_width, sprite_uv_height, // bottom right 
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);  // top left

		AEGfxTriAdd(
			0.5f, -0.5f, 0xFFFFFFFF, sprite_uv_width, sprite_uv_height, // bottom right 
			0.5f, 0.5f, 0xFFFFFFFF, sprite_uv_width, 0.0f,   // top right
			-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);  // bottom left
		mesh = AEGfxMeshEnd();
		//=======================================================================
	}
}


AnimationComponent::AnimationComponent(GameObject* _owner) : BaseComponent(_owner)
{
	ResourceManager::GetInst()->Get("Idle", "Assets/PlayerIdle_SpriteSheet.png");
	ResourceManager::GetInst()->Get("Run", "Assets/PlayerRun_SpriteSheet.png");
	ResourceManager::GetInst()->Get("Dash", "Assets/PlayerDash_SpriteSheet.png");
	ResourceManager::GetInst()->Get("Jump", "Assets/PlayerJump&Fall_SpriteSheet.png");
	ResourceManager::GetInst()->Get("Attack", "Assets/PlayerAttack_SpriteSheet.png");
	ResourceManager::GetInst()->Get("LongAttack", "Assets/PlayerLongAttack_SpriteSheet.png");

	ChangeAnimation("Idle", 1, 8, 8, 0.1f);

	dashState = false, jumpState = false, attackState = false, longattackState = false;
	dashTimer = 0.f, jumpTimer = 0.f, attackTimer = 0.f, longattackTimer = 0.f;
	flip = false;
}

AnimationComponent::~AnimationComponent()
{
	if (mesh != nullptr)
		AEGfxMeshFree(mesh);
}

void AnimationComponent::Update()
{
	if (mesh == nullptr)
		return;

	TransComponent* my_trs = (TransComponent*)this->m_pOwner->FindComponent("Transform");

	GameObject* playerObj = GoManager::GetInst()->FindObj("Player");
	PlayerComponent* player_comp = (PlayerComponent*)playerObj->FindComponent("PlayerComp");

	if (playerObj != nullptr)
	{
		TransComponent* player_trs = (TransComponent*)playerObj->FindComponent("Transform");
		my_trs->SetPos(player_trs->GetPos());
		my_trs->SetScale({ 80,80 });
	}
	if (player_comp->GetManiActive())
		animation_duration_per_frame = 0.7f;
	else
		animation_duration_per_frame = 0.1f;

	//Right
	if (AEInputCheckCurr(AEVK_D) && !dashState && !jumpState && !attackState && !longattackState)
	{
		ChangeAnimation("Run", 1, 8, 8, 0.1f);
		flip = false;
	}

	//Left
	else if (AEInputCheckCurr(AEVK_A) && !dashState && !jumpState && !attackState && !longattackState)
	{
		ChangeAnimation("Run", 1, 8, 8, 0.1f);
		flip = true;
	}

	//Idle
	else if (!dashState && !jumpState && !attackState && !longattackState)
	{
		flip = false;
		ChangeAnimation("Idle", 1, 8, 8, 0.1f);

	}
	

	//Dash
	if (AEInputCheckTriggered(AEVK_SPACE) && !jumpState && !attackState && !longattackState)
	{
		player_comp->SetInvincible(true);
		dashState = true;
		dashTimer = 0.f;

		if (AEInputCheckCurr(AEVK_A))
		{
			flip = true;
		}

		ChangeAnimation("Dash", 1, 6, 6, 0.1f);
	}
	dashTimer += (f32)AEFrameRateControllerGetFrameTime();
	if (dashTimer >= animation_duration_per_frame * spritesheet_max_sprites)
	{
		player_comp->SetInvincible(false);
		dashState = false;
	}

	//Jump
	//cf.) air상태일때 fall 애니메이션만 딱 작동이되고 Land 했을때 다시 Idle로 변하게.
	if (AEInputCheckTriggered(AEVK_W) && !dashState && !attackState && !longattackState)
	{
		jumpState = true;
		jumpTimer = 0.f;

		Initialize();
		ChangeAnimation("Jump", 1, 6, 6, 0.25);
		//ChangeAnimation("Assets/PlayerJump&Fall_SpriteSheet.png");
	}
	jumpTimer += (f32)AEFrameRateControllerGetFrameTime();
	if (jumpTimer >= animation_duration_per_frame * spritesheet_max_sprites)
		jumpState = false;

	//Attack	
	if (player_comp->GetIsAttackTutorial() == true || player_comp->GetIsTutorialStage() == false)
	{
		if (player_comp->GetMeleeAction() && AEInputCheckTriggered(AEVK_LBUTTON))
		{
			attackState = true;
			attackTimer = 0.f;

			//Flip!!========
			AEVec2	norD = { 0,0 };
			if (playerObj != nullptr && player_comp != nullptr)
			{
				norD = player_comp->GetNorVec();
			}
			if (norD.x < 0)
				flip = true;
			else
				flip = false;
			//==============

			//Initialize();
			ChangeAnimation("Attack", 1, 8, 8, 0.1f);
		}
		if (attackState)
		{
			my_trs->SetScale({ 256,96 });
		}
		attackTimer += (f32)AEFrameRateControllerGetFrameTime();
		if (attackState && attackTimer >= animation_duration_per_frame * spritesheet_max_sprites)
		{
			attackState = false;
			my_trs->SetScale({ 80,80 });
		}



		//Long Attack
		if (player_comp->GetShotAction() && AEInputCheckTriggered(AEVK_LBUTTON))
		{
			longattackState = true;
			longattackTimer = 0.f;

			//Flip!!========
			AEVec2	norD = { 0,0 };
			if (playerObj != nullptr && player_comp != nullptr)
			{
				norD = player_comp->GetNorVec();
			}
			if (norD.x < 0)
				flip = true;
			else
				flip = false;
			//==============

			Initialize();
			ChangeAnimation("LongAttack", 1, 8, 8, 0.1f);
		}
		if (longattackState)
		{
			my_trs->SetScale({ 110,100 });
		}
		longattackTimer += (f32)AEFrameRateControllerGetFrameTime();
		if (longattackState && longattackTimer >= animation_duration_per_frame * spritesheet_max_sprites)
		{
			longattackState = false;
			my_trs->SetScale({ 80,80 });
		}
	}
	
	animation_timer += (f32)AEFrameRateControllerGetFrameTime() /* * delay*/;
	if (animation_timer >= animation_duration_per_frame)
	{
		// Reset the timer.
		animation_timer = 0;

		// Calculate the next sprite UV
		current_sprite_index = ++current_sprite_index % spritesheet_max_sprites;
		u32 current_sprite_row = current_sprite_index / spritesheet_cols;
		u32 current_sprite_col = current_sprite_index % spritesheet_cols;
		current_sprite_uv_offset_x = sprite_uv_width * current_sprite_col;
		current_sprite_uv_offset_y = sprite_uv_height * current_sprite_row;
	}
	//AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	//AEGfxSetTextureMode(AE_GFX_TM_AVERAGE);

	AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

	AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);

	if (pTex != nullptr)
		AEGfxTextureSet(pTex, current_sprite_uv_offset_x, current_sprite_uv_offset_y);
	//AEGfxTextureSet(pTex, 0, 0);

	TransComponent* trans = static_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));

	AEMtx33 isReverseMtx;
	AEMtx33Scale(&isReverseMtx, 1, 1);

	if(flip)
		AEMtx33Scale(&isReverseMtx, -1, 1);

	if (trans)
	{
		AEMtx33 transf = trans->GetMatrix();
		AEMtx33Concat(&transf, &transf, &isReverseMtx);
		AEGfxSetTransform(transf.m);
	}

	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
	return;
}

