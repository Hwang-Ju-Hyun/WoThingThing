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
	if (!Isvibration)
	{
		m_vLookAt = { player_trs->GetPos().x,player_trs->GetPos().y };
		AEGfxSetCamPosition(m_vLookAt.x, m_vLookAt.y);
	}
	else
	{
		AEVec2 playerPos = player_trs->GetPos();
		while (1)
		{
			float delatTime = AEFrameRateControllerGetFrameTime();
			AccTime += delatTime;						
			if (AccTime > 0.2f)
			{
				AccTime = 0.f;
				break;
			}
			if (AccTime <= 0.1f)
			{
				playerPos.x -= 1000.f;
			}
			else if (AccTime > 0.1f && AccTime <= 0.2f)
			{
				playerPos.x += 1700.f;
			}							
			AEGfxSetCamPosition(playerPos.x, playerPos.y);
		}		
	}
}

void CameraManager::Setvibration(bool _vib)
{
	Isvibration = _vib;
}

bool CameraManager::Getvibration()
{
	return Isvibration;
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

void CameraManager::AddLookAt(const AEVec2& _vLookAt)
{
	m_vLookAt.x += _vLookAt.x;
	m_vLookAt.y += _vLookAt.y;
}

const AEVec2& CameraManager::GetLookAt()
{
	return m_vLookAt;
}

void CameraManager::vibration()
{	
	TransComponent* player_trs = dynamic_cast<TransComponent*>(m_pPlayer->FindComponent("Transform"));
	while (1)
	{
		float delatTime = AEFrameRateControllerGetFrameTime();
		if (AccTime >= 1)
			break;
		AccTime += delatTime;
		if (AccTime <= 0.5)
		{
			AEVec2 playerPos = m_vLookAt;
			playerPos.x -= 300.f;
			m_vLookAt = { playerPos };
		}
		else if (AccTime > 0.5&&AccTime<1)
		{
			AEVec2 playerPos = m_vLookAt;
			playerPos.x += 3000.f;
			m_vLookAt = { playerPos };
		}
		AEGfxSetCamPosition(m_vLookAt.x, m_vLookAt.y);
	}		
	AccTime = 0.f;
}
