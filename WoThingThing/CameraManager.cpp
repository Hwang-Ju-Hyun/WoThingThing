#include "CameraManager.h"
#include "TimeManager.h"
#include "GoManager.h"
#include "GameObject.h"
#include "TransComponent.h"
CameraManager::CameraManager()
	:m_vLookAt{}
{

}

CameraManager::~CameraManager()
{

}


void CameraManager::Update()
{		
	TransComponent* player_trs = dynamic_cast<TransComponent*>(player->FindComponent("Transform"));	
	TransComponent* mouse_trs = dynamic_cast<TransComponent*>(mouse->FindComponent("Transform"));
	TransComponent* aim_trs = dynamic_cast<TransComponent*>(aim->FindComponent("Transform"));
	float playerCamX = player_trs->GetPos().x;
	float playerCamY = player_trs->GetPos().y;	

	mouse_trs->AddPos({ playerCamX,playerCamY });
	//aim_trs->AddPos({ playerCamX,playerCamY });
	AEGfxSetCamPosition(playerCamX, playerCamY);
}

void CameraManager::SetPlayer(GameObject* _player)
{
	player = _player;
}

void CameraManager::SetMouse(GameObject* _mouse)
{
	mouse = _mouse;
}

void CameraManager::SetAim(GameObject* _aim)
{
	aim = _aim;
}



void CameraManager::SetLookAt(const AEVec2& _vLookAt)
{
	m_vLookAt = _vLookAt;
}

const AEVec2& CameraManager::GetLookAt()
{
	return m_vLookAt;
}
