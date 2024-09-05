#include "BulletAnimationComponent.h"
#include "ResourceManager.h"
#include "Resource.h"
#include "ImageResource.h"
#include "TransComponent.h"
#include "GameObject.h"

void BulletAnimationComponent::Initialize()
{
	animation_timer = 0.f;
	current_sprite_index = 0; // start from first sprite
	current_sprite_uv_offset_x = 0.f;
	current_sprite_uv_offset_y = 0.f;
}

void BulletAnimationComponent::ChangeAnimation(std::string _name, f32 rows, f32 cols, f32 max, f32 duration)
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

BulletAnimationComponent::BulletAnimationComponent(GameObject* _owner) : BaseComponent(_owner)
{
	ResourceManager::GetInst()->Get("BulletAnim", "Assets/Bullet_SpriteSheet.png");

	ChangeAnimation("BulletAnim", 1, 4, 4, 0.1);

}

void BulletAnimationComponent::Update()
{
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
	if (trans)
	{
		AEMtx33 transf = trans->GetMatrix();
		AEGfxSetTransform(transf.m);
	}

	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

	return;
}



BulletAnimationComponent::~BulletAnimationComponent()
{
	if (mesh != nullptr)
		AEGfxMeshFree(mesh);
}