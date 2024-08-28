#include "TimeManager.h"

TimeManager::TimeManager()
    :m_fDt(0.f)
    ,m_fAccTime(0.f)
{

}

TimeManager::~TimeManager()
{

}

const float& TimeManager::GetDeltaTime()//�� �������� �ɸ��� �ð�
{
    return m_fDt;
}

const float& TimeManager::GetAccTime()//������ �ð�
{
    return m_fAccTime;
}

void TimeManager::SetAccTime(float _time)//�ð� ����
{
    m_fAccTime = _time;
}
    
void TimeManager::Update()
{
    m_fDt = (f32)AEFrameRateControllerGetFrameTime();
    m_fAccTime += m_fDt;
}
