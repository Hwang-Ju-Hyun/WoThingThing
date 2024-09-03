#include "TimeManager.h"

TimeManager::TimeManager()
    :m_fDt(0.f)
    ,m_fAccTime(0.f)
{

}

TimeManager::~TimeManager()
{

}

const float& TimeManager::GetDeltaTime()//한 프레임이 걸리는 시간
{
    return m_fDt;
}

const float& TimeManager::GetAccTime()//누적된 시간
{
    return m_fAccTime;
}

void TimeManager::SetAccTime(float _time)//시간 설정
{
    m_fAccTime = _time;
}
    
void TimeManager::Update()
{
    m_fDt = (f32)AEFrameRateControllerGetFrameTime();
    m_fAccTime += m_fDt;
}
