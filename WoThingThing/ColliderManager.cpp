#include "ColliderManager.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "TransComponent.h"
#include"TestLevel.h"//일단 테스트용
#include"IDLE.h"

ColliderManager::ColliderManager()
{

}

ColliderManager::~ColliderManager()
{

}

bool TestCollisionRectRect(float obj1Right, float obj1Left, float obj1Top, float obj1Bot,
	float obj2Right, float obj2Left, float obj2TopY, float obj2BotY)
{
	if (obj1Right<obj2Left || obj1Left>obj2Right || obj1Bot<obj2TopY || obj1Top>obj2BotY)
		return false;
	return true;
}

bool TestCollisionRectRectInclusive(float obj1Right, float obj1Left, float obj1Top, float obj1Bot,
	float obj2Right, float obj2Left, float obj2TopY, float obj2BotY)
{
	if (obj1Right > obj2Left && obj1Left < obj2Right && obj1Bot<obj2TopY && obj1Top>obj2BotY)
		return true;
	return false;
}
//나중에 여기 부분 건들기
bool ColliderManager::IsCollision(GameObject* _obj1, GameObject* _obj2)
{
	if (_obj1 == nullptr || _obj2 == nullptr)
	{
		return false;
	}


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

	return TestCollisionRectRect(obj1Right, obj1Left, obj1Top, obj1Bot, 
		obj2Right, obj2Left, obj2TopY, obj2BotY);
}

bool ColliderManager::IsCollision(GameObject* _obj1, TransComponent::Node _node)
{
	BaseComponent* obj_trs1 = _obj1->FindComponent("Transform");
	
	AEVec2 obj1_Pos = static_cast<TransComponent*>(obj_trs1)->GetPos();
	AEVec2 obj2_Pos = _node.node_pos;

	AEVec2 obj1_Scale = static_cast<TransComponent*>(obj_trs1)->GetScale();
	AEVec2 obj2_Scale = { 50.f,70.f };

	float obj1Right = obj1_Pos.x + obj1_Scale.x / 2.f;
	float obj1Left = obj1_Pos.x - obj1_Scale.x / 2.f;
	float obj1Top = obj1_Pos.y - obj1_Scale.y / 2.f;
	float obj1Bot = obj1_Pos.y + obj1_Scale.y / 2.f;

	float obj2Right = obj2_Pos.x + obj2_Scale.x / 2.f;
	float obj2Left = obj2_Pos.x - obj2_Scale.x / 2.f;
	float obj2TopY = obj2_Pos.y - obj2_Scale.y / 2.f;
	float obj2BotY = obj2_Pos.y + obj2_Scale.y / 2.f;


	if (obj1Right<obj2Left || obj1Left>obj2Right || obj1Bot<obj2TopY || obj1Top>obj2BotY)
		return false;
	return true;
}

bool ColliderManager::IsCollision(GameObject* _obj1, AEVec2 _vec)
{
	BaseComponent* obj_trs1 = _obj1->FindComponent("Transform");

	AEVec2 obj1_Pos = static_cast<TransComponent*>(obj_trs1)->GetPos();
	AEVec2 obj2_Pos = _vec;

	AEVec2 obj1_Scale = static_cast<TransComponent*>(obj_trs1)->GetScale();
	AEVec2 obj2_Scale = { 50.f,70.f };

	float obj1Right = obj1_Pos.x + obj1_Scale.x / 2.f;
	float obj1Left = obj1_Pos.x - obj1_Scale.x / 2.f;
	float obj1Top = obj1_Pos.y - obj1_Scale.y / 2.f;
	float obj1Bot = obj1_Pos.y + obj1_Scale.y / 2.f;

	float obj2Right = obj2_Pos.x + obj2_Scale.x / 2.f;
	float obj2Left = obj2_Pos.x - obj2_Scale.x / 2.f;
	float obj2TopY = obj2_Pos.y - obj2_Scale.y / 2.f;
	float obj2BotY = obj2_Pos.y + obj2_Scale.y / 2.f;

	if (obj1Right<obj2Left || obj1Left>obj2Right || obj1Bot<obj2TopY || obj1Top>obj2BotY)
		return false;
	return true;
}

//Player의 피견판정 범위 줄어들게 하기
bool ColliderManager::handle_Player_EnemyAtk_Collision(GameObject* _obj1, GameObject* _obj2)
{
	if (_obj1 == nullptr || _obj2 == nullptr)
	{
		return false;
	}

	//obj1이 player이기 때문에 건들기 
	BaseComponent* obj_trs1 = _obj1->FindComponent("Transform");
	BaseComponent* obj_trs2 = _obj2->FindComponent("Transform");
	AEVec2 obj1_Pos = static_cast<TransComponent*>(obj_trs1)->GetPos();
	AEVec2 obj2_Pos = static_cast<TransComponent*>(obj_trs2)->GetPos();

	AEVec2 obj1_Scale = static_cast<TransComponent*>(obj_trs1)->GetScale();
	AEVec2 obj2_Scale = static_cast<TransComponent*>(obj_trs2)->GetScale();

	float obj1Right = obj1_Pos.x + ((obj1_Scale.x / 4.f) - 8.f);
	float obj1Left = obj1_Pos.x - ((obj1_Scale.x / 4.f) - 8.f);
	float obj1Top = obj1_Pos.y - ((obj1_Scale.y / 4.f) - 4.f);
	float obj1Bot = obj1_Pos.y + ((obj1_Scale.y / 3.f));
	//DrawRect(obj1Left, obj1Bot, obj1Right, obj1Top, 1, 0, 0);

	float obj2Right = obj2_Pos.x + obj2_Scale.x / 2.f;
	float obj2Left = obj2_Pos.x - obj2_Scale.x / 2.f;
	float obj2TopY = obj2_Pos.y - obj2_Scale.y / 2.f;
	float obj2BotY = obj2_Pos.y + obj2_Scale.y / 2.f;

	return TestCollisionRectRect(obj1Right, obj1Left, obj1Top, obj1Bot,
		obj2Right, obj2Left, obj2TopY, obj2BotY);
}

//근접 캐릭터용, range부분 더 늘리기?
bool ColliderManager::EdgeSearch(GameObject* _obj1, GameObject* _obj2, bool enemy_dir, float x_range, float y_range,float bottom_y_range)
{
	if (_obj1 == nullptr || _obj2 == nullptr)
		return false;
	BaseComponent* enemy_trs = _obj1->FindComponent("Transform");
	BaseComponent* obj_trs2 = _obj2->FindComponent("Transform");

	AEVec2 enemy_Pos = static_cast<TransComponent*>(enemy_trs)->GetPos();
	AEVec2 obj2_Pos = static_cast<TransComponent*>(obj_trs2)->GetPos();
	
	AEVec2 enemy_Scale = static_cast<TransComponent*>(enemy_trs)->GetScale();
	AEVec2 obj2_Scale = static_cast<TransComponent*>(obj_trs2)->GetScale();
	
	float obj2Right = obj2_Pos.x + obj2_Scale.x / 2.f;
	float obj2Left = obj2_Pos.x - obj2_Scale.x / 2.f;
	float obj2TopY = obj2_Pos.y + obj2_Scale.y / 2.f;
	float obj2BotY = obj2_Pos.y - obj2_Scale.y / 2.f;

	//DrawRect(obj2Left, obj2BotY, obj2Right, obj2TopY, 1, 0, 0);
	
	//영역의 좌표(정사각형 기준)
	if (enemy_dir == true) //보는 방향에 따른 영역 변환
	{
		//이 부분 그리게 하기 나중에 코드 작성
		float Search_LeftArea_X = enemy_Pos.x - enemy_Scale.x; //왼쪽 방향으로 가고 있을 때
		float L_SearchPlayer_RightX = Search_LeftArea_X + enemy_Scale.x / 2.f;
		float L_SearchPlayer_LeftX = Search_LeftArea_X - x_range * (enemy_Scale.x / 2.f);//x축 범위
		float L_SearchPlayer_TopY = enemy_Pos.y + y_range * (enemy_Scale.y / 2.f);//y축 범위
		float L_SearchPlayer_BotY = enemy_Pos.y - bottom_y_range * (enemy_Scale.y / 2.f);
	
	
	
		//그리기영역
		//DrawRect(L_SearchPlayer_LeftX, L_SearchPlayer_BotY, L_SearchPlayer_RightX, L_SearchPlayer_TopY, 0, 0, 1);
		//--------------
		if (TestCollisionRectRectInclusive(L_SearchPlayer_RightX, L_SearchPlayer_LeftX, L_SearchPlayer_TopY, L_SearchPlayer_BotY,
			obj2Right, obj2Left, obj2TopY, obj2BotY))
		{
			//std::cout << "SearchPlayerLeft" << std::endl;
			return true;
		}
	}
	else if (enemy_dir == false)
	{
		float Search_RightArea_X = enemy_Pos.x + enemy_Scale.x;//오른쪽 방향으로 가고 있을 때
		float R_SearchPlayer_LeftX = Search_RightArea_X - enemy_Scale.x / 2.f;
		float R_SearchPlayer_RightX = Search_RightArea_X + x_range * (enemy_Scale.x / 2.f);
		float R_SearchPlayer_TopY = enemy_Pos.y + y_range * (enemy_Scale.y / 2.f);
		float R_SearchPlayer_BotY = enemy_Pos.y - bottom_y_range * (enemy_Scale.y / 2.f);
	
		//DrawRect(R_SearchPlayer_LeftX, R_SearchPlayer_BotY, R_SearchPlayer_RightX, R_SearchPlayer_TopY, 0, 0, 1);
		if (TestCollisionRectRectInclusive(R_SearchPlayer_RightX, R_SearchPlayer_LeftX, R_SearchPlayer_TopY, R_SearchPlayer_BotY,
			obj2Right, obj2Left, obj2TopY, obj2BotY))
		{
			//std::cout << "SearchPlayerLeft" << std::endl;
			return true;
		}
	}
	return false;
}


bool ColliderManager::PlayerSearch(GameObject* _obj1, GameObject* _obj2, bool enemy_dir, float x_range, float y_range, float bottom_y_range)
{
	if (_obj1 == nullptr || _obj2 == nullptr)
		return false;
	BaseComponent* enemy_trs = _obj1->FindComponent("Transform");
	BaseComponent* obj_trs2 = _obj2->FindComponent("Transform");

	AEVec2 enemy_Pos = static_cast<TransComponent*>(enemy_trs)->GetPos();
	AEVec2 obj2_Pos = static_cast<TransComponent*>(obj_trs2)->GetPos();

	AEVec2 enemy_Scale = static_cast<TransComponent*>(enemy_trs)->GetScale();
	AEVec2 obj2_Scale = static_cast<TransComponent*>(obj_trs2)->GetScale();

	float obj2Right = obj2_Pos.x + obj2_Scale.x / 2.f;
	float obj2Left = obj2_Pos.x - obj2_Scale.x / 2.f;
	float obj2TopY = obj2_Pos.y + obj2_Scale.y / 2.f;
	float obj2BotY = obj2_Pos.y - obj2_Scale.y / 2.f;

	//DrawRect(obj2Left, obj2BotY, obj2Right, obj2TopY, 1, 0, 0);

	//영역의 좌표(정사각형 기준)
	if (enemy_dir == true) //보는 방향에 따른 영역 변환
	{
		//이 부분 그리게 하기 나중에 코드 작성
		float Search_LeftArea_X = enemy_Pos.x - enemy_Scale.x; //왼쪽 방향으로 가고 있을 때
		float L_SearchPlayer_RightX = Search_LeftArea_X + enemy_Scale.x;
		float L_SearchPlayer_LeftX = Search_LeftArea_X - x_range * (enemy_Scale.x / 2.f);//x축 범위
		float L_SearchPlayer_TopY = enemy_Pos.y + y_range * (enemy_Scale.y / 2.f);//y축 범위
		float L_SearchPlayer_BotY = enemy_Pos.y - bottom_y_range * (enemy_Scale.y / 2.f);



		//그리기영역
		//DrawRect(L_SearchPlayer_LeftX, L_SearchPlayer_BotY, L_SearchPlayer_RightX, L_SearchPlayer_TopY, 1, 0, 0);
		//--------------
		if (TestCollisionRectRectInclusive(L_SearchPlayer_RightX, L_SearchPlayer_LeftX, L_SearchPlayer_TopY, L_SearchPlayer_BotY,
			obj2Right, obj2Left, obj2TopY, obj2BotY))
		{
			//std::cout << "SearchPlayerLeft" << std::endl;
			return true;
		}
	}
	else if (enemy_dir == false)
	{
		float Search_RightArea_X = enemy_Pos.x + enemy_Scale.x;//오른쪽 방향으로 가고 있을 때
		float R_SearchPlayer_LeftX = Search_RightArea_X - enemy_Scale.x;
		float R_SearchPlayer_RightX = Search_RightArea_X + x_range * (enemy_Scale.x / 2.f);
		float R_SearchPlayer_TopY = enemy_Pos.y + y_range * (enemy_Scale.y / 2.f);
		float R_SearchPlayer_BotY = enemy_Pos.y - bottom_y_range * (enemy_Scale.y / 2.f);

		//DrawRect(R_SearchPlayer_LeftX, R_SearchPlayer_BotY, R_SearchPlayer_RightX, R_SearchPlayer_TopY, 1, 0, 0);
		if (TestCollisionRectRectInclusive(R_SearchPlayer_RightX, R_SearchPlayer_LeftX, R_SearchPlayer_TopY, R_SearchPlayer_BotY,
			obj2Right, obj2Left, obj2TopY, obj2BotY))
		{
			//std::cout << "SearchPlayerLeft" << std::endl;
			return true;
		}
	}
	return false;
}


//보스 넉백 콜리전
bool ColliderManager::KnockBackCollision(GameObject* _obj1, GameObject* _obj2)
{
	//obj2는 보스여야함
	if (_obj1 == nullptr || _obj2 == nullptr)
	{
		return false;
	}	

	BaseComponent* obj_trs1 = _obj1->FindComponent("Transform");
	BaseComponent* obj_trs2 = _obj2->FindComponent("Transform");
	AEVec2 obj1_Pos = static_cast<TransComponent*>(obj_trs1)->GetPos();
	AEVec2 obj2_Pos = static_cast<TransComponent*>(obj_trs2)->GetPos();

	AEVec2 obj1_Scale = static_cast<TransComponent*>(obj_trs1)->GetScale();
	AEVec2 obj2_Scale = static_cast<TransComponent*>(obj_trs2)->GetScale();

	float obj1Right = obj1_Pos.x + obj1_Scale.x / 2.f;
	float obj1Left = obj1_Pos.x - obj1_Scale.x / 2.f;
	float obj1Top = obj1_Pos.y - obj1_Scale.y / 2.f;
	float obj1Bot = obj1_Pos.y + obj1_Scale.y / 2.f;


	float obj2Right =(obj2_Pos.x + obj2_Scale.x / 2.f)+50.f;
	float obj2Left = (obj2_Pos.x - obj2_Scale.x / 2.f)-50.f;
	float obj2TopY = (obj2_Pos.y - obj2_Scale.y / 2.f)-50.f;
	float obj2BotY = (obj2_Pos.y + obj2_Scale.y / 2.f)+50.f;

	//DrawRect(obj2Left, obj2BotY, obj2Right, obj2TopY, 1, 0, 0);

	return TestCollisionRectRect(obj1Right, obj1Left, obj1Top, obj1Bot,
		obj2Right, obj2Left, obj2TopY, obj2BotY);
}

//변수값만 잘주기
bool ColliderManager::MeleeEnemyAttack(GameObject* _obj1, GameObject* _obj2, bool enemy_dir)
{
	BaseComponent* enemy_trs = _obj1->FindComponent("Transform");
	BaseComponent* obj_trs2 = _obj2->FindComponent("Transform");
	AEVec2 enemy_Pos = static_cast<TransComponent*>(enemy_trs)->GetPos();
	AEVec2 obj2_Pos = static_cast<TransComponent*>(obj_trs2)->GetPos();

	AEVec2 enemy_Scale = static_cast<TransComponent*>(enemy_trs)->GetScale();
	AEVec2 obj2_Scale = static_cast<TransComponent*>(obj_trs2)->GetScale();

	float obj2RightX = obj2_Pos.x + ((obj2_Scale.x / 4.f) - 10.f);
	float obj2LeftX = obj2_Pos.x - ((obj2_Scale.x / 4.f) - 10.f);
	float obj2TopY = obj2_Pos.y + obj2_Scale.y / 2.f;
	float obj2BotY = obj2_Pos.y - obj2_Scale.y / 2.f;
	//DrawRect(obj2LeftX, obj2BotY, obj2RightX, obj2TopY, 1, 0, 0);

	//영역의 좌표(정사각형 기준)
	if (enemy_dir == true) //보는 방향에 따른 영역 변환
	{
		//이 부분 그리게 하기 나중에 코드 작성
		float Search_LeftArea_X = enemy_Pos.x - enemy_Scale.x; //왼쪽 방향으로 가고 있을 때
		float L_SearchPlayer_RightX = enemy_Pos.x + enemy_Scale.x / 2.f;
		float L_SearchPlayer_LeftX = enemy_Pos.x - (enemy_Scale.x / 2.f);//x축 범위
		float L_SearchPlayer_TopY = enemy_Pos.y + 1.f * (enemy_Scale.y / 2.f);//y축 범위
		float L_SearchPlayer_BotY = enemy_Pos.y - enemy_Scale.y / 2.f;

		//DrawRect(L_SearchPlayer_LeftX, L_SearchPlayer_BotY, L_SearchPlayer_RightX, L_SearchPlayer_TopY, 0, 1, 0);

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
		float Search_RightArea_X = enemy_Pos.x + enemy_Scale.x;//오른쪽 방향으로 가고 있을 때
		float R_SearchPlayer_LeftX = enemy_Pos.x - (enemy_Scale.x / 2.f);
		float R_SearchPlayer_RightX = enemy_Pos.x + (enemy_Scale.x / 2.f);
		float R_SearchPlayer_TopY = enemy_Pos.y + 1.f * (enemy_Scale.y / 2.f);
		float R_SearchPlayer_BotY = enemy_Pos.y - enemy_Scale.y / 2.f;

		//DrawRect(R_SearchPlayer_LeftX, R_SearchPlayer_BotY, R_SearchPlayer_RightX, R_SearchPlayer_TopY, 0, 1, 0);

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

//매개변수는 무조건 조정예정(지금은 불완정한 값이 들어온 상태 chase에서 하던 여기서 하던Rigid와 trans값을 받아와서 조정예정
////bool isFacingtheSameDirection(AEVec2 e_pos, AEVec2 player_pos, bool enemy_dir) 이런식으로
bool ColliderManager::isFacingtheSameDirection(AEVec2 chase_pos, bool enemy_dir)
{
	AEVec2 vec2;
	if (enemy_dir == true) //왼쪽
	{
		vec2 = { -1.0f, 0.0f };
	}
	else if (enemy_dir == false) //오른쪽
	{
		vec2 = { 1.0f, 0.0f };
	}
	float dotProduct = Dot(chase_pos, vec2);

	return dotProduct > 0;
}

float ColliderManager::Dot(const AEVec2& vec1, const AEVec2& vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}	



//bool isFacingtheSameDirection(e_pos, player_pos, direction)
//{
	// vec1 = enemy->player(적이 플레이어한테 가는 벡터 값
	// vec2 = enemy가 보고 있는 방향이니 direction 오른쪽인 경우 벡터(1,0) 왼쪽인 경우는 벡터(-1,0)을 준다
	//vec1과 vec2를 내적해서 나온 값이 양수면 같은방향(true반환) 음수면 다른방향(false반환)
	//
//}

void ColliderManager::DrawRect(float bottomleft_x, float bottomleft_y, float topRight_x, float topRight_y, float r, float g, float b)
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
	//AEGfxSetColorToMultiply(m_color.red , m_color.green , m_color.blue, 1);
	//AEGfxSetColorToMultiply(1, 0, 0, 1);

	//Set color to add
	AEGfxSetColorToAdd(r, g, b, 0);

	//Set Blend Mode
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1);

		//이동 행렬 생성
	AEVec2 Pos = { (bottomleft_x + topRight_x) / 2,(topRight_y + bottomleft_y) / 2 };
	AEVec2 Scale = { topRight_x - bottomleft_x ,topRight_y - bottomleft_y };
	AEMtx33 translateMtx;
	AEMtx33 m_matMatrix;
	AEMtx33Trans(&translateMtx, Pos.x, Pos.y);
		//크기 행렬 생성
	AEMtx33 scaleMtx;
	AEMtx33Scale(&scaleMtx, Scale.x, Scale.y);

		//Concat
	AEMtx33Concat(&m_matMatrix, &translateMtx, &scaleMtx);

	AEGfxSetTransform(m_matMatrix.m);

	AEGfxMeshDraw(mesh, AE_GFX_MDM_LINES_STRIP);

	//AEGfxEnd(); 반드시 지워야 함 코드(그래픽스)악의 존재
	AEGfxMeshFree(mesh);
	return;
}

void ColliderManager::SetPlayerSearchOnOff(bool _on)
{
	PlayerSearchOnOff = _on;
}

bool ColliderManager::GetPlayerSearchOnOff()
{
	return PlayerSearchOnOff;
}
