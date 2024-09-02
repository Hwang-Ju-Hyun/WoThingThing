#include "Bullet.h"

#include "GoManager.h"
#include "GameObject.h"

#include "TransComponent.h"
#include "SpriteComponent.h"
#include "BulletComponent.h"


void CreateBullet(AEVec2 initPos, AEVec2 nor_dVec)
{
	GameObject* bullet = new GameObject("Bullet");
	GoManager::GetInst()->AddObject(bullet);
	bullet->AddComponent("Transform", new TransComponent(bullet));
	bullet->AddComponent("Sprite", new SpriteComponent(bullet));
	bullet->AddComponent("Bullet", new BulletComponent(bullet));

	TransComponent* bullet_trs = (TransComponent*)bullet->FindComponent("Transform");
	BulletComponent* bullet_comp = (BulletComponent*)bullet->FindComponent("Bullet");

	bullet_comp->SetBulletVec(nor_dVec);

	SpriteComponent* bullet_spr = (SpriteComponent*)bullet->FindComponent("Sprite");
	bullet_trs->SetPos(initPos);
	bullet_trs->SetScale({ 10, 10 });
}
