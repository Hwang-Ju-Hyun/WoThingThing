#include "Bullet.h"

#include "GoManager.h"
#include "GameObject.h"

#include "TransComponent.h"
#include "SpriteComponent.h"
#include "BulletComponent.h"


void CreateBullet(AEVec2 initPos, AEVec2 nor_dVec, std::string _bulletname)
{
	GameObject* bullet = new GameObject(_bulletname);
	GoManager::GetInst()->AddObject(bullet);
	bullet->AddComponent("Transform", new TransComponent(bullet));
	bullet->AddComponent("Sprite", new SpriteComponent(bullet));
	bullet->AddComponent("Bullet", new BulletComponent(bullet));

	TransComponent* bullet_trs = (TransComponent*)bullet->FindComponent("Transform");
	BulletComponent* bullet_comp = (BulletComponent*)bullet->FindComponent("Bullet");

	bullet_comp->SetBulletVec(nor_dVec);

	SpriteComponent* bullet_spr = (SpriteComponent*)bullet->FindComponent("Sprite");
	//player_trs->GetPos().x + (nor_dVec.x * 50.f), player_trs->GetPos().y + (nor_dVec.y * 50.f)

	bullet_trs->SetPos(initPos.x + (nor_dVec.x * 50.f), initPos.y + (nor_dVec.y * 50.f));
	bullet_trs->SetScale({ 10, 10 });
}
