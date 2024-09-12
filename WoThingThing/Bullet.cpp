#include "Bullet.h"

#include "GoManager.h"
#include "GameObject.h"

#include "TransComponent.h"
#include "SpriteComponent.h"
#include "BulletComponent.h"
#include "PlayerComponent.h"
#include "BulletAnimationComponent.h"

#include "ResourceManager.h"
int remainBullet;

void CreateGun(AEVec2 initPos)
{
	remainBullet = 5;
	GameObject* gun = new GameObject("Gun");
	GoManager::GetInst()->AddObject(gun);
	gun->AddComponent("Transform", new TransComponent(gun));
	gun->AddComponent("BulletAnim", new BulletAnimationComponent(gun));
	//gun->AddComponent("Sprite", new SpriteComponent(gun));
	
	TransComponent* gun_trs = (TransComponent*)gun->FindComponent("Transform");
	gun_trs->SetPos(initPos.x, initPos.y);
	gun_trs->SetScale({ 60,80 });
}


void CreateBullet(AEVec2 initPos, AEVec2 nor_dVec, std::string _bulletname, bool _enemyShoot)
{
	if (!_enemyShoot)
	{
		if (remainBullet > 0) //Player
		{
			remainBullet--;

			GameObject* bullet = new GameObject(_bulletname);
			GoManager::GetInst()->AddObject(bullet);
			bullet->AddComponent("Transform", new TransComponent(bullet));
			//bullet->AddComponent("Sprite", new SpriteComponent(bullet));
			bullet->AddComponent("BulletAnim", new BulletAnimationComponent(bullet));
			bullet->AddComponent("Bullet", new BulletComponent(bullet));
			BulletComponent* bullet_comp = (BulletComponent*)bullet->FindComponent("Bullet");
			bullet_comp->SetBulletVec(nor_dVec);
			bullet_comp->EnemyShoot = _enemyShoot;

			TransComponent* bullet_trs = (TransComponent*)bullet->FindComponent("Transform");
			bullet_trs->SetPos(initPos.x + (nor_dVec.x * 50.f), initPos.y + (nor_dVec.y * 50.f));
			bullet_trs->SetScale({ 30, 40 });
		}
	}
	else
	{
		GameObject* bullet = new GameObject(_bulletname);
		GoManager::GetInst()->AddObject(bullet);
		bullet->AddComponent("Transform", new TransComponent(bullet));
		bullet->AddComponent("Sprite", new SpriteComponent(bullet));
		bullet->AddComponent("Bullet", new BulletComponent(bullet));
		BulletComponent* bullet_comp = (BulletComponent*)bullet->FindComponent("Bullet");
		bullet_comp->SetBulletVec(nor_dVec);
		bullet_comp->EnemyShoot = _enemyShoot;

		TransComponent* bullet_trs = (TransComponent*)bullet->FindComponent("Transform");
		bullet_trs->SetPos(initPos.x + (nor_dVec.x * 50.f), initPos.y + (nor_dVec.y * 50.f));
		bullet_trs->SetScale({ 10, 10 });
	}
}
 
void CreateSupplement(AEVec2 initPos)
{
	//i) ������ ��ġ������ �����ϱ�
	//ii) �÷��̾��� �Ѿ��� �����Ҷ� ���� ��ó���� �����ϰ� �����ϱ�
	GameObject* supplement = new GameObject("BulletSupplement");
	GoManager::GetInst()->AddObject(supplement);
	supplement->AddComponent("Transform", new TransComponent(supplement));
	supplement->AddComponent("BulletAnim", new BulletAnimationComponent(supplement));
	//supplement->AddComponent("Sprite", new SpriteComponent(supplement));

	TransComponent* supple_trs = (TransComponent*)supplement->FindComponent("Transform");
	//initPos ���� ���� ��ġ�� �ָ� ��
	supple_trs->SetPos(initPos.x, initPos.y);
	supple_trs->SetScale({ 15,20 });

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
