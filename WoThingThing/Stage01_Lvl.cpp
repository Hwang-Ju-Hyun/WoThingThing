#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#include <iostream>
#include "header.h"

#include "GameStateManager.h"
#include "MainMenu_Lvl.h"
#include "Stage01_Lvl.h"

#include "GameObject.h"
#include "GoManager.h"

#include "BaseComponent.h"
#include "TransComponent.h"
#include "SpriteComponent.h"
#include "RigidBodyComponent.h"
#include "PlayerComponent.h"
#include "BulletComponent.h"
#include "CompManager.h"

#include "EventManager.h"
#include "ColliderManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "AudioResource.h"
#include "TextResource.h"

#include "Serializer.h"

#include "Utility.h"
#include "AiComponent.h"
#include "CameraManager.h"
#include "AEInput.h"
#include "AEUtil.h"
#include "AEMath.h"

#include"TargetAim_Sniper.h"

Level::Stage01_Lvl::Stage01_Lvl()
{
}

Level::Stage01_Lvl::~Stage01_Lvl()
{
}

void Level::Stage01_Lvl::Init()
{    
    //Object and Component Init
    Serializer::GetInst()->LoadLevel("temp.json");

    player = new GameObject("Player");
    GoManager::GetInst()->AddObject(player); //GetInst() == GetPtr()
    player->AddComponent("Transform", new TransComponent(player));
    player->AddComponent("Sprite", new SpriteComponent(player));    
    player->AddComponent("PlayerComp", new PlayerComponent(player));
    

    aimTrace = new GameObject("aimTrace");
    GoManager::GetInst()->AddObject(aimTrace);
    aimTrace->AddComponent("Transform", new TransComponent(aimTrace));
    aimTrace->AddComponent("Sprite", new SpriteComponent(aimTrace));   


    //EventManager에서 요거 지우쇼 
    RePosition* Platform_Player = new RePosition;
    EventManager::GetInst()->AddEntity("Collision",Platform_Player);

    //Enemy
    Enemy = new GameObject("Enemy");
    GoManager::GetInst()->AddObject(Enemy);

    Enemy->AddComponent("Transform", new TransComponent(Enemy));
    Enemy->AddComponent("Sprite", new SpriteComponent(Enemy));
    Enemy->AddComponent("RigidBody", new RigidBodyComponent(Enemy));
    Enemy->AddComponent("Ai", new AiComponent(Enemy));
    AiComponent* Enemy_state = (AiComponent*)Enemy->FindComponent("Ai");
    Enemy_state->SetTarget(player);//순서중요 trager부터 먼저 세팅 해준다 그리고 먼저 palyer부터 만들어준다.
    //Enemy_state->SetSniper_bullet(Enemy_bullet);
    Enemy_state->Setdir(true);//true가 오른쪽, false가 왼쪽
    Enemy_state->Setdir_time(2.0f);
    Enemy_state->SetState("IDLE","Melee");
    //Enemy_state->SetState("IDLE_Sniper", "Sniper");



    EnemySniper = new GameObject("EnemySniper");
    GoManager::GetInst()->AddObject(EnemySniper);
    
    EnemySniper->AddComponent("Transform", new TransComponent(EnemySniper));
    EnemySniper->AddComponent("Sprite", new SpriteComponent(EnemySniper));
    EnemySniper->AddComponent("RigidBody", new RigidBodyComponent(EnemySniper));
    EnemySniper->AddComponent("Ai", new AiComponent(EnemySniper));
    AiComponent* EnemySniper_state = (AiComponent*)EnemySniper->FindComponent("Ai");
    EnemySniper_state->SetTarget(player);//순서중요 trager부터 먼저 세팅 해준다 그리고 먼저 palyer부터 만들어준다.
    EnemySniper_state->Setdir(true);//true가 오른쪽, false가 왼쪽
    EnemySniper_state->Setdir_time(1.0f);
    //EnemySniper_state->SetState("IDLE", "Melee");
    EnemySniper_state->SetState("IDLE_Sniper", "Sniper");


    auto vecObj = GoManager::GetInst()->Allobj();
    for (int i = 0; i < vecObj.size(); i++)
    {
        if (vecObj[i]->GetName() == "Node")
        {
            vecObj[i]->AddComponent("Sprite", new SpriteComponent(vecObj[i]));
            SpriteComponent* node_spr = static_cast<SpriteComponent*>(vecObj[i]->FindComponent("Sprite"));
            node_spr->m_color.red = 155;
            node_spr->m_color.green = 250;
            node_spr->m_color.blue = 255;
        }
    }

    CameraManager::GetInst()->SetMouse(mouseAim);
    CameraManager::GetInst()->SetPlayer(player);
    CameraManager::GetInst()->SetAim(aimTrace);

    testEnemy = nullptr;
}

AEVec2 enemyDvec{ 1, 0 };
void Level::Stage01_Lvl::Update()
{
    //Component 
    TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
    SpriteComponent* player_spr = (SpriteComponent*)player->FindComponent("Sprite");
    RigidBodyComponent* player_rig = (RigidBodyComponent*)player->FindComponent("RigidBody");
    PlayerComponent* player_comp = (PlayerComponent*)player->FindComponent("PlayerComp");
    

    if(EnemySniper!= nullptr)
    {
        AiComponent* Enemy_meleeAi = (AiComponent*)Enemy->FindComponent("Ai");
        AiComponent* Enemy_SniperAi = (AiComponent*)EnemySniper->FindComponent("Ai");
    }



    //Right Click : Right attack

    if (AEInputCheckCurr(AEVK_R) == true)
    {
        //GSM::GameStateManager::GetInst()->ChangeLevel(new Level::Stage01_Lvl);
    }
    else if (AEInputCheckCurr(AEVK_E) == true)
    {
        GSM::GameStateManager::GetInst()->ChangeLevel(nullptr);
    }
    else if (AEInputCheckCurr(AEVK_T) == true)
    {
        GSM::GameStateManager::GetInst()->ChangeLevel(new Level::MainMenu_Lvl);
    }



    //Spawn Test Enemy
    if (testEnemy == nullptr || !testEnemy->GetActive())
    {
        if (AEInputCheckTriggered(AEVK_3) /* && testEnemy == nullptr*/) //collision이 일어나고 testEnemy를 nullptr로 만들어 주는데 왜 안되는거징
        {
            testEnemy = new GameObject("Test");
            GoManager::GetInst()->AddObject(testEnemy);
            testEnemy->AddComponent("Transform", new TransComponent(testEnemy));
            testEnemy->AddComponent("Sprite", new SpriteComponent(testEnemy));

            TransComponent* test_trs = static_cast<TransComponent*>(testEnemy->FindComponent("Transform"));
            test_trs->SetPos(0, -300);
            test_trs->SetScale({ 50, 50 });
        }
    }
    else if (testEnemy != nullptr || testEnemy->GetActive())
    {
        TransComponent* enemy_trs = (TransComponent*)testEnemy->FindComponent("Transform");
        AEVec2 bullet_pos = static_cast<TransComponent*>(enemy_trs)->GetPos();

        bullet_pos.x += -2.f * enemyDvec.x;
        static_cast<TransComponent*>(enemy_trs)->SetPos(bullet_pos);
    }

    int cnt = 0;
    for (auto obj : GoManager::GetInst()->Allobj())
    {
        if (obj->GetName() == "Platform")
        {
            if (ColliderManager::GetInst()->IsCollision(player, obj))
            {
                HandleCollision(player, obj);
            }
            if (ColliderManager::GetInst()->IsCollision(Enemy, obj))
            {
                HandleCollision(Enemy, obj);
                //AI COMP세팅을 해주고
                Enemy_Platform_Collision_Event* e_p_c_e = new Enemy_Platform_Collision_Event(obj, Enemy);
                EventManager::GetInst()->AddEvent(e_p_c_e);

            }

            if (ColliderManager::GetInst()->IsCollision(EnemySniper, obj))
            {
                HandleCollision(EnemySniper, obj);
            }
            int a = 0;
            for (auto findObj : GoManager::GetInst()->Allobj())
            {
                if (findObj->GetName() == "PlayerBullet" || findObj->GetName() == "EnemyBullet")
                {
                    if (ColliderManager::GetInst()->IsCollision(findObj, obj))
                    {
                        
                        std::cout <<"cnt : "<< ++a << std::endl;
                        BulletComponent* bullet_comp = (BulletComponent*)findObj->FindComponent("Bullet");
                        bullet_comp->DestroyBullet();
                    }
                }
            }

        }
        if (obj->GetName() == "EnemyBullet")
        {
           if (ColliderManager::GetInst()->IsCollision(player_comp->GetMelee(), obj))
           {
               BulletComponent* bullet_comp = (BulletComponent*)obj->FindComponent("Bullet");
               AEVec2 returnbullet = bullet_comp->GetBulletVec();
               float dt = AEFrameRateControllerGetFrameTime();
               if (AEInputCheckCurr(AEVK_LSHIFT)) 
               {
                   bullet_comp->SetBulletVec({ -1 * returnbullet.x * dt,-1 * returnbullet.y * dt });
               }
               else 
               {
                   bullet_comp->SetBulletVec({ -1 * returnbullet.x,-1 * returnbullet.y });
               }
           }
        }
        if (obj->GetName() == "EnemySniper")
        {
            if (ColliderManager::GetInst()->IsCollision(player_comp->GetMelee(), obj))
            {
                //Error!!
                //Where: in CompManager.cpp
                //What: Exception thrown: read access violation. && iter->was 0xFFFFFFFFFFFFFFD7.
                //Why: I think -> obj라는 게임오브젝트를 delete했는데 그 안에 있는 컴포넌트들도 삭제를 안해줘서 CompManager에서 업데이트를 할 때,
                //객체를 잃어버린 둥둥 떠다니는 컴포넌트들을 업데이트 하려 하니 생긴 오류같다.
                //24.09.02 --> RemoveComponent()에서 오류가 나는것을 발견 --> 어떤 Component를 지울지를 몰랐기 때문에 엉뚱한 Component를 지우고 있었어서 memory leak가 났음
                // RemoveComponent(BaseComponent * _comp) 로 수정하여 삭제할 Component의 주소값을 던져주어 그 Component들만 삭제하게 만듦

                //enemyDvec.x = -1;

                //DESTROY ENEMY
                //obj->SetActive(false); //Set false means DELETE AND REMOVE GO.
                //obj = nullptr; //I dont have enemy anymore
            }
            //Test: Collision Enemy with Player's Bullet
            for (auto findObj : GoManager::GetInst()->Allobj())
            {
                if (findObj->GetName() == "PlayerBullet" || findObj->GetName() == "EnemyBullet")
                {
                    if (ColliderManager::GetInst()->IsCollision(findObj, obj))
                    {
                        std::cout << "c" << std::endl;
                        BulletComponent* bullet_comp = (BulletComponent*)findObj->FindComponent("Bullet");
                        bullet_comp->DestroyBullet();

                        EnemySniper->SetActive(false);
                        EnemySniper = nullptr;
                        
                    }
                }
            }


        }
    }

    CameraManager::GetInst()->Update();
    GoManager::GetInst()->RemoveDeathObj();

    if (AEInputCheckPrev(AEVK_0))
    {
        GSM::GameStateManager::GetInst()->Exit();
    }
}

void Level::Stage01_Lvl::Exit()
{

    auto res = ResourceManager::GetInst()->GetReource();
    ResourceManager::GetInst()->RemoveAllRes();
    GoManager::GetInst()->RemoveAllObj();
}

//바닥이랑 obj Collision이면서 위치보정
void Level::Stage01_Lvl::HandleCollision(GameObject* obj1, GameObject* obj2)
{
    // Transform 및 RigidBody 컴포넌트 가져오기
    TransComponent* obj_trs1 = static_cast<TransComponent*>(obj1->FindComponent("Transform"));
    TransComponent* obj_trs2 = static_cast<TransComponent*>(obj2->FindComponent("Transform"));


    AEVec2 obj1_Pos = obj_trs1->GetPos();
    AEVec2 obj2_Pos = obj_trs2->GetPos();

    AEVec2 obj1_Scale = obj_trs1->GetScale();
    AEVec2 obj2_Scale = obj_trs2->GetScale();

    //RigidBodyComponent* obj_rb1 = static_cast<RigidBodyComponent*>(obj1->FindComponent("RigidBody"));
    if (obj1->GetName() == "Enemy" || obj1->GetName() == "EnemySniper")
    {
        RigidBodyComponent* obj_rb1 = static_cast<RigidBodyComponent*>(obj1->FindComponent("RigidBody"));
        //check 4 distance
        float distanceUpper = std::fabs(obj2_Pos.y + (obj2_Scale.y / 2.f) - (obj1_Pos.y - obj1_Scale.y / 2.f));
        float distanceDown = std::fabs(obj2_Pos.y - (obj2_Scale.y / 2.f) - (obj1_Pos.y + obj1_Scale.y / 2.f));
        float distanceRight = std::fabs(obj2_Pos.x + (obj2_Scale.x / 2.f) - (obj1_Pos.x - obj1_Scale.x / 2.f));
        float distanceLeft = std::fabs(obj2_Pos.x - (obj2_Scale.x / 2.f) - (obj1_Pos.x + obj1_Scale.x / 2.f));


        float distArr[4] = { distanceUpper,distanceRight,distanceLeft,distanceDown };
        float minDistance = distArr[0];
        int direct = 0;
        for (int i = 1; i < 4; i++)
        {
            if (minDistance > distArr[i])
            {
                minDistance = distArr[i];
                direct = i;
            }
        }
    

        switch (direct)
        {
        case 0://Upper
            obj_trs1->AddPos({ 0,minDistance });
            obj_rb1->SetJumpVelocityZero();
            //obj_rb1->SetJumpCntZero();
            break;
        case 1://Right
            obj_trs1->AddPos({ minDistance , 0 });
            break;
        case 2://Left		
            obj_trs1->AddPos({ -minDistance, 0 });
            break;
        case 3://Down
            obj_trs1->AddPos({ 0,-minDistance });
            obj_rb1->SetJumpVelocityZero();
            break;
        }
    }
    else if(obj1->GetName() == "Player")
    {
        PlayerComponent* obj_player = static_cast<PlayerComponent*>(obj1->FindComponent("PlayerComp"));

        //check 4 distance
        float distanceUpper = std::fabs(obj2_Pos.y + (obj2_Scale.y / 2.f) - (obj1_Pos.y - obj1_Scale.y / 2.f));
        float distanceDown = std::fabs(obj2_Pos.y - (obj2_Scale.y / 2.f) - (obj1_Pos.y + obj1_Scale.y / 2.f));
        float distanceRight = std::fabs(obj2_Pos.x + (obj2_Scale.x / 2.f) - (obj1_Pos.x - obj1_Scale.x / 2.f));
        float distanceLeft = std::fabs(obj2_Pos.x - (obj2_Scale.x / 2.f) - (obj1_Pos.x + obj1_Scale.x / 2.f));


        float distArr[4] = { distanceUpper,distanceRight,distanceLeft,distanceDown };
        float minDistance = distArr[0];
        int direct = 0;
        for (int i = 1; i < 4; i++)
        {
            if (minDistance > distArr[i])
            {
                minDistance = distArr[i];
                direct = i;
            }
        }     

        switch (direct)
        {
        case 0://Upper
            obj_trs1->AddPos({ 0,minDistance });
            obj_player->SetJumpVelocityZero();
            obj_player->SetJumpCntZero();
            break;
        case 1://Right
            obj_trs1->AddPos({ minDistance , 0 });
            break;
        case 2://Left		
            obj_trs1->AddPos({ -minDistance, 0 });
            break;
        case 3://Down
            obj_trs1->AddPos({ 0,-minDistance });
            obj_player->SetJumpVelocityZero();
            break;
        }
    }
   
}
