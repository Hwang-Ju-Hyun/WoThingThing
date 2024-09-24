#include "EnemyAnimationComponent.h"
#include "GameObject.h"
#include "TransComponent.h"
#include "ImageResource.h"
#include "ResourceManager.h"
#include"PlayerComponent.h"
#include"GameObject.h"
#include"GoManager.h"

void EnemyAnimationComponent::Initialize()
{
	animation_timer = 0.f;
	current_sprite_index = 0; // start from first sprite
	current_sprite_uv_offset_x = 0.f;
	current_sprite_uv_offset_y = 0.f;
}

void EnemyAnimationComponent::ChangeAnimation(std::string _name, f32 rows, f32 cols, f32 max, f32 duration)
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

void EnemyAnimationComponent::SetEnemyDir(bool dir)
{
	e_dir = dir;
}

void EnemyAnimationComponent::SetEnemy(int num)
{
	who_enemy = num;//1이 melee 2가 Sniper 3이 boss
}

EnemyAnimationComponent::EnemyAnimationComponent(GameObject* _owner) : BaseComponent(_owner)
{
	//ResourceManager::GetInst()->Get("Idle", "Assets/PlayerIdle_SpriteSheet.png");
	//ResourceManager::GetInst()->Get("Run", "Assets/PlayerRun_SpriteSheet.png");
	//ResourceManager::GetInst()->Get("Dash", "Assets/PlayerDash_SpriteSheet.png");
	//ResourceManager::GetInst()->Get("Jump", "Assets/PlayerJump&Fall_SpriteSheet.png");

	//ChangeAnimation("Idle", 1, 8, 8, 0.1); 처음 여기에 상태 세팅해주기

	//meleeEnemyChase
	
	//ChangeAnimation("MeleeIdle", 1, 8, 8, 0.1);
	

	dashState = false, jumpState = false;
	dashTimer = 0.f, jumpTimer = 0.f;
	flip = false;
}

EnemyAnimationComponent::~EnemyAnimationComponent()
{
	if (mesh != nullptr)
		AEGfxMeshFree(mesh);
}

void EnemyAnimationComponent::Update()
{
	if (mesh == nullptr)
		return;

	GameObject* tempPlayer = GoManager::GetInst()->FindObj("Player");
	PlayerComponent* temp_comp = (PlayerComponent*)tempPlayer->FindComponent("PlayerComp");
	bool manipulActive = temp_comp->GetManiActive();
	if (manipulActive)
	{
		animation_timer += (f32)AEFrameRateControllerGetFrameTime() * 0.1;
	}
	else
	{
		animation_timer += (f32)AEFrameRateControllerGetFrameTime();
	}

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

	if (e_dir) 
	{
		flip = true;
	}
	else
	{
		flip = false;
	}

	if (flip)
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

void EnemyAnimationComponent::LoadFromJson(const json& str)
{
	auto compData = str.find("CompData");
	if (compData != str.end())
	{
		auto name = compData->find("name");
		current = name.value();
		auto rows = compData->find("rows");
		spritesheet_rows = rows.value();
		auto cols = compData->find("cols");
		spritesheet_cols = cols.value();
		auto animation_per_frame = compData->find("animation_duration_per_frame");
		animation_duration_per_frame = animation_per_frame.value();
	}
}

json EnemyAnimationComponent::SaveToJson(const json& str)
{
	json data;
	data["Type"] = "EnemyAnimation";

	json compData;
	compData["name"] = current;
	compData["rows"] = spritesheet_rows;
	compData["cols"] = spritesheet_cols;
	compData["animation_duration_per_frame"] = animation_duration_per_frame;

	data["CompData"] = compData;

	return data;
}

BaseRTTI* EnemyAnimationComponent::CreateEnemyAnimationComponent()
{
	GameObject* lastObj = GoManager::GetInst()->GetLastObj();	//아마 여기가 문제일듯 <- 아니네	
	BaseRTTI* p = lastObj->AddComponent("EnemyAnimation", new EnemyAnimationComponent(lastObj));
	return p;
}
