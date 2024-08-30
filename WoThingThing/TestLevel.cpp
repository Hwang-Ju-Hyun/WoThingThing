#include "TestLevel.h"
#include "header.h"
#include "MainMenu_Lvl.h"
#include "GameStateManager.h"
#include "GameObject.h"
#include "GoManager.h"
#include "BaseComponent.h"
#include "TransComponent.h"
#include "SpriteComponent.h"
#include "CompManager.h"
#include "ColliderManager.h"
#include "RigidBodyComponent.h"
#include "ResourceManager.h"
#include "AudioResource.h"
#include "TextResource.h"
#include "Utility.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "AEInput.h"
#include"AiComponent.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

Level::TestLevel::TestLevel()
{

}

Level::TestLevel::~TestLevel()
{	
	
}

void Level::TestLevel::Init()
{
	Test_player = new GameObject("Test_player");
	Enemy = new GameObject("Enemy");
	GoManager::GetInst()->AddObject(Test_player);
	GoManager::GetInst()->AddObject(Enemy);

	Test_player->AddComponent("Transform", new TransComponent(Test_player));
	Test_player->AddComponent("Sprite", new SpriteComponent(Test_player));

	Enemy->AddComponent("Transform", new TransComponent(Enemy));
	Enemy->AddComponent("Sprite", new SpriteComponent(Enemy));
	//�ֵ�
	Enemy->AddComponent("RigidBody", new RigidBodyComponent(Enemy));

	//Ai
	Enemy->AddComponent("Ai", new AiComponent(Enemy));
	AiComponent* Enemy_state = (AiComponent*)Enemy->FindComponent("Ai");
	Enemy_state->SetTarget(Test_player);//�����߿� trager���� ���� ���� ���ش� �׸��� ���� palyer���� ������ش�.
	Enemy_state->Setdir(true);//true�� ����, false�� ������
	Enemy_state->Setdir_time(1.0f);
	//�� ai���� Melee, Sniper, Boss 
	//�������� �������� Boss1,Boss2 �̷������� ����
	 
	
	//�������� ���ð��� "IDLE_Sniper", "Sniper"
	//SetSniper_bullet �߰� �ʼ�!! 
	//�Ѿ� ������Ʈ ������ �߰����ֱ�

	
	//���� ���ð��� "IDLE", "Melee"
	Enemy_state->SetState("IDLE", "Melee");
	//Enemy_state->SetTarget(Test_player);

	//������� �ٵ� �����
}

void Level::TestLevel::Update()
{
	TransComponent* player_trs = (TransComponent*)Test_player->FindComponent("Transform");
	SpriteComponent* player_spr = (SpriteComponent*)Test_player->FindComponent("Sprite");

	TransComponent* Enemy_trs = (TransComponent*)Enemy->FindComponent("Transform");
	SpriteComponent* Enemy_spr = (SpriteComponent*)Enemy->FindComponent("Sprite");

    for (auto player : GoManager::GetInst()->Allobj())
    {
        if (player->GetName() == "Test_player")
        {
            if (AEInputCheckCurr(AEVK_W))
            {
				player_trs->AddPos(0.f, 10.f);
            }
            if (AEInputCheckCurr(AEVK_S))
            {
				player_trs->AddPos(0.f, -10.f);
            }
			if (AEInputCheckCurr(AEVK_D))
			{
				player_trs->AddPos(10.f, 0.f);
			}
			if (AEInputCheckCurr(AEVK_A))
			{
				player_trs->AddPos(-10.f, 0.f);
			}

        }
    }
	//if (ColliderManager::GetInst()->PlayerSearch(Enemy,Test_player))
	//{
	//	//SetSearch(true);
	//}
	//else 
	//{
	//	//SetSearch(false);
	//}
}

void Level::TestLevel::Exit()
{
}
