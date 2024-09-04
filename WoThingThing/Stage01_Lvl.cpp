#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#include <iostream>
#include "header.h"

#include "GameStateManager.h"
#include "MainMenu_Lvl.h"
#include "Stage01_Lvl.h"
#include "GameOver_Lvl.h"

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
#include "NaveMeshManager.h"
#include "Utility.h"
#include "AiComponent.h"
#include "CameraManager.h"
#include "PathFindMoveComponent.h"
#include "StageBoss_Lvl.h"
#include "AEInput.h"
#include "AEUtil.h"
#include "AEMath.h"

#include "Bullet.h"
#include"TargetAim_Sniper.h"

AEVec2 enemyDvec{ 1, 0 };

Level::Stage01_Lvl::Stage01_Lvl()
{
}

Level::Stage01_Lvl::~Stage01_Lvl()
{
}

void Level::Stage01_Lvl::Init()
{    
    //Object and Component Init
    
    //인제 temp는 보스 맵이 된거여
    //Serializer::GetInst()->LoadLevel("temp.json");

    //stage01맵을 불러오자
    Serializer::GetInst()->LoadLevel("Assets/stage01.json");


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
    TransComponent* Enemy_trs = (TransComponent*)Enemy->FindComponent("Transform");
    AiComponent* Enemy_state = (AiComponent*)Enemy->FindComponent("Ai");
    Enemy_state->SetTarget(player);//순서중요 trager부터 먼저 세팅 해준다 그리고 먼저 palyer부터 만들어준다.
    Enemy_state->Setdir(true);//true가 오른쪽, false가 왼쪽
    Enemy_state->Setdir_time(2.0f);
    Enemy_state->SetFirstPlace(Enemy_trs->GetPos());
    Enemy_state->SetState("IDLE", "Melee");



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

    //TEST==========
    Enemy_TEST = new GameObject("Enemy_TEST");
    GoManager::GetInst()->AddObject(Enemy_TEST);

    Enemy_TEST->AddComponent("Transform", new TransComponent(Enemy_TEST));
    Enemy_TEST->AddComponent("Sprite", new SpriteComponent(Enemy_TEST));
    Enemy_TEST->AddComponent("RigidBody", new RigidBodyComponent(Enemy_TEST));
    Enemy_TEST->AddComponent("PathFindMove", new PathFindMoveComponent(Enemy_TEST));
    //TEST===========

    
    CameraManager::GetInst()->SetMouse(mouseAim);
    CameraManager::GetInst()->SetPlayer(player);
    CameraManager::GetInst()->SetAim(aimTrace);

    gameOver = false;

    NaveMeshManager::GetInst()->SetPlayer(player);
    NaveMeshManager::GetInst()->CreateLinkTable();

}

void Level::Stage01_Lvl::Update()
{
    //Component Pointer

    //Component 
    TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
    SpriteComponent* player_spr = (SpriteComponent*)player->FindComponent("Sprite");
    RigidBodyComponent* player_rig = (RigidBodyComponent*)player->FindComponent("RigidBody");
    PlayerComponent* player_comp = (PlayerComponent*)player->FindComponent("PlayerComp");

    //std::cout << "(" << player_trs->GetPos().x << "," << player_trs->GetPos().y << ")" << std::endl;
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

    Collision();

    CameraManager::GetInst()->Update();
    GoManager::GetInst()->RemoveDeathObj();

    if (AEInputCheckPrev(AEVK_0))
    {
        GSM::GameStateManager::GetInst()->Exit();
    }

    //Test line
    if (AEInputCheckTriggered(AEVK_4))
        CreateSupplement({ 0, -300 });
    
    //Player->GetHeath() == 0
    //    gameOver = true

    if (!(player_comp->IsAlive()))
    {
        GSM::GameStateManager* gsm = GSM::GameStateManager::GetInst();
        gsm->ChangeLevel(new Level::GameOver_Lvl);

        return;
    }

    s32 mouseX, mouseY;
    AEInputGetCursorPosition(&mouseX, &mouseY);

    //convert to world
    //Screen -> NDC
    mouseX -= 800;
    mouseY -= 450;
    mouseY *= -1;
    AEVec2 camera = CameraManager::GetInst()->GetLookAt();
    //NDC -> Camera
    mouseX += camera.x;
    mouseY += camera.y;
    float nodeBotX = (float)mouseX - 35.f;
    float nodeBotY = (float)mouseY - 35.f;
    float nodeTopX = (float)mouseX + 35.f;
    float nodeTopY = (float)mouseY + 35.f;

    static int nodeId = 0;
    //NodeEditor	
    if (AEInputCheckTriggered(AEVK_RBUTTON))
    {
        ////Ask manager for the node. It will handle the unique IDs	
        // 		
        TransComponent::Node node_left;

        node_left.node_id = nodeId++;
        node_left.node_pos = { (float)mouseX,(float)mouseY };

        NaveMeshManager::GetInst()->AddNode(node_left);
    }


    for (auto it : NaveMeshManager::GetInst()->GetallNode())
        NaveMeshManager::GetInst()->DrawNode(it.node_pos.x - 35, it.node_pos.y - 35, it.node_pos.x + 35, it.node_pos.y + 35, 1.0f, 1.0f, 0);


    //Camera Update
    CameraManager::GetInst()->Update();

    //======================WARNING=============================
    //=======NEVER TOUCH DOWN CODE EXCEPT HWNAG JUHYUN==========    
    TransComponent* EnemyTEST_tsr = static_cast<TransComponent*>(Enemy_TEST->FindComponent("Transform"));
    RigidBodyComponent* EnemyTEST_rg = static_cast<RigidBodyComponent*>(Enemy_TEST->FindComponent("RigidBody"));
    PathFindMoveComponent* EnemyTEST_pf = static_cast<PathFindMoveComponent*>(Enemy_TEST->FindComponent("PathFindMove"));
    //플레이어한테서 가장 가까운 노드를 찾는다
    NaveMeshManager::GetInst()->SetMinCost(10000.f);
    int player_node = NaveMeshManager::GetInst()->FindObjectNode(player);

    //보스의 현재위치의 가장 가까운 노드를 찾는다
    int EnemyTest_node = NaveMeshManager::GetInst()->FindObjectNode(Enemy_TEST);
    auto node_link = NaveMeshManager::GetInst()->GetvecLink();
    auto node = NaveMeshManager::GetInst()->GetallNode();
    if (ColliderManager::GetInst()->IsCollision(Enemy_TEST, node[EnemyTest_node]))
    {
        NaveMeshManager::GetInst()->FindShortestPath(EnemyTest_node, player_node, 0);
    }

    auto minCost = NaveMeshManager::GetInst()->GetMinCost();
    auto FoundedPath = NaveMeshManager::GetInst()->GetPath();

    int PathIndex = EnemyTEST_pf->GetPathToPathIndex();

    std::cout << "Player Located Node : " << player_node << std::endl;
    std::cout << "Enemy Located Node : " << EnemyTest_node << std::endl;
    std::cout << "Minimum cost: " << minCost << std::endl;
    std::cout << "Founded Path: ";
    for (auto node : FoundedPath)
        std::cout << node << " ";
    std::cout << std::endl;


    if (FoundedPath.size() > 1)
    {
        //costLink는 점프가 될수도 있고  walk가 될 수도 있음                                          
        int nodeID1 = FoundedPath[PathIndex];
        int nodeID2;
        if (FoundedPath.size() <= PathIndex + 1)
            nodeID2 = nodeID1;
        else
            nodeID2 = FoundedPath[PathIndex + 1];
        int idx = 0;
        while (nodeID2 != node_link[nodeID1][idx].first)
        {
            idx++;
        }
        auto costLink = node_link[FoundedPath[PathIndex]][idx].second;

        //해당 보스위치가 다음 서브노드의 도착지점에 도착하였다면!
        //밑에 주석 막 지우지마 쓰일 수도 있음
        /*if (EnemyTEST_pf->IsArrivedTargetNode(Enemy_TEST, node[PathIndex + 1].node_pos))
        {
            EnemyTEST_pf->PlusPathToPathIndex();
      ddd  }*/
      /*if (EnemyTEST_pf->IsArrivedTargetNode(Enemy_TEST, node[idx].node_pos))
      {
          EnemyTEST_pf->PlusPathToPathIndex();
      }*/
        if (EnemyTEST_pf->IsArrivedTargetNode(Enemy_TEST, node[nodeID2]))
        {
            EnemyTEST_pf->PlusPathToPathIndex();

        }
        else
        {
            costLink->Move(Enemy_TEST, node[nodeID1], FoundedPath[PathIndex], 1, node[nodeID2]);
        }

    }
    //=======NEVER TOUCH UPPER CODE EXCEPT HWNAG JUHYUN==========
    //======================WARNING=============================

    std::cout << std::endl;
    if (AEInputCheckTriggered(AEVK_ESCAPE))
        GSM::GameStateManager::GetInst()->ChangeLevel(new MainMenu_Lvl);
    if (AEInputCheckTriggered(AEVK_F1))
        GSM::GameStateManager::GetInst()->ChangeLevel(new StageBoss_Lvl);
}


void Level::Stage01_Lvl::Exit()
{
    auto res = ResourceManager::GetInst()->GetReource();
    ResourceManager::GetInst()->RemoveAllRes();    
    EventManager::GetInst()->RemoveAllEvent();
    GoManager::GetInst()->RemoveAllObj();
}

void Level::Stage01_Lvl::Collision()
{
    PlayerComponent* player_comp = (PlayerComponent*)player->FindComponent("PlayerComp");
    //Collision
    int cnt = 0;
    for (auto obj : GoManager::GetInst()->Allobj())
    {
        //Platform
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
                bullet_comp->EnemyShoot = false;
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


           //Player Death
           
           if (ColliderManager::GetInst()->IsCollision(player, obj))
           {               
               //gameOver = true;
               player_comp->TakeDamge();
           }
        }
        //Sniper죽는판정
        if (obj->GetName() == "EnemySniper")
        {
            //Test: Collision Enemy with Player's Bullet
            for (auto findObj : GoManager::GetInst()->Allobj())
            {
                if (findObj->GetName() == "PlayerBullet" || findObj->GetName() == "EnemyBullet")
                {
                    if (ColliderManager::GetInst()->IsCollision(findObj, obj))
                    {
                        //std::cout << "c" << std::endl;
                        BulletComponent* bullet_comp = (BulletComponent*)findObj->FindComponent("Bullet");
                        if (!bullet_comp->EnemyShoot)
                        {
                            EnemySniper->SetActive(false);
                            EnemySniper = nullptr;
                        }
                        bullet_comp->DestroyBullet();
                    }
                }
            }
            if (ColliderManager::GetInst()->IsCollision(player_comp->GetMelee(), obj))
            {
                EnemySniper->SetActive(false);
                EnemySniper = nullptr;
            }

        }

        if (obj->GetName() == "Enemy") 
        {
            //총알부분
            for (auto findObj : GoManager::GetInst()->Allobj())
            {
                if (findObj->GetName() == "PlayerBullet" || findObj->GetName() == "EnemyBullet") 
                {
                    if (ColliderManager::GetInst()->IsCollision(findObj, obj)) 
                    {
                        //std::cout << "c" << std::endl;
                        BulletComponent* bullet_comp = (BulletComponent*)findObj->FindComponent("Bullet");
                        if (!bullet_comp->EnemyShoot)
                        {
                            Enemy->SetActive(false);
                            Enemy = nullptr;
                            bullet_comp->DestroyBullet();
                        }
                        //bullet_comp->DestroyBullet();
                    }
                }
            }
            //근접
            if (ColliderManager::GetInst()->IsCollision(player_comp->GetMelee(), obj)) 
            {
                Enemy->SetActive(false);
                Enemy = nullptr;
            }
        }


        if (obj->GetName() == "BulletSupplement")
        {
            if (ColliderManager::GetInst()->IsCollision(player, obj))
            {
                AddBullet();
                //std::cout << "Add Bullet!" << std::endl;

                obj->SetActive(false);
            }

        }
    }
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
    if (obj1->GetName() == "Enemy" || obj1->GetName() == "EnemySniper" || obj1->GetName() == "Enemy_TEST")
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