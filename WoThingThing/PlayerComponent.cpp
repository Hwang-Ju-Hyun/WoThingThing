#include "PlayerComponent.h"
#include "TransComponent.h"
#include "SpriteComponent.h"
#include "CameraManager.h"

#include "Bullet.h"
#include "BulletComponent.h"

#include "GameObject.h"
#include "GoManager.h"
int PlayerComponent::jumpCnt = 0;
bool PlayerComponent::meleeActive = true;
bool PlayerComponent::shotActive = false;

PlayerComponent::PlayerComponent(GameObject* _owner) : BaseComponent(_owner)
{
	m_vVelocity = { 0.f, 0.f };

	dashVelocity = { 0.f, 0.f };
	dash_const = { 400.f, 400.f };
	jumpVelocity = { 0.f, 400.f };
	m_vGravity = { 0.f, 600.f };

	mouseAim = new GameObject("mouseAim");
	GoManager::GetInst()->AddObject(mouseAim);
	mouseAim->AddComponent("Transform", new TransComponent(mouseAim));
	mouseAim->AddComponent("Sprite", new SpriteComponent(mouseAim));

	aim_line = new GameObject("AimLine");
	GoManager::GetInst()->AddObject(aim_line);
	aim_line->AddComponent("Transform", new TransComponent(aim_line));
	aim_line->AddComponent("Sprite", new SpriteComponent(aim_line));

	melee = nullptr;

	timeManipul = 7.f;
	manipulActive = false;
}

//About Player's movement
void PlayerComponent::Jump(float jumpVal)
{
	TransComponent* player_trs = static_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));
	AEVec2 pos = static_cast<TransComponent*>(player_trs)->GetPos();
	float dt = AEFrameRateControllerGetFrameTime();
	jumpVelocity.y = jumpVal;
	pos.y += jumpVelocity.y * dt;
	static_cast<TransComponent*>(player_trs)->SetPos(pos);
}
void PlayerComponent::Dash(AEVec2 directVec)
{
	TransComponent* player_trs = static_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));
	AEVec2 pos = static_cast<TransComponent*>(player_trs)->GetPos();

	float dt = AEFrameRateControllerGetFrameTime();

	dashVelocity.x = directVec.x * dash_const.x;
	dashVelocity.y = directVec.y * dash_const.y;


}
void PlayerComponent::MoveMent()
{
	TransComponent* player_trs = static_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));
	float dt = AEFrameRateControllerGetFrameTime();
	//D �� SHIFT�� ���������� ���� �� --> �׳� SHIFT�� ������ ������ ��ü������ ����ǰ� ����
	if (AEInputCheckCurr(AEVK_LSHIFT))
	{
		manipulActive = true;
		timeManipul -= dt;
		std::cout << timeManipul << std::endl;

		if (timeManipul <= 0.f)
		{
			manipulActive = false; //�������� 0�̸� ������ ���ȿ��� Manipulate�� �ȵǰ�
			timeManipul = 0.f;
		}
	}
	if (!AEInputCheckCurr(AEVK_LSHIFT))
	{
		manipulActive = false;
		if (timeManipul < 7.f)
			timeManipul += dt;
		std::cout << timeManipul << std::endl;
	}

	//Jump
	if (AEInputCheckTriggered(AEVK_W))
	{
		jumpCnt++;
		if (jumpCnt <= 2000)
			Jump(400);
	}
	//Landing	
	// Ȳ���� �ڵ� ���� -> �ؿ� �ڵ带 setjumpcntzero ::Stage01 handleCollision���� ����
	if (AEInputCheckCurr(AEVK_W) && AEInputCheckCurr(AEVK_D) && AEInputCheckTriggered(AEVK_SPACE))
		Dash({ 1, 1 });
	//Left
	if (AEInputCheckCurr(AEVK_A))
	{
		//player_trs->AddPos(-5.f, 0.f);
		player_trs->MovePos(-5.f, 0.f, manipulActive, dt);
		//Dash
		if (AEInputCheckCurr(AEVK_W) && AEInputCheckTriggered(AEVK_SPACE))
			Dash({ -1, 1 });
		else if (AEInputCheckTriggered(AEVK_SPACE))
			Dash({ -1, 0 });
	}
	//Right
	if (AEInputCheckCurr(AEVK_D))
	{
		//player_trs->AddPos(5.f, 0.f);
		player_trs->MovePos(5.f, 0.f, manipulActive, dt);
		//Dash
		if (AEInputCheckCurr(AEVK_W) && AEInputCheckTriggered(AEVK_SPACE))
			Dash({ 1, 1 });
		else if (AEInputCheckTriggered(AEVK_SPACE))
			Dash({ 1, 0 });
	}

	AEVec2 pos = static_cast<TransComponent*>(player_trs)->GetPos();

	//left shift : time manipulation
	if (AEInputCheckCurr(AEVK_LSHIFT)&& manipulActive)
		//if (manipulActive)
			dt *= 0.1f;

	//if dash velocity is too low. set to 0 (dash ended)
	if (AEVec2Length(&dashVelocity) <= 300.f)
	{
		AEVec2Zero(&dashVelocity);
	}

	//dash
	dashVelocity.x = dashVelocity.x * (1 - dt);
	dashVelocity.y = dashVelocity.y * (1 - dt);
	pos.x += (dashVelocity.x) * (2 * dt);
	pos.y += (dashVelocity.y) * (1.f * dt);

	//Gravity
	jumpVelocity.y -= m_vGravity.y * dt;	
	pos.y = pos.y + jumpVelocity.y * dt;
	static_cast<TransComponent*>(player_trs)->SetPos(pos);
}

bool PlayerComponent::GetManiActive()
{
	return manipulActive;
}

//About mouse
void PlayerComponent::MouseAim()
{
	//Mouse Position
	TransComponent* aim_trs = (TransComponent*)mouseAim->FindComponent("Transform");
	s32 mouseX, mouseY;
	AEInputGetCursorPosition(&mouseX, &mouseY);
	mouseX -= 800;              //mouse X position lerp
	mouseY -= 450, mouseY *= -1;//mouse Y position lerp

	mousePos.x = mouseX, mousePos.y = mouseY;
	AEVec2 player_Cam = CameraManager::GetInst()->GetLookAt();
	aim_trs->SetPos(mousePos);
	aim_trs->AddPos({ player_Cam.x,player_Cam.y });

	//Mouse Position Lerp
	//mousePos == mouse position in world coord
	//player_Cam == player position in camera coord
	//so, mousePos += player_Cam == World coord mouse position to Camera coord mouse position.
	mousePos.x += player_Cam.x;
	mousePos.y += player_Cam.y;
}
void PlayerComponent::MouseTraceLine()
{
	TransComponent* aimTrace_trs = (TransComponent*)aim_line->FindComponent("Transform");
	AEVec2 player_Cam = CameraManager::GetInst()->GetLookAt();

	aimTrace_trs->SetPos((mousePos.x + player_Cam.x) / 2.f, (mousePos.y + player_Cam.y) / 2.f);

	AEVec2 lineDirection = { mousePos.x - player_Cam.x, mousePos.y - player_Cam.y };
	//scale
	float dis = AEVec2Length(&lineDirection);
	aimTrace_trs->SetScale({ dis, 1 });
	//rotation
	AEVec2 nor_lineDirection = { 0,0 };
	AEVec2Normalize(&nor_lineDirection, &lineDirection);

	//if mouse position in sector 3, 4 : reverse line
	if (nor_lineDirection.y < 0)
		nor_lineDirection.x *= -1;
	//////////////////////////////////////////////////

	aimTrace_trs->SetRot(AEACos(nor_lineDirection.x));
	//aim_trs->AddPos({ player_Cam.x,player_Cam.y });
}
AEVec2 PlayerComponent::GetMousePos()
{
	return mousePos;
}

//About Player's attack
void PlayerComponent::Attack()
{
	//melee attack
	if (AEInputCheckTriggered(AEVK_1))
		meleeActive = true, shotActive = false;
	//shot attack
	else if (AEInputCheckTriggered(AEVK_2))
		meleeActive = false, shotActive = true;

	TransComponent* player_trs = static_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));

	AEVec2 player_Cam = CameraManager::GetInst()->GetLookAt();

	//Direction Vector between player and mouse
	AEVec2 dVec = { (mousePos.x - player_trs->GetPos().x), (mousePos.y - player_trs->GetPos().y) }; //direction Vector
	AEVec2 nor_dVec{ 0,0 }; //Normailize direction Vector
	AEVec2Normalize(&nor_dVec, &dVec);

	if (meleeActive)
	{
		//Remove about shotAttack
		TransComponent* aimTrace_spr = (TransComponent*)aim_line->FindComponent("Transform");
		aimTrace_spr->SetScale({ 0,0 });
		/////////////////////////

		if (AEInputCheckTriggered(AEVK_LBUTTON))
		{
			if(melee == nullptr)
			{
				melee = new GameObject("Melee");
				GoManager::GetInst()->AddObject(melee); //GetInst() == GetPtr()
				melee->AddComponent("Transform", new TransComponent(melee));
				melee->AddComponent("Sprite", new SpriteComponent(melee));

				TransComponent* melee_trs = static_cast<TransComponent*>(melee->FindComponent("Transform"));
				melee_trs->SetPos(player_trs->GetPos().x + (nor_dVec.x * 50.f), player_trs->GetPos().y + (nor_dVec.y * 50.f));
				//
				melee_trs->SetScale({ 100, 100 });
			}
		}
		else
		{
			//melee_trs->SetScale({ 0, 0 });
			if (melee != nullptr)
			{
				//delete melee;
				melee->SetActive(false); //Set false means DELETE AND REMOVE GO.
				melee = nullptr; //I dont have a melee anymore

			}
		}
	}
	else if (shotActive)
	{
		MouseTraceLine();
		if (AEInputCheckTriggered(AEVK_LBUTTON))
		{
			CreateBullet(player_trs->GetPos(), nor_dVec, "PlayerBullet", false);

		}
	}
}
GameObject* PlayerComponent::GetMelee()
{
	return melee;
}


// Ȳ���� �ڵ� �߰�
void PlayerComponent::SetJumpCntZero()
{
	jumpCnt = 0;
}
void PlayerComponent::SetJumpVelocityZero()
{
	jumpVelocity.y = 0.f;
}

void PlayerComponent::Update()
{
	MoveMent();
	MouseAim();
	Attack();
}

void PlayerComponent::LoadFromJson(const json& str)
{
	return;
}
json PlayerComponent::SaveToJson()
{
	return json();
}