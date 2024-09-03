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
	TransComponent* player_trs = dynamic_cast<TransComponent*>(m_pPlayer->FindComponent("Transform"));
	m_vLookAt = { player_trs->GetPos().x,player_trs->GetPos().y };			
	AEGfxSetCamPosition(m_vLookAt.x, m_vLookAt.y);
}

void CameraManager::SetPlayer(GameObject* _player)
{
	m_pPlayer = _player;
}

void CameraManager::SetMouse(GameObject* _mouse)
{
	m_pMouseAim = _mouse;
}

void CameraManager::SetAim(GameObject* _aim)
{
	m_pAimTracer = _aim;
}



void CameraManager::SetLookAt(const AEVec2& _vLookAt)
{
	m_vLookAt = _vLookAt;
}

const AEVec2& CameraManager::GetLookAt()
{
	return m_vLookAt;
}
