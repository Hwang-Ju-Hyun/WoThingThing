#include "BulletComponent.h"
#include "PlayerComponent.h"
#include "TransComponent.h"
#include "SpriteComponent.h"
#include "GoManager.h"
#include "GameObject.h"
#include "CameraManager.h"

BulletComponent::BulletComponent(GameObject* _owner) : BaseComponent(_owner)
{
	bullet_Vec = { 0.f,0.f };
	bullet_const = { 35.f, 35.f };
}

void BulletComponent::SetBulletVec(AEVec2 dVec)
{
	bullet_Vec.x = dVec.x * bullet_const.x;
	bullet_Vec.y = dVec.y * bullet_const.y;
}

AEVec2 BulletComponent::GetBulletVec()
{
	return bullet_Vec;
}

void BulletComponent::DestroyBullet()
{
	std::cout << m_pOwner << "Destroy Bullet!!" << std::endl;
	m_pOwner->SetActive(false);
	// 주석 풀 시 진짜 사형
	//m_pOwner = nullptr;
}

void BulletComponent::Update()
{
	TransComponent* bullet_trs = (TransComponent*)m_pOwner->FindComponent("Transform");
	AEVec2 bullet_pos = static_cast<TransComponent*>(bullet_trs)->GetPos();

	float dt = AEFrameRateControllerGetFrameTime();
	if (AEInputCheckCurr(AEVK_LSHIFT))
	{
		bullet_pos.x += bullet_Vec.x * dt;
		bullet_pos.y += bullet_Vec.y * dt;
	}
	else
	{
		bullet_pos.x += bullet_Vec.x;
		bullet_pos.y += bullet_Vec.y;
	}
	static_cast<TransComponent*>(bullet_trs)->SetPos(bullet_pos);


	//IF: bullet OUTRANGE OF SCREEN --> DESTROY
	AEVec2 player_Cam = CameraManager::GetInst()->GetLookAt();
	AEVec2 camera_screen = { 800,400 };
	AEVec2 pos_outrange_screen;
	AEVec2Add(&pos_outrange_screen, &player_Cam, &camera_screen);
	AEVec2 neg_outrange_screen;
	AEVec2Sub(&neg_outrange_screen, &player_Cam, &camera_screen);
	if (bullet_pos.y > pos_outrange_screen.y || bullet_pos.y < neg_outrange_screen.y
		|| bullet_pos.x > pos_outrange_screen.x || bullet_pos.x < neg_outrange_screen.x)
	{
		std::cout << "c" << std::endl;
		DestroyBullet();
	}



}
