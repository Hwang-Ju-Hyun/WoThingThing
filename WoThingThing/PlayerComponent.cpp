#include "PlayerComponent.h"
#include "TransComponent.h"

#include "GameObject.h"
#include "GoManager.h"

PlayerComponent::PlayerComponent(GameObject* _owner) : BaseComponent(_owner)
{
	m_vVelocity = { 0.f, 0.f };
	dashVelocity = { 0.f, 0.f };
	dash_const = { 400.f, 400.f };
	jumpVelocity = { 0.f, 0.f };
	m_vGravity = { 0.f, 600.f };
}

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

	static_cast<TransComponent*>(player_trs)->SetPos(pos);
}
int cnt = 0;
void PlayerComponent::Update()
{
	TransComponent* player_trs = static_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));
	//Jump
	if (AEInputCheckTriggered(AEVK_W))
	{
		cnt++;
		if (cnt <= 100)
			Jump(400);
	}
	//Landing
	if (player_trs->GetPos().y <= -379.f)
		cnt = 0;

	if (AEInputCheckCurr(AEVK_W) && AEInputCheckCurr(AEVK_D) && AEInputCheckTriggered(AEVK_SPACE))
		Dash({ 1, 1 });
	//Left
	if (AEInputCheckCurr(AEVK_A))
	{
		if (player_trs->GetPos().x > -770)
			player_trs->AddPos(-5.f, 0.f);

		//Dash
		if (AEInputCheckCurr(AEVK_W) && AEInputCheckTriggered(AEVK_SPACE))
			Dash({ -1, 1 });
		else if (AEInputCheckTriggered(AEVK_SPACE))
			Dash({ -1, 0 });
	}

	//Right
	if (AEInputCheckCurr(AEVK_D))
	{
		if (player_trs->GetPos().x < 770)
			player_trs->AddPos(5.f, 0.f);

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

void PlayerComponent::LoadFromJson(const json& str)
{
	return;
}

json PlayerComponent::SaveToJson()
{
	return json();
}