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
#include "TimeManager.h"
#include "RigidBodyComponent.h"
#include "PlayerComponent.h"
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
#include "GameOver_Lvl.h"
#include "AEInput.h"
#include "AEUtil.h"
#include "AEMath.h"
#include "BulletComponent.h"
#include "Bullet.h"
#include "GameOver_Lvl.h"
#include "EnemyAnimationComponent.h"
#include"AnimationComponent.h"

Level::StageBoss_Lvl::StageBoss_Lvl()
{
}

Level::StageBoss_Lvl::~StageBoss_Lvl()
{
}

void Level::StageBoss_Lvl::Init()
{
    //Object and Component Init
    //      
    //stageBoss맵을 불러오자
    ResourceManager::GetInst()->Get("BossSturn", "Assets/BossSturn.png");//(1,2,2,0.1)
    ResourceManager::GetInst()->Get("BossRun", "Assets/BossRun.png");//(1,6,6,0.1)
    ResourceManager::GetInst()->Get("BossAtk", "Assets/BossAtk.png");//(1, 4, 4, 0.1);
    Serializer::GetInst()->LoadLevel("Assets/stageBoss.json");


    player = new GameObject("Player");
    GoManager::GetInst()->AddObject(player); //GetInst() == GetPtr()
    player->AddComponent("Transform", new TransComponent(player));
    //player->AddComponent("Sprite", new SpriteComponent(player));
    player->AddComponent("PlayerComp", new PlayerComponent(player));
    player->AddComponent("Animation", new AnimationComponent(player));
    TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
    player_trs->SetScale({ 80, 80 });


    aimTrace = new GameObject("aimTrace");
    GoManager::GetInst()->AddObject(aimTrace);
    aimTrace->AddComponent("Transform", new TransComponent(aimTrace));
    aimTrace->AddComponent("Sprite", new SpriteComponent(aimTrace));



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
    //Enemy_TEST->AddComponent("Sprite", new SpriteComponent(Enemy_TEST));
    Enemy_TEST->AddComponent("RigidBody", new RigidBodyComponent(Enemy_TEST));
    Enemy_TEST->AddComponent("PathFindMove", new PathFindMoveComponent(Enemy_TEST));
    Enemy_TEST->AddComponent("EnemyAnimation", new EnemyAnimationComponent(Enemy_TEST));
    EnemyAnimationComponent* Enemy_ani = (EnemyAnimationComponent*)Enemy_TEST->FindComponent("EnemyAnimation");
    Enemy_ani->ChangeAnimation("BossRun", 1, 6, 6, 0.1);
    //TEST===========


    CameraManager::GetInst()->SetMouse(mouseAim);
    CameraManager::GetInst()->SetPlayer(player);
    CameraManager::GetInst()->SetAim(aimTrace);

    gameOver = false;

    NaveMeshManager::GetInst()->SetPlayer(player);
    NaveMeshManager::GetInst()->CreateLinkTable();

    enemyDir = true;
}

void Level::StageBoss_Lvl::Update()
{
    //Component Pointer    

    //Component 
    TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
    SpriteComponent* player_spr = (SpriteComponent*)player->FindComponent("Sprite");
    RigidBodyComponent* player_rig = (RigidBodyComponent*)player->FindComponent("RigidBody");
    PlayerComponent* player_comp = (PlayerComponent*)player->FindComponent("PlayerComp");

    TransComponent* EnemyTest_trs = (TransComponent*)Enemy_TEST->FindComponent("Transform");
    SpriteComponent* EnemyTest_spr = (SpriteComponent*)Enemy_TEST->FindComponent("Sprite");
    RigidBodyComponent* EnemyTest_rig = (RigidBodyComponent*)Enemy_TEST->FindComponent("RigidBody");
    EnemyAnimationComponent* Enemy_ani = (EnemyAnimationComponent*)Enemy_TEST->FindComponent("EnemyAnimation");


   
  
    playerPos = player_trs->GetPos();
    enemyTestPos = EnemyTest_trs->GetPos();
    chaseVec.x = playerPos.x - enemyTestPos.x;
    chaseVec.y = playerPos.y - enemyTestPos.y;

    if (!(ColliderManager::GetInst()->isFacingtheSameDirection(chaseVec, enemyDir)))
    {
        //Chase_outTime = 0.0f;
        enemyDir = !(enemyDir);
        Enemy_ani->SetEnemyDir(!enemyDir);
    }

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
    //float nodeBotX = (float)mouseX - 35.f;
    //float nodeBotY = (float)mouseY - 35.f;
    //float nodeTopX = (float)mouseX + 35.f;
    //float nodeTopY = (float)mouseY + 35.f;

    float nodeBotX = (float)mouseX - 25.f;
    float nodeBotY = (float)mouseY - 35.f;
    float nodeTopX = (float)mouseX + 25.f;
    float nodeTopY = (float)mouseY + 35.f;

    static int nodeId = 0;
    //NodeEditor	
    //if (AEInputCheckTriggered(AEVK_RBUTTON))
    //{
    //    ////Ask manager for the node. It will handle the unique IDs	
    //    // 		
    //    TransComponent::Node node_left;

    //    node_left.node_id = nodeId++;
    //    node_left.node_pos = { (float)mouseX,(float)mouseY };

    //    NaveMeshManager::GetInst()->AddNode(node_left);
    //}

    auto a = NaveMeshManager::GetInst()->GetallNode();
    a.size();

    //for (auto it : NaveMeshManager::GetInst()->GetallNode())
    //    NaveMeshManager::GetInst()->DrawNode(it.node_pos.x - 25, it.node_pos.y - 35, it.node_pos.x + 25, it.node_pos.y + 35, 1.0f, 1.0f, 0);


    //Camera Update
    CameraManager::GetInst()->Update();

    //======================WARNING=============================
    //=======NEVER TOUCH DOWN CODE EXCEPT HWNAG JUHYUN==========    
    TransComponent* EnemyTEST_tsr = static_cast<TransComponent*>(Enemy_TEST->FindComponent("Transform"));
    RigidBodyComponent* EnemyTEST_rg = static_cast<RigidBodyComponent*>(Enemy_TEST->FindComponent("RigidBody"));
    PathFindMoveComponent* EnemyTEST_pf = static_cast<PathFindMoveComponent*>(Enemy_TEST->FindComponent("PathFindMove"));

    NaveMeshManager::GetInst()->SetMinCost(10000.f);
    //플레이어한테서 가장 가까운 노드를 찾는다
    int player_node = NaveMeshManager::GetInst()->FindObjectNode(player);

    //보스의 현재위치의 가장 가까운 노드를 찾는다
    int EnemyTest_node = NaveMeshManager::GetInst()->FindObjectNode(Enemy_TEST);

    auto node_link = NaveMeshManager::GetInst()->GetvecLink();
    auto node = NaveMeshManager::GetInst()->GetallNode();

    if (ColliderManager::GetInst()->IsCollision(Enemy_TEST, node[EnemyTest_node]))
    {
        NaveMeshManager::GetInst()->FindShortestPath(EnemyTest_node, player_node, 0);
    }
    else
    {
        double deltatime = AEFrameRateControllerGetFrameTime();
        AccTime += deltatime;
        if (AccTime > 1.)
        {           
            NaveMeshManager::GetInst()->FindShortestPath(EnemyTest_node, player_node, 0);
            AccTime = 0.;
        }
    }

    auto minCost = NaveMeshManager::GetInst()->GetMinCost();
    auto FoundedPath = NaveMeshManager::GetInst()->GetPath();    
    

    int PathIndex = EnemyTEST_pf->GetPathToPathIndex();
   
    //std::cout << player_trs->GetPos().x << "," << player_trs->GetPos().y << std::endl;

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
            //문제될시 player삭제 NaveMesh매니저 Move전부 바꿔주기
            costLink->Move(Enemy_TEST, node[nodeID1], FoundedPath[PathIndex], 1, node[nodeID2], player);
        }

    }   
    //=======NEVER TOUCH UPPER CODE EXCEPT HWNAG JUHYUN==========
    //======================WARNING=============================



    //std::cout << std::endl;
    //if (AEInputCheckTriggered(AEVK_Q))
    //{
    //    Serializer::GetInst()->SaveLevel("Assets/stageBoss.json");
    //}
    //if (AEInputCheckTriggered(AEVK_F2))
    //    GSM::GameStateManager::GetInst()->ChangeLevel(new MainMenu_Lvl);
    //if (AEInputCheckTriggered(AEVK_F1))
    //    GSM::GameStateManager::GetInst()->ChangeLevel(new StageBoss_Lvl);
}

void Level::StageBoss_Lvl::HandleCollision(GameObject* obj1, GameObject* obj2)
{
    // Transform 및 RigidBody 컴포넌트 가져오기
    TransComponent* obj_trs1 = static_cast<TransComponent*>(obj1->FindComponent("Transform"));
    TransComponent* obj_trs2 = static_cast<TransComponent*>(obj2->FindComponent("Transform"));


    AEVec2 obj1_Pos = obj_trs1->GetPos();
    AEVec2 obj2_Pos = obj_trs2->GetPos();

    AEVec2 obj1_Scale = obj_trs1->GetScale();
    AEVec2 obj2_Scale = obj_trs2->GetScale();

    if (obj1->GetName() == "Player" )
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
    else if (obj1->GetName() == "Enemy_TEST")
    {
        RigidBodyComponent* obj_enemy = static_cast<RigidBodyComponent*>(obj1->FindComponent("RigidBody"));

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
            obj_enemy->SetJumpVelocityZero();            
            break;
        case 1://Right
            obj_trs1->AddPos({ minDistance , 0 });
            break;
        case 2://Left		
            obj_trs1->AddPos({ -minDistance, 0 });
            break;
        case 3://Down
            obj_trs1->AddPos({ 0,-minDistance });
            obj_enemy->SetJumpVelocityZero();
            break;
        }
    }

}

void Level::StageBoss_Lvl::Collision()
{
    PlayerComponent* player_comp = (PlayerComponent*)player->FindComponent("PlayerComp");
    EnemyAnimationComponent* Enemy_ani = (EnemyAnimationComponent*)Enemy_TEST->FindComponent("EnemyAnimation");
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
            if (ColliderManager::GetInst()->IsCollision(Enemy_TEST, obj))
            {
                HandleCollision(Enemy_TEST, obj);
                //AI COMP세팅을 해주고
               //Enemy_Platform_Collision_Event* e_p_c_e = new Enemy_Platform_Collision_Event(obj, Enemy);
               //EventManager::GetInst()->AddEvent(e_p_c_e);
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
                gameOver = true;
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
    //여기가 보스랑 플레이어가 부딫히는 부분

    if (ColliderManager::GetInst()->PlayerSearch(Enemy_TEST, player, enemyDir, 0.5, 1, 1))
    {
        Enemy_ani->ChangeAnimation("BossAtk", 1, 4, 4, 0.1);
        m_fDt = (f32)AEFrameRateControllerGetFrameTime();
        melee_DelayAtk += m_fDt;
        //std::cout << melee_DelayAtk << std::endl;
        if (melee_DelayAtk > 0.5f)//0.05초주기
        {
            player_comp->TakeDamge();
            //std::cout << "Attack Player" << std::endl;
        }
    }
    else 
    {
        m_fDt = 0.0f;
        melee_DelayAtk = 0.f;
    }
}



void Level::StageBoss_Lvl::Exit()
{
    auto res = ResourceManager::GetInst()->GetReource();
    ResourceManager::GetInst()->RemoveAllRes();
    GoManager::GetInst()->RemoveAllObj();
    //Serializer::GetInst()->SaveLevel("Assets/stageBoss.json");
}
