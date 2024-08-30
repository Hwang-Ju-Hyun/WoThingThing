#include "BulletComponent.h"
#include "TransComponent.h"
#include "GoManager.h"
#include "GameObject.h"

BulletComponent::BulletComponent(GameObject* _owner) : BaseComponent(_owner)
{
	for (auto iter : GoManager::GetInst()->Allobj())
	{
		if (iter->GetName() == "Bullet")
		{
			bullet = iter;
		}
	}
	player = (PlayerComponent*)bullet->FindComponent("PlayerComp");
}

BulletComponent::~BulletComponent()
{
	bullet = nullptr;
}

void BulletComponent::Update()
{
	if (player->GetBullet() != nullptr /*&& bullet->GetActive()*/)
	{
		TransComponent* bullet_trs = (TransComponent*)player->GetBullet()->FindComponent("Transform");
		AEVec2 bullet_pos = static_cast<TransComponent*>(bullet_trs)->GetPos();
		bullet_pos.x += bullet_Vec.x;
		bullet_pos.y += bullet_Vec.y;
		static_cast<TransComponent*>(bullet_trs)->SetPos(bullet_pos);
	}
}
