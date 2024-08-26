#pragma once
#include "header.h"
class TimeManager
{
public:
	SINGLE(TimeManager);
private:
	float m_fDt;
	float m_fAccTime;
public:
	const float& GetDeltaTime();
	const float& GetAccTime();
	void SetAccTime(float _time);
public:
	void Update();
};

