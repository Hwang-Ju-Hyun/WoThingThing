#include "PlayerComponent.h"
#include "TransComponent.h"
#include "SpriteComponent.h"
#include "CameraManager.h"
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

	melee = new GameObject("Melee");
	GoManager::GetInst()->AddObject(melee); //GetInst() == GetPtr()
	melee->AddComponent("Transform", new TransComponent(melee));
	melee->AddComponent("Sprite", new SpriteComponent(melee));

	mouseAim = new GameObject("mouseAim");
	GoManager::GetInst()->AddObject(mouseAim);
	mouseAim->AddComponent("Transform", new TransComponent(mouseAim));
	mouseAim->AddComponent("Sprite", new SpriteComponent(mouseAim));
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
	std::cout << "FrameCnt: " << AEFrameRateControllerGetFrameCount() << std::endl;
	std::cout << "JUMP : " << pos.x << "\t" << pos.y << std::endl;
	std::cout << "JUMP : " << pos.x << "\t" << pos.y << std::endl;
	std::cout << "JUMP : " << pos.x << "\t" << pos.y << std::endl;
	std::cout << "JUMP : " << pos.x << "\t" << pos.y << std::endl;
	std::cout << "JUMP : " << pos.x << "\t" << pos.y << std::endl;
	std::cout << "JUMP : " << pos.x << "\t" << pos.y << std::endl;
	std::cout << "JUMP : " << pos.x << "\t" << pos.y << std::endl;
	std::cout << "JUMP : " << pos.x << "\t" << pos.y << std::endl;
	std::cout << "JUMP : " << pos.x << "\t" << pos.y << std::endl;
	std::cout << "JUMP : " << pos.x << "\t" << pos.y << std::endl;
}
void PlayerComponent::Dash(AEVec2 directVec)
{
	TransComponent* player_trs = static_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));
	AEVec2 pos = static_cast<TransComponent*>(player_trs)->GetPos();

	float dt = AEFrameRateControllerGetFrameTime();

	dashVelocity.x = directVec.x * dash_const.x;
	dashVelocity.y = directVec.y * dash_const.y;

	static_cast<TransComponent*>(player_trs)->SetPos(pos);
}
void PlayerComponent::MoveMent()
{
	TransComponent* player_trs = static_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));
	//Jump
	if (AEInputCheckTriggered(AEVK_W))
	{
		jumpCnt++;
		if (jumpCnt <= 2)
			Jump(400);
	}
	//Landing	
	// 황주현 코드 수정 -> 밑에 코드를 setjumpcntzero ::Stage01 handleCollision에서 구현
	//if (player_trs->GetPos().y <= -379.f)
	//	jumpCnt = 0;

	if (AEInputCheckCurr(AEVK_W) && AEInputCheckCurr(AEVK_D) && AEInputCheckTriggered(AEVK_SPACE))
		Dash({ 1, 1 });
	//Left
	if (AEInputCheckCurr(AEVK_A))
	{
		player_trs->AddPos(-5.f, 0.f);
		//if (player_trs->GetPos().x > -770)

		//Dash
		if (AEInputCheckCurr(AEVK_W) && AEInputCheckTriggered(AEVK_SPACE))
			Dash({ -1, 1 });
		else if (AEInputCheckTriggered(AEVK_SPACE))
			Dash({ -1, 0 });
	}

	//Right
	if (AEInputCheckCurr(AEVK_D))
	{
		player_trs->AddPos(5.f, 0.f);
		//if (player_trs->GetPos().x < 770)

		//Dash
		if (AEInputCheckCurr(AEVK_W) && AEInputCheckTriggered(AEVK_SPACE))
			Dash({ 1, 1 });
		else if (AEInputCheckTriggered(AEVK_SPACE))
			Dash({ 1, 0 });
	}

	AEVec2 pos = static_cast<TransComponent*>(player_trs)->GetPos();

	float dt = AEFrameRateControllerGetFrameTime();
	//left shift : time manipulation
	if (AEInputCheckCurr(AEVK_LSHIFT))
	{
		dt *= 0.1f;
	}

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
	//auto trans= CompManager::GetInst()->FindComponent("Transform");

	if (pos.y <= -380)
	{
		jumpVelocity.y = 0;
		pos.y = -380.f;
	}
	else
	{
		jumpVelocity.y -= m_vGravity.y * dt;
	}
	pos.y = pos.y + jumpVelocity.y * dt;
	static_cast<TransComponent*>(player_trs)->SetPos(pos);
}

//About mouse
void PlayerComponent::MouseAim()
{
	//Mouse Position
	TransComponent* aim_trs = (TransComponent*)mouseAim->FindComponent("Transform");
	SpriteComponent* aim_spr = (SpriteComponent*)mouseAim->FindComponent("Sprite");
	s32 mouseX, mouseY;
	AEInputGetCursorPosition(&mouseX, &mouseY);
	mouseX -= 800;              //mouse X position lerp
	mouseY -= 450, mouseY *= -1;//mouse Y position lerp

	mousePos.x = mouseX, mousePos.y = mouseY;
	AEVec2 player_Cam = CameraManager::GetInst()->GetLookAt();
	aim_trs->SetPos(mousePos);
	aim_trs->AddPos({ player_Cam.x,player_Cam.y });
}
AEVec2 PlayerComponent::GetMousePos()
{
	return mousePos;
}

//About Player's attack
bool PlayerComponent::GetWeaponType(int n)
{
	if (n == 1)
		return meleeActive;
	else if (n == 2)
		return shotActive;
}
void PlayerComponent::MeleeAttack()
{
	//melee attack
	if (AEInputCheckTriggered(AEVK_1))
		meleeActive = true, shotActive = false;
	//shot attack
	else if (AEInputCheckTriggered(AEVK_2))
		meleeActive = false, shotActive = true;

	if (meleeActive)
	{
		TransComponent* player_trs = static_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));
		TransComponent* melee_trs = static_cast<TransComponent*>(melee->FindComponent("Transform"));

		AEVec2 dVec = { (mousePos.x - player_trs->GetPos().x), (mousePos.y - player_trs->GetPos().y) };
		AEVec2 nor_dVec{ 0,0 };
		AEVec2Normalize(&nor_dVec, &dVec);
		melee_trs->SetPos((player_trs->GetPos().x * nor_dVec.x) + (nor_dVec.x * player_trs->GetScale().x),
			(player_trs->GetPos().y * nor_dVec.x) + (nor_dVec.y * player_trs->GetScale().y));

		if (AEInputCheckTriggered(AEVK_LBUTTON))
			melee_trs->SetScale({ 100, 100 });
		else
			melee_trs->SetScale({ 0, 0 });

		
	}
}


// 황주현 코드 추가
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
	MeleeAttack();
	MouseAim();
}

void PlayerComponent::LoadFromJson(const json& str)
{
	return;
}

json PlayerComponent::SaveToJson()
{
	return json();
}