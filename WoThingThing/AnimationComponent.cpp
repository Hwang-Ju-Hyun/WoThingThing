#include "AnimationComponent.h"
#include "GameObject.h"
#include "TransComponent.h"
#include "ImageResource.h"
#include "ResourceManager.h"

void AnimationComponent::Initialize()
{
	animation_timer = 0.f;
	current_sprite_index = 0; // start from first sprite
	current_sprite_uv_offset_x = 0.f;
	current_sprite_uv_offset_y = 0.f;
}

void AnimationComponent::ChangeAnimation(std::string _name, f32 rows, f32 cols, f32 max, f32 duration)
{

	if (this->current != _name)
	{
		std::cout << this->current << "        " << _name << std::endl;
		std::cout << this->current << "        " << _name << std::endl;
		//if(pTex != nullptr)
		//{
		//	AEGfxTextureUnload(this->pTex); //Unload pTex
		//}
		//Load pTex
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
	else
	{

	}
}

AnimationComponent::AnimationComponent(GameObject* _owner) : BaseComponent(_owner)
{
	ResourceManager::GetInst()->Get("Idle", "Assets/PlayerIdle_SpriteSheet.png");
	ResourceManager::GetInst()->Get("Run", "Assets/PlayerRun_SpriteSheet.png");
	ResourceManager::GetInst()->Get("Dash", "Assets/PlayerDash_SpriteSheet.png");
	ResourceManager::GetInst()->Get("Jump", "Assets/PlayerJump&Fall_SpriteSheet.png");




	ChangeAnimation("Idle", 1, 8, 8, 0.1);

	dashState = false, jumpState = false;
	dashTimer = 0.f, jumpTimer = 0.f;
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


	// Reverse based Y-axis
	//==============Movement condition=====================================//


	//Right
	if (AEInputCheckCurr(AEVK_D) && !dashState && !jumpState)
	{
		ChangeAnimation("Run", 1, 8, 8, 0.1);
		flip = false;
	}

	//Left
	else if (AEInputCheckCurr(AEVK_A) && !dashState && !jumpState)
	{
		ChangeAnimation("Run", 1, 8, 8, 0.1);
		flip = true;
	}

	//Idle
	else if (!dashState && !jumpState)
	{
		flip = false;

		ChangeAnimation("Idle", 1, 8, 8, 0.1);
	}
	

	//Dash
	if (AEInputCheckTriggered(AEVK_SPACE) && !jumpState)
	{
		dashState = true;
		dashTimer = 0.f;

		if (AEInputCheckCurr(AEVK_A))
		{
			flip = true;
		}

		ChangeAnimation("Dash", 1, 6, 6, 0.1);
	}
	dashTimer += (f32)AEFrameRateControllerGetFrameTime();
	if (dashTimer >= animation_duration_per_frame * spritesheet_max_sprites)
		dashState = false;

	//Jump
	if (AEInputCheckTriggered(AEVK_W) && !dashState)
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

		//pTex = AEGfxTextureLoad("Assets/idle_1.png");
		//pTex = testArr[i++];

	}
	//AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	//AEGfxSetTextureMode(AE_GFX_TM_AVERAGE);

	AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

	AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);

	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);

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
