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
#include "AEInput.h"
#include "AEUtil.h"
#include "AEMath.h"
#include "BulletComponent.h"
#include <random>
#include "Bullet.h"
#include "Congratulation.h"
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
    //stageBoss���� �ҷ�����
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

    std::cout << Enemy_TEST->GetHP() << std::endl;
    
    if (Enemy_TEST->GetHP() <= 0)
    {
        GSM::GameStateManager* gsm = GSM::GameStateManager::GetInst();
        gsm->ChangeLevel(new Level::Congratulation);
        return;
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
   
    
    //Camera Update
    CameraManager::GetInst()->Update();

    //======================WARNING=============================
    //=======NEVER TOUCH DOWN CODE EXCEPT HWNAG JUHYUN==========        
    RigidBodyComponent* EnemyTEST_rg = static_cast<RigidBodyComponent*>(Enemy_TEST->FindComponent("RigidBody"));
    PathFindMoveComponent* EnemyTEST_pf = static_cast<PathFindMoveComponent*>(Enemy_TEST->FindComponent("PathFindMove"));

    NaveMeshManager::GetInst()->SetMinCost(10000.f);
    //�÷��̾����׼� ���� ����� ��带 ã�´�
    int player_node = NaveMeshManager::GetInst()->FindObjectNode(player);

    //������ ������ġ�� ���� ����� ��带 ã�´�
    int EnemyTest_node = NaveMeshManager::GetInst()->FindObjectNode(Enemy_TEST);

    auto node_link = NaveMeshManager::GetInst()->GetvecLink();
    auto node = NaveMeshManager::GetInst()->GetallNode();

    if (ColliderManager::GetInst()->IsCollision(Enemy_TEST, node[EnemyTest_node]))
    {
        NaveMeshManager::GetInst()->FindShortestPath(EnemyTest_node, player_node, 0);
    }
    else
    {                          
        float deltatime = float(AEFrameRateControllerGetFrameTime());
        AccTime += deltatime;
        if (AccTime >= 1.f)
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
        //costLink�� ������ �ɼ��� �ְ�  walk�� �� ���� ����                                          
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

        //�ش� ������ġ�� ���� �������� ���������� �����Ͽ��ٸ�!
        if (EnemyTEST_pf->IsArrivedTargetNode(Enemy_TEST, node[nodeID2]))
        {
            EnemyTEST_pf->PlusPathToPathIndex();

        }
        else
        {
            //�����ɽ� player���� NaveMesh�Ŵ��� Move���� �ٲ��ֱ�
            costLink->Move(Enemy_TEST, node[nodeID1], FoundedPath[PathIndex], 1, node[nodeID2], player);
        }

    }   
    //=======NEVER TOUCH UPPER CODE EXCEPT HWNAG JUHYUN==========
    //======================WARNING=============================


    if (Enemy_TEST->GetHP() >= 10&& Enemy_TEST->GetHP()<15)
    {                        
        AEVec2 dVec = { -(EnemyTest_trs->GetPos().x - player_trs->GetPos().x), -(EnemyTest_trs->GetPos().y - player_trs->GetPos().y) }; //direction Vector
        AEVec2 nor_dVec{ 0,0 }; //Normailize direction Vector
        AEVec2Normalize(&nor_dVec, &dVec);
        float deltaTime = (f32)AEFrameRateControllerGetFrameTime();
        AttackDelayTime += deltaTime;
        if (AttackDelayTime > 1.5f)
        {
            auto res_BossShotgun = ResourceManager::GetInst()->Get("sfx_BossShotgun", "Assets/BossShotgun.mp3");
            AudioResource* bgm_res = static_cast<AudioResource*>(res_BossShotgun);
            bgm_res->SetSFXorMusic(Sound::SFX);
            auto bgm_audio = bgm_res->GetAudio();
            auto bgm_audioGroup = bgm_res->GetAudioGroup();
            AEAudioPlay(bgm_audio, bgm_audioGroup, 1.f, 1.f, 0);

            CreateBullet(EnemyTest_trs->GetPos(), nor_dVec, "BossBullet", true);
            nor_dVec.y += 0.05f;
            CreateBullet(EnemyTest_trs->GetPos(), nor_dVec, "BossBullet", true);
            nor_dVec.y += 0.05f;
            CreateBullet(EnemyTest_trs->GetPos(), nor_dVec, "BossBullet", true);
            nor_dVec.y -= 0.15f;
            CreateBullet(EnemyTest_trs->GetPos(), nor_dVec, "BossBullet", true);
            nor_dVec.y -= 0.30f;
            AttackDelayTime = 0.f;
        }
    }
    else if (Enemy_TEST->GetHP() < 10)
    {
        AEVec2 dVec = { -(EnemyTest_trs->GetPos().x - player_trs->GetPos().x), -(EnemyTest_trs->GetPos().y - player_trs->GetPos().y) }; //direction Vector
        AEVec2 nor_dVec{ 0,0 }; //Normailize direction Vector
        AEVec2Normalize(&nor_dVec, &dVec);
        float deltaTime = (f32)AEFrameRateControllerGetFrameTime();
        AttackDelayTime += deltaTime;
        if (AttackDelayTime > 0.5f)
        {
            CreateBullet(EnemyTest_trs->GetPos(), nor_dVec, "BossBullet", true);            
            AttackDelayTime = 0.f;
        }
    }
}

void Level::StageBoss_Lvl::HandleCollision(GameObject* obj1, GameObject* obj2)
{
    // Transform �� RigidBody ������Ʈ ��������
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
            }
            //�Ѿ� �÷��� �浹ó��
            for (auto findObj : GoManager::GetInst()->Allobj())
            {
                if (findObj->GetName() == "PlayerBullet" || findObj->GetName() == "BossBullet")
                {
                    if (ColliderManager::GetInst()->IsCollision(findObj, obj))
                    {
                        BulletComponent* bullet_comp = (BulletComponent*)findObj->FindComponent("Bullet");
                        bullet_comp->DestroyBullet();
                    }
                }
            }
        }
        //�е�
        if (obj->GetName() == "BossBullet")
        {
            if (ColliderManager::GetInst()->IsCollision(player_comp->GetMelee(), obj))
            {
                auto res_padding = ResourceManager::GetInst()->Get("sfx_paddingBoss", "Assets/padding2.wav");
                AudioResource* bgm_res = static_cast<AudioResource*>(res_padding);
                bgm_res->SetSFXorMusic(Sound::SFX);
                auto bgm_audio = bgm_res->GetAudio();
                auto bgm_audioGroup = bgm_res->GetAudioGroup();
                AEAudioPlay(bgm_audio, bgm_audioGroup, 1.f, 1.f, 0);

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
                auto resDead = ResourceManager::GetInst()->Get("sfx_PlayerDeadToBoss", "Assets/Dead1.wav");
                AudioResource* bgm_resDead = static_cast<AudioResource*>(resDead);
                bgm_resDead->SetSFXorMusic(Sound::SFX);
                auto bgm_audioDead = bgm_resDead->GetAudio();
                auto bgm_audioGroupDead = bgm_resDead->GetAudioGroup();
                AEAudioPlay(bgm_audioDead, bgm_audioGroupDead, 1.f, 1.f, 0);
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
    //���Ⱑ ������ �÷��̾ �΋H���� �κ�
    if (ColliderManager::GetInst()->GetPlayerSearchOnOff() == true)
    {
        if (ColliderManager::GetInst()->PlayerSearch(Enemy_TEST, player, enemyDir, 0.5, 1, 1))
        {
            Enemy_ani->ChangeAnimation("BossAtk", 1, 4, 4, 0.1);
            m_fDt = (f32)AEFrameRateControllerGetFrameTime();
            melee_DelayAtk += m_fDt;
            //std::cout << melee_DelayAtk << std::endl;
            if (melee_DelayAtk > 0.5f)//0.05���ֱ�
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
}



void Level::StageBoss_Lvl::Exit()
{
    auto res = ResourceManager::GetInst()->GetReource();
    ResourceManager::GetInst()->RemoveAllRes();
    GoManager::GetInst()->RemoveAllObj();
    //Serializer::GetInst()->SaveLevel("Assets/stageBoss.json");
}
