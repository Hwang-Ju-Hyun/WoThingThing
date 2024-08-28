#include "IDLE.h"
#include"GameObject.h"
#include"TransComponent.h"
#include"EnemyStateManager.h"
#include"ColliderManager.h"
#include"TimeManager.h"
#include"TestLevel.h"//���� ���� ������Ʈ�� ���ؼ�


//��ġ���� �ӵ����� �κ�
//���� ������Ʈ �ڱ��ڽ��� �޾ƾ���
bool ESM::IDLE::SearchPlayer = false;

void ESM::IDLE::Init()
{
	accumulatedTime = 0;
}

void ESM::IDLE::Update()
{
	accumulatedTime = TimeManager::GetInst()->GetAccTime();
	if (accumulatedTime >= 5.0f)
	{
		// �ð� �ʱ�ȭ
		TimeManager::GetInst()->SetAccTime(0.0f);
		// �߰��� �ʿ��� ������ ���⿡ �ۼ�
		std::cout << "5 seconds passed, resetting timer." << std::endl;

		Level::TestLevel::enemy_dir = !(Level::TestLevel::enemy_dir);
	}

	if (SearchPlayer) 
	{
		//ESM::EnemyStateManager::GetInst()->ChangeState(new ESM::); Chase �߰� 
		//std::cout << "ChaseMode" << std::endl;
	}

}

void ESM::IDLE::Exit()
{
	//obj�� �� ������ �����ִ��� �׾��ִ���?
}

ESM::IDLE::IDLE(GameObject* _owner)
{
	enemy = _owner;
}
