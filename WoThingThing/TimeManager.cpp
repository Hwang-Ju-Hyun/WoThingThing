#include "TimeManager.h"

TimeManager::TimeManager()
    :m_fDt(0.f)
    ,m_fAccTime(0.f)
{

}

TimeManager::~TimeManager()
{

}

const float& TimeManager::GetDeltaTime()
{
    return m_fDt;
}

const float& TimeManager::GetAccTime()
{
    return m_fAccTime;
}

void TimeManager::SetAccTime(float _time)
{
    m_fAccTime = _time;
}

void TimeManager::Update()
{
    m_fDt = (f32)AEFrameRateControllerGetFrameTime();
    m_fAccTime += m_fDt;
}
