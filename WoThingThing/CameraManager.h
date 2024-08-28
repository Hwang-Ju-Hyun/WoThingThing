#pragma once
#include "header.h"

class GameObject;

class CameraManager
{
public:
	SINGLE(CameraManager);
private:
	AEVec2 m_vLookAt;
	AEVec2 m_vCurLookAt;
	AEVec2 m_vPrevLookAt;
	GameObject* player;
	GameObject* mouse;
	GameObject* aim;
public:
	void Update();	
public:
	void SetPlayer(GameObject* _player);
	void SetMouse(GameObject* _mouse);
	void SetAim(GameObject* _aim);
	void SetLookAt(const AEVec2& _vLookAt);
	const AEVec2& GetLookAt();
};