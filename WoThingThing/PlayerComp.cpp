#include "PlayerComp.h"
#include "TransComponent.h"
#include "GameObject.h"

PlayerComp::PlayerComp(GameObject* _owner) : BaseComponent(_owner)
{
	m_vVelocity = { 0.f, 0.f };
	dashVelocity = { 0.f, 0.f };
	dash_const = { 400.f, 400.f };
	jumpVelocity = { 0.f, 0.f };
	m_vGravity = { 0.f, 600.f };
}

void PlayerComp::Jump(float jumpVal)
{
	auto trans = GetOwner()->FindComponent("Transform");
	AEVec2 pos = static_cast<TransComponent*>(trans)->GetPos();
	float dt = AEFrameRateControllerGetFrameTime();
	jumpVelocity.y = jumpVal;
	pos.y += jumpVelocity.y * dt;
	static_cast<TransComponent*>(trans)->SetPos(pos);
}

void PlayerComp::Dash(AEVec2 directVec)
{
	auto trans = GetOwner()->FindComponent("Transform");
	AEVec2 pos = static_cast<TransComponent*>(trans)->GetPos();

	float dt = AEFrameRateControllerGetFrameTime();

	dashVelocity.x = directVec.x * dash_const.x;
	dashVelocity.y = directVec.y * dash_const.y;

	static_cast<TransComponent*>(trans)->SetPos(pos);
}

void PlayerComp::Update()
{
	auto trans = GetOwner()->FindComponent("Transform");
	AEVec2 pos = static_cast<TransComponent*>(trans)->GetPos();

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
	static_cast<TransComponent*>(trans)->SetPos(pos);

}

void PlayerComp::LoadFromJson(const json& str)
{
	return;
}

json PlayerComp::SaveToJson()
{
	return json();
}