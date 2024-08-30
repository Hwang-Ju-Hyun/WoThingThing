#include "IDLE_Sniper.h"
#include"GameObject.h"
#include"TransComponent.h"
#include"EnemyStateManager.h"
#include"ColliderManager.h"
#include"TimeManager.h"
#include "TargetAim_Sniper.h"
#include"SpriteComponent.h"

void ESM::IDLE_Sniper::Init()
{
	accumulatedTime = 0;
	TimeManager::GetInst()->SetAccTime(0.0f);
}

void ESM::IDLE_Sniper::Update()
{
	accumulatedTime = TimeManager::GetInst()->GetAccTime();

	if (dir_Time != 0)
	{
		//���⸸ �޶�����
		if (accumulatedTime >= dir_Time)//5.0f����
		{
			// �ð� �ʱ�ȭ
			TimeManager::GetInst()->SetAccTime(0.0f);
			// �߰��� �ʿ��� ������ ���⿡ �ۼ�
			std::cout << dir_Time << " Turn Dir" << std::endl;
			dir = !(dir);
		}
	}

	
	if (ColliderManager::GetInst()->PlayerSearch(enemy, player, dir, 20.f, 10.f,10.f))//���⿡ �������� ����
	{
		//�������۴� �ٷ� ���ݸ��� �����Ѵ�.
		ESM::TargetAim_Sniper* p = new ESM::TargetAim_Sniper(enemy, player, dir, dir_Time, bullet);
		ESM::EnemyStateManager::GetInst()->ChangeState(p);
	}

}

void ESM::IDLE_Sniper::Exit()
{
}

ESM::IDLE_Sniper::IDLE_Sniper(GameObject* _enemy, GameObject* _player, bool dir_num, float Time, GameObject* _bullet)
{
	enemy = _enemy;//enemyobject
	player = _player;//Playerobject
	dir = dir_num;
	dir_Time = Time;
	bullet = _bullet;
}
