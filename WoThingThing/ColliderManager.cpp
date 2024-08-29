#include "ColliderManager.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "TransComponent.h"
#include"TestLevel.h"//�ϴ� �׽�Ʈ��
#include"IDLE.h"

ColliderManager::ColliderManager()
{

}

ColliderManager::~ColliderManager()
{

}
//���߿� ���� �κ� �ǵ��
bool ColliderManager::IsCollision(GameObject* _obj1, GameObject* _obj2)
{
	BaseComponent* obj_trs1 = _obj1->FindComponent("Transform");
	BaseComponent* obj_trs2 = _obj2->FindComponent("Transform");
	AEVec2 obj1_Pos = static_cast<TransComponent*>(obj_trs1)->GetPos();
	AEVec2 obj2_Pos = static_cast<TransComponent*>(obj_trs2)->GetPos();
	
	AEVec2 obj1_Scale = static_cast<TransComponent*>(obj_trs1)->GetScale();
	AEVec2 obj2_Scale = static_cast<TransComponent*>(obj_trs2)->GetScale();

	float obj1Right    = obj1_Pos.x + obj1_Scale.x/2.f;
	float obj1Left     = obj1_Pos.x - obj1_Scale.x /2.f;
	float obj1Top      = obj1_Pos.y - obj1_Scale.y / 2.f;
	float obj1Bot      = obj1_Pos.y + obj1_Scale.y / 2.f;
	
	float obj2Right	   = obj2_Pos.x + obj2_Scale.x / 2.f;
	float obj2Left 	   = obj2_Pos.x - obj2_Scale.x / 2.f;
	float obj2TopY     = obj2_Pos.y - obj2_Scale.y / 2.f;
	float obj2BotY     = obj2_Pos.y + obj2_Scale.y / 2.f;

	if (obj1Right<obj2Left || obj1Left>obj2Right || obj1Bot<obj2TopY || obj1Top>obj2BotY)
		return false;
	return true;
}

//���� ĳ���Ϳ� 
bool ColliderManager::PlayerSearch(GameObject* _obj1, GameObject* _obj2, bool enemy_dir)
{
	BaseComponent* enemy_trs = _obj1->FindComponent("Transform");
	BaseComponent* obj_trs2 = _obj2->FindComponent("Transform");
	AEVec2 enemy_Pos = static_cast<TransComponent*>(enemy_trs)->GetPos();
	AEVec2 obj2_Pos = static_cast<TransComponent*>(obj_trs2)->GetPos();

	AEVec2 enemy_Scale = static_cast<TransComponent*>(enemy_trs)->GetScale();
	AEVec2 obj2_Scale = static_cast<TransComponent*>(obj_trs2)->GetScale();

	float obj2RightX = obj2_Pos.x + obj2_Scale.x / 2.f;
	float obj2LeftX = obj2_Pos.x - obj2_Scale.x / 2.f;
	float obj2TopY = obj2_Pos.y + obj2_Scale.y / 2.f;
	float obj2BotY = obj2_Pos.y - obj2_Scale.y / 2.f;

	//������ ��ǥ(���簢�� ����)
	if (enemy_dir == true) //���� ���⿡ ���� ���� ��ȯ
	{
		//�� �κ� �׸��� �ϱ� ���߿� �ڵ� �ۼ�
		float Search_LeftArea_X = enemy_Pos.x - enemy_Scale.x; //���� �������� ���� ���� ��
		float L_SearchPlayer_RightX = Search_LeftArea_X + enemy_Scale.x / 2.f;
		float L_SearchPlayer_LeftX = Search_LeftArea_X - 16.f * (enemy_Scale.x / 2.f);//x�� ����
		float L_SearchPlayer_TopY = enemy_Pos.y + 8.f * (enemy_Scale.y / 2.f);//y�� ����
		float L_SearchPlayer_BotY = enemy_Pos.y - enemy_Scale.y / 2.f;



		//�׸��⿵��
		DrawRect(L_SearchPlayer_LeftX, L_SearchPlayer_BotY, L_SearchPlayer_RightX, L_SearchPlayer_TopY, 1, 0, 0);
		//--------------

		if (L_SearchPlayer_LeftX < obj2_Pos.x &&
			L_SearchPlayer_RightX > obj2_Pos.x &&
			L_SearchPlayer_BotY < obj2_Pos.y &&
			L_SearchPlayer_TopY > obj2_Pos.y)
		{
			//std::cout << "SearchPlayerLeft" << std::endl;
			return true;
		}

	}
	else if (enemy_dir == false)
	{
		float Search_RightArea_X = enemy_Pos.x + enemy_Scale.x;//������ �������� ���� ���� ��
		float R_SearchPlayer_LeftX = Search_RightArea_X - enemy_Scale.x / 2.f;
		float R_SearchPlayer_RightX = Search_RightArea_X + 16.f * (enemy_Scale.x / 2.f);
		float R_SearchPlayer_TopY = enemy_Pos.y + 8.f * (enemy_Scale.y / 2.f);
		float R_SearchPlayer_BotY = enemy_Pos.y - enemy_Scale.y / 2.f;

		DrawRect(R_SearchPlayer_LeftX, R_SearchPlayer_BotY, R_SearchPlayer_RightX, R_SearchPlayer_TopY, 1, 0, 0);
		if (R_SearchPlayer_LeftX < obj2_Pos.x &&
			R_SearchPlayer_RightX > obj2_Pos.x &&
			R_SearchPlayer_BotY < obj2_Pos.y &&
			R_SearchPlayer_TopY > obj2_Pos.y)
		{
			//std::cout << "SearchPlayerRight" << std::endl;
			return true;
		}
	}
	return false;
}

bool ColliderManager::MeleeEnemyAttack(GameObject* _obj1, GameObject* _obj2, bool enemy_dir)
{
	BaseComponent* enemy_trs = _obj1->FindComponent("Transform");
	BaseComponent* obj_trs2 = _obj2->FindComponent("Transform");
	AEVec2 enemy_Pos = static_cast<TransComponent*>(enemy_trs)->GetPos();
	AEVec2 obj2_Pos = static_cast<TransComponent*>(obj_trs2)->GetPos();

	AEVec2 enemy_Scale = static_cast<TransComponent*>(enemy_trs)->GetScale();
	AEVec2 obj2_Scale = static_cast<TransComponent*>(obj_trs2)->GetScale();

	float obj2RightX = obj2_Pos.x + obj2_Scale.x / 2.f;
	float obj2LeftX = obj2_Pos.x - obj2_Scale.x / 2.f;
	float obj2TopY = obj2_Pos.y + obj2_Scale.y / 2.f;
	float obj2BotY = obj2_Pos.y - obj2_Scale.y / 2.f;

	//������ ��ǥ(���簢�� ����)
	if (enemy_dir == true) //���� ���⿡ ���� ���� ��ȯ
	{
		//�� �κ� �׸��� �ϱ� ���߿� �ڵ� �ۼ�
		float Search_LeftArea_X = enemy_Pos.x - enemy_Scale.x; //���� �������� ���� ���� ��
		float L_SearchPlayer_RightX = Search_LeftArea_X + enemy_Scale.x / 2.f;
		float L_SearchPlayer_LeftX = Search_LeftArea_X - 1.f * (enemy_Scale.x / 2.f);//x�� ����
		float L_SearchPlayer_TopY = enemy_Pos.y + 1.f * (enemy_Scale.y / 2.f);//y�� ����
		float L_SearchPlayer_BotY = enemy_Pos.y - enemy_Scale.y / 2.f;

		DrawRect(L_SearchPlayer_LeftX, L_SearchPlayer_BotY, L_SearchPlayer_RightX, L_SearchPlayer_TopY, 0, 1, 0);

		if (L_SearchPlayer_LeftX < obj2_Pos.x &&
			L_SearchPlayer_RightX > obj2_Pos.x &&
			L_SearchPlayer_BotY < obj2_Pos.y &&
			L_SearchPlayer_TopY > obj2_Pos.y)
		{
			//std::cout << "SearchPlayerLeft" << std::endl;
			return true;
		}

	}
	else if (enemy_dir == false)
	{
		float Search_RightArea_X = enemy_Pos.x + enemy_Scale.x;//������ �������� ���� ���� ��
		float R_SearchPlayer_LeftX = Search_RightArea_X - (enemy_Scale.x / 2.f);
		float R_SearchPlayer_RightX = Search_RightArea_X + 1.f * (enemy_Scale.x / 2.f);
		float R_SearchPlayer_TopY = enemy_Pos.y + 1.f * (enemy_Scale.y / 2.f);
		float R_SearchPlayer_BotY = enemy_Pos.y - enemy_Scale.y / 2.f;

		DrawRect(R_SearchPlayer_LeftX, R_SearchPlayer_BotY, R_SearchPlayer_RightX, R_SearchPlayer_TopY, 0, 1, 0);

		if (R_SearchPlayer_LeftX < obj2_Pos.x &&
			R_SearchPlayer_RightX > obj2_Pos.x &&
			R_SearchPlayer_BotY < obj2_Pos.y &&
			R_SearchPlayer_TopY > obj2_Pos.y)
		{
			//std::cout << "SearchPlayerRight" << std::endl;
			return true;
		}
	}
	return false;
}

void ColliderManager::DrawRect(float bottomleft_x, float bottomleft_y, float topRight_x, float topRight_y, float r, float g, float b)
{
	AEGfxMeshStart();

	//AEGfxTriAdd(
	//	-0.5f, -0.5f, 0xFF000000, 0.0f, 1.0f,
	//	0.5f, -0.5f, 0xFF000000, 1.0f, 1.0f,
	//	-0.5f, 0.5f, 0xFF000000, 0.0f, 0.0f);
	//
	//AEGfxTriAdd(
	//	0.5f, -0.5f, 0xFF000000, 1.0f, 1.0f,
	//	0.5f, 0.5f, 0xFF000000, 1.0f, 0.0f,
	//	-0.5f, 0.5f, 0xFF000000, 0.0f, 0.0f);

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
	//AEGfxSetColorToMultiply(m_color.red , m_color.green , m_color.blue, 1);
	//AEGfxSetColorToMultiply(1, 0, 0, 1);

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

	return;
}
