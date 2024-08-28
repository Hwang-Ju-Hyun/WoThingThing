#include "IDLE.h"
#include"GameObject.h"
#include"TransComponent.h"
#include"EnemyStateManager.h"
#include"ColliderManager.h"
#include"TimeManager.h"
#include"TestLevel.h"//���� ���� ������Ʈ�� ���ؼ�(���߿��� ���� ������������ ����� ����)
//���߿� ���°��� ������Ű������ ���� ���� �Է��Ͽ� ���� ���ϱ�
#include"Chase.h"

//��ġ���� �ӵ����� �κ�
//���� ������Ʈ �ڱ��ڽ��� �޾ƾ���

void ESM::IDLE::Init()
{
	accumulatedTime = 0;
}

void ESM::IDLE::Update()
{
	accumulatedTime = TimeManager::GetInst()->GetAccTime();
	//���⸸ �޶�����
	if (accumulatedTime >= 5.0f)
	{
		// �ð� �ʱ�ȭ
		TimeManager::GetInst()->SetAccTime(0.0f);
		// �߰��� �ʿ��� ������ ���⿡ �ۼ�
		std::cout << "5 seconds passed, resetting timer." << std::endl;

		//Level::TestLevel::enemy_dir = !(Level::TestLevel::enemy_dir);
	}

	if (ColliderManager::GetInst()->PlayerSearch(enemy, player))
	{
		//std::cout << "ChaseMode" << std::endl;
		ESM::Chase* p = new ESM::Chase(enemy, player);
		ESM::EnemyStateManager::GetInst()->ChangeState(p);
	}

}

void ESM::IDLE::Exit()
{
	//delete enemy;
	//obj�� �� ������ �����ִ��� �׾��ִ���?
}

ESM::IDLE::IDLE(GameObject* _enemy, GameObject* _player)
{
	enemy = _enemy;//enemyobject
	player = _player;//Playerobject
	
}
