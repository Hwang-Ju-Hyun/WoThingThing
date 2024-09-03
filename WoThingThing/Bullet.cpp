#include "Bullet.h"

#include "GoManager.h"
#include "GameObject.h"

#include "TransComponent.h"
#include "SpriteComponent.h"
#include "BulletComponent.h"

//use for drawrect
#include "ColliderManager.h"
void DrawRect(float bottomleft_x, float bottomleft_y, float topRight_x, float topRight_y, float r, float g, float b)
{
	AEGfxMeshStart();

	AEGfxVertexAdd(-0.5f, 0.5f, 0xFF000000, 0.0f, 1.0f);
	AEGfxVertexAdd(-0.5f, -0.5f, 0xFF000000, 0.0f, 0.0f);

	AEGfxVertexAdd(0.5f, -0.5f, 0xFF000000, 1.0f, 0.0f);
	AEGfxVertexAdd(0.5f, 0.5f, 0xFF000000, 1.0f, 1.0f);

	AEGfxVertexAdd(-0.5f, 0.5f, 0xFF000000, 0.0f, 1.0f);

	AEGfxVertexList* mesh = AEGfxMeshEnd();

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	//AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);


	//Set color to Multiply	
	AEGfxSetColorToMultiply(1, 1, 1, 1);

	//Set color to add
	AEGfxSetColorToAdd(r, g, b, 0);

	//Set Blend Mode
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1);

	//�̵� ��� ����
	AEVec2 Pos = { (bottomleft_x + topRight_x) / 2,(topRight_y + bottomleft_y) / 2 };
	AEVec2 Scale = { topRight_x - bottomleft_x ,topRight_y - bottomleft_y };
	AEMtx33 translateMtx;
	AEMtx33 m_matMatrix;
	AEMtx33Trans(&translateMtx, Pos.x, Pos.y);
	//ũ�� ��� ����
	AEMtx33 scaleMtx;
	AEMtx33Scale(&scaleMtx, Scale.x, Scale.y);

	//Concat
	AEMtx33Concat(&m_matMatrix, &translateMtx, &scaleMtx);

	AEGfxSetTransform(m_matMatrix.m);

	AEGfxMeshDraw(mesh, AE_GFX_MDM_LINES_STRIP);
}

void CreateBullet(AEVec2 initPos, AEVec2 nor_dVec, std::string _bulletname, bool _enemyShoot)
{
	if(!_enemyShoot)
	{
		if (remainBullet > 0)
		{
			remainBullet--;

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
	supplement->AddComponent("Sprite", new SpriteComponent(supplement));

	TransComponent* supple_trs = (TransComponent*)supplement->FindComponent("Transform");
	//initPos ���� ���� ��ġ�� �ָ� ��
	supple_trs->SetPos(initPos.x, initPos.y);
	supple_trs->SetScale({ 30,30 });


	DrawRect(supple_trs->GetPos().x - 15, supple_trs->GetPos().y - 15, 
		supple_trs->GetPos().x + 15, supple_trs->GetPos().y + 15, 1, 1, 0);
}

void AddBullet()
{
	if (remainBullet >= 0 && remainBullet < 4)
		remainBullet++;
}
