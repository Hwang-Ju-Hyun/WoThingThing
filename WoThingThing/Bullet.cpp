#include "Bullet.h"

#include "GoManager.h"
#include "GameObject.h"

#include "TransComponent.h"
#include "SpriteComponent.h"
#include "BulletComponent.h"
#include "PlayerComponent.h"
#include "BulletAnimationComponent.h"

#include "ResourceManager.h"
#include "ImageResource.h"
int remainBullet;

void CreateGun(AEVec2 initPos)
{
	remainBullet = 5;
	GameObject* gun = new GameObject("Gun");
	GoManager::GetInst()->AddObject(gun);

	gun->AddComponent("Transform", new TransComponent(gun));
	TransComponent* gun_trs = (TransComponent*)gun->FindComponent("Transform");
	gun_trs->SetPos(initPos.x, initPos.y);
	gun_trs->SetScale({ 80,80 });

	gun->AddComponent("Sprite", new SpriteComponent(gun));
	SpriteComponent* gun_spr = (SpriteComponent*)gun->FindComponent("Sprite");
	ResourceManager::GetInst()->Get("CreateGun", "Assets/CreateGun.png");
	ImageResource* createGun = (ImageResource*)ResourceManager::GetInst()->FindRes("CreateGun");
	gun_spr->SetTexture(createGun->GetImage());
}


void CreateBullet(AEVec2 initPos, AEVec2 nor_dVec, std::string _bulletname, bool _enemyShoot)
{
	if (!_enemyShoot) //Player
	{
		if (remainBullet > 0)
		{
			remainBullet--;

			GameObject* bullet = new GameObject(_bulletname);
			GoManager::GetInst()->AddObject(bullet);
			bullet->AddComponent("Transform", new TransComponent(bullet));

			bullet->AddComponent("BulletAnim", new BulletAnimationComponent(bullet));
			BulletAnimationComponent* bullet_anim = (BulletAnimationComponent*)bullet->FindComponent("BulletAnim");
			bullet_anim->SetAnim("BulletAnim", "Assets/Bullet_SpriteSheet.png", 1, 4, 4, 0.1f);

			bullet->AddComponent("Bullet", new BulletComponent(bullet));
			BulletComponent* bullet_comp = (BulletComponent*)bullet->FindComponent("Bullet");
			bullet_comp->SetBulletVec(nor_dVec);
			bullet_comp->EnemyShoot = _enemyShoot;

			TransComponent* bullet_trs = (TransComponent*)bullet->FindComponent("Transform");
			bullet_trs->SetPos(initPos.x + (nor_dVec.x * 50.f), initPos.y + (nor_dVec.y * 50.f));
			bullet_trs->SetScale({ 30, 40 });
		}
	}
	else //Enemy
	{
		GameObject* bullet = new GameObject(_bulletname);
		GoManager::GetInst()->AddObject(bullet);
		bullet->AddComponent("Transform", new TransComponent(bullet));
		bullet->AddComponent("Sprite", new SpriteComponent(bullet));
		if (_bulletname == "BossBullet")
		{
			SpriteComponent* bullet_spr = (SpriteComponent*)bullet->FindComponent("Sprite");
			ResourceManager::GetInst()->Get("BossBullet", "Assets/BossBullet.png");
			ImageResource* bossBullet = (ImageResource*)ResourceManager::GetInst()->FindRes("BossBullet");
			bullet_spr->SetTexture(bossBullet->GetImage());
		}
		else if (_bulletname == "EnemyBullet")
		{
			SpriteComponent* bullet_spr = (SpriteComponent*)bullet->FindComponent("Sprite");
			ResourceManager::GetInst()->Get("EnemyBullet", "Assets/EnemyBullet.png");
			ImageResource* enemyBullet = (ImageResource*)ResourceManager::GetInst()->FindRes("EnemyBullet");
			bullet_spr->SetTexture(enemyBullet->GetImage());
		}
		bullet->AddComponent("Bullet", new BulletComponent(bullet));
		BulletComponent* bullet_comp = (BulletComponent*)bullet->FindComponent("Bullet");
		bullet_comp->SetBulletVec(nor_dVec);
		bullet_comp->EnemyShoot = _enemyShoot;

		TransComponent* bullet_trs = (TransComponent*)bullet->FindComponent("Transform");
		bullet_trs->SetPos(initPos.x + (nor_dVec.x * 50.f), initPos.y + (nor_dVec.y * 50.f));
		bullet_trs->SetScale({ 15,15 });
	}
}
 
void CreateSupplement(AEVec2 initPos)
{
	//i) ������ ��ġ������ �����ϱ�
	//ii) �÷��̾��� �Ѿ��� �����Ҷ� ���� ��ó���� �����ϰ� �����ϱ�
	GameObject* supplement = new GameObject("BulletSupplement");
	GoManager::GetInst()->AddObject(supplement);

	supplement->AddComponent("Transform", new TransComponent(supplement));
	TransComponent* supple_trs = (TransComponent*)supplement->FindComponent("Transform");
	supple_trs->SetPos(initPos.x, initPos.y);
	supple_trs->SetScale({ 40, 40 });

	//Animation
	supplement->AddComponent("SuppleAnim", new BulletAnimationComponent(supplement));
	BulletAnimationComponent* supple_anim = (BulletAnimationComponent*)supplement->FindComponent("SuppleAnim");
	supple_anim->SetAnim("SupplyBullet", "Assets/SupplyBullet_SpriteSheet.png", 1, 10, 10, 0.1f);

	//Sprite
	//supplement->AddComponent("Sprite", new SpriteComponent(supplement));
	//SpriteComponent* supple_spr = (SpriteComponent*)supplement->FindComponent("Sprite");
	//ResourceManager::GetInst()->Get("SupplyBullet", "Assets/SupplyBullet.png");
	//ImageResource* suppleBullet = (ImageResource*)ResourceManager::GetInst()->FindRes("SupplyBullet");
	//supple_spr->SetTexture(suppleBullet->GetImage());
}

int GetBullet()
{
	return remainBullet;
}

void AddBullet()
{
	if (remainBullet >= 0 && remainBullet < 5)
		remainBullet++;
}
