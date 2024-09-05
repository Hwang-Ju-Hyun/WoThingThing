#include "AnimationComponent.h"
#include "GameObject.h"
#include "TransComponent.h"
#include "ResourceManager.h"

AnimationComponent::AnimationComponent(GameObject* _owner) : BaseComponent(_owner)
{
	spritesheet_rows = 1;
	spritesheet_cols = 8;
	spritesheet_max_sprites = 8;
	sprite_uv_width = 1.f / spritesheet_cols;
	sprite_uv_height = 1.f / spritesheet_rows;

	animation_timer = 0.f;
	animation_duration_per_frame = 0.2f;
	current_sprite_index = 0; // start from first sprite
	current_sprite_uv_offset_x = 0.f;
	current_sprite_uv_offset_y = 0.f;

	mesh = 0;
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

	//pTex = AEGfxTextureLoad("Assets/PlayerIdle_1.png");
}

AnimationComponent::~AnimationComponent()
{
	AEGfxMeshFree(mesh);
	AEGfxTextureUnload(pTex);
}

void AnimationComponent::Update()
{
	if (mesh == nullptr)
		return;


	// Reverse based Y-axis
	AEMtx33 isReverseMtx;
	AEMtx33Scale(&isReverseMtx, 1, 1);

	//==============Movement condition=====================================//
	//Idle
	spritesheet_rows = 1;
	spritesheet_cols = 8;
	spritesheet_max_sprites = 8;
	sprite_uv_width = 1.f / spritesheet_cols;
	sprite_uv_height = 1.f / spritesheet_rows;
	animation_duration_per_frame = 0.1f;
	pTex = AEGfxTextureLoad("Assets/PlayerIdle_SpriteSheet.png");


	float delay = 1.f;
	//Right
	if (AEInputCheckCurr(AEVK_D))
	{
		pTex = AEGfxTextureLoad("Assets/PlayerRun_SpriteSheet.png");
	}
	//Left
	if (AEInputCheckCurr(AEVK_A))
	{
		AEMtx33Scale(&isReverseMtx, -1, 1);
		pTex = AEGfxTextureLoad("Assets/PlayerRun_SpriteSheet.png");

	}
	
	//Dash
	if (AEInputCheckCurr(AEVK_SPACE))
	{
		spritesheet_cols = 6;
		spritesheet_max_sprites = 6;
		sprite_uv_width = 1.f / spritesheet_cols;
		sprite_uv_height = 1.f / spritesheet_rows;

		//animation_duration_per_frame = 0.2f;
		//delay = AEFrameRateControllerGetFrameTime();

		pTex = AEGfxTextureLoad("Assets/PlayerDash_SpriteSheet.png");
	}

	//if (AEInputCheckTriggered(AEVK_SPACE))
	//{
	//	pTex = AEGfxTextureLoad("Assets/PlayerDash_SpriteSheet.png");
	//	AEMtx33Scale(&isReverseMtx, -1, 1);
	//}
	//=====================================================================//

	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, sprite_uv_height, // bottom left
		0.5f, -0.5f, 0xFFFFFFFF, sprite_uv_width, sprite_uv_height, // bottom right 
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);  // top left

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, sprite_uv_width, sprite_uv_height, // bottom right 
		0.5f, 0.5f, 0xFFFFFFFF, sprite_uv_width, 0.0f,   // top right
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);  // bottom left


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
	if (trans)
	{
		AEMtx33 transf = trans->GetMatrix();
		AEMtx33Concat(&transf, &transf, &isReverseMtx);
		AEGfxSetTransform(transf.m);
	}

	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

	return;
}
