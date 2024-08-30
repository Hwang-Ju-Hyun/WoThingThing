#include "IDLE.h"
#include"GameObject.h"
#include"TransComponent.h"
#include"EnemyStateManager.h"
#include"ColliderManager.h"
#include"TimeManager.h"
#include"TestLevel.h"//���� ���� ������Ʈ�� ���ؼ�(���߿��� ���� ������������ ����� ����)
//���߿� ���°��� ������Ű������ ���� ���� �Է��Ͽ� ���� ���ϱ�
#include"Chase.h"
#include "EnemyAttack.h"

//��ġ���� �ӵ����� �κ�
//���� ������Ʈ �ڱ��ڽ��� �޾ƾ���

void ESM::IDLE::Init()
{
	accumulatedTime = 0;
	TimeManager::GetInst()->SetAccTime(0.0f);
}

void ESM::IDLE::Update()
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



	if (ColliderManager::GetInst()->PlayerSearch(enemy, player, dir, 16.f, 8.f, 1.f))
	{
		//std::cout << "ChaseMode" << std::endl;
		ESM::Chase* p = new ESM::Chase(enemy, player, dir, dir_Time);
		ESM::EnemyStateManager::GetInst()->ChangeState(p);
	}

}

void ESM::IDLE::Exit()
{
	//delete enemy;
	//obj�� �� ������ �����ִ��� �׾��ִ���?
}

ESM::IDLE::IDLE(GameObject* _enemy, GameObject* _player, bool dir_num, float Time)
{
	enemy = _enemy;//enemyobject
	player = _player;//Playerobject
	dir = dir_num;
	dir_Time = Time;
}
