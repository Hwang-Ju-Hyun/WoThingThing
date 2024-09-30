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
#include "ImageResource.h"

bool Level::StageBoss_Lvl::Stage2 = true;

Level::StageBoss_Lvl::StageBoss_Lvl()
{
}

Level::StageBoss_Lvl::~StageBoss_Lvl()
{
}

void Level::StageBoss_Lvl::Init()
{
    //Background Image
    background = new GameObject("Background");
    GoManager::GetInst()->AddObject(background);
    background->AddComponent("Transform", new TransComponent(background));
    background->AddComponent("Sprite", new SpriteComponent(background));
    ResourceManager::GetInst()->Get("BackgroundImg", "Assets/BackgroundNightImage.png");
    SpriteComponent* bg_spr = (SpriteComponent*)background->FindComponent("Sprite");
    ImageResource* bgResource = (ImageResource*)ResourceManager::GetInst()->FindRes("BackgroundImg");
    bg_spr->SetTexture(bgResource->GetImage());
    bg_spr->SetAlpha(0.5f);

    Stage2 = true;
    //Object and Component Init
    //      
    //stageBoss맵을 불러오자
    ResourceManager::GetInst()->Get("BossSturn", "Assets/BossSturn.png");//(1,2,2,0.1)
    ResourceManager::GetInst()->Get("BossRun", "Assets/BossRun.png");//(1,6,6,0.1)
    ResourceManager::GetInst()->Get("BossAtk", "Assets/BossAtk.png");//(1, 4, 4, 0.1);
    ResourceManager::GetInst()->Get("KnockBack", "Assets/KnockBack.png");
    ResourceManager::GetInst()->Get("Boss_drone_Atk", "Assets/Boss_drone_Atk.png");//(1,12,12,0.1)

    Serializer::GetInst()->LoadLevel("Assets/stageBoss.json");


    player = new GameObject("Player");
    GoManager::GetInst()->AddObject(player); //GetInst() == GetPtr()
    player->AddComponent("Transform", new TransComponent(player));
    //player->AddComponent("Sprite", new SpriteComponent(player));
    player->AddComponent("PlayerComp", new PlayerComponent(player));
    //player->AddComponent("Animation", new AnimationComponent(player));
    TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
    player_trs->SetScale({ 80, 80 });

    PlayerComponent* player_comp = (PlayerComponent*)player->FindComponent("PlayerComp");
    player_comp->SetObtain();


    playerAnim = new GameObject("PlayerAnim");
    GoManager::GetInst()->AddObject(playerAnim); //GetInst() == GetPtr()
    playerAnim->AddComponent("Transform", new TransComponent(playerAnim));
    playerAnim->AddComponent("Animation", new AnimationComponent(playerAnim));

    aimTrace = new GameObject("aimTrace");
    GoManager::GetInst()->AddObject(aimTrace);
    aimTrace->AddComponent("Transform", new TransComponent(aimTrace));
    aimTrace->AddComponent("Sprite", new SpriteComponent(aimTrace));



    auto vecObj = GoManager::GetInst()->Allobj();
    for (int i = 0; i < vecObj.size(); i++)
    {
        if (vecObj[i]->GetName() == "Node")
        {
            //vecObj[i]->AddComponent("Sprite", new SpriteComponent(vecObj[i]));
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
    Enemy_ani->ChangeAnimation("BossRun", 1, 6, 6, 0.1f);

    //
    //Enemy_TEST->SetHP(20);
    //
    //TEST===========


    //보스 드론부분
    Boss_drone = new GameObject("Boss_drone");
    GoManager::GetInst()->AddObject(Boss_drone);
    Boss_drone->AddComponent("Transform", new TransComponent(Boss_drone));
    //Boss_drone->AddComponent("Sprite", new SpriteComponent(Boss_drone));
    Boss_drone->AddComponent("EnemyAnimation", new EnemyAnimationComponent(Boss_drone));
    EnemyAnimationComponent* Boss_drone_ani = (EnemyAnimationComponent*)Boss_drone->FindComponent("EnemyAnimation");
    Boss_drone_ani->ChangeAnimation("Boss_drone_Atk", 1, 12, 12, 0.4f);
    Boss_drone_ani->SetEnemyDir(true);

    CameraManager::GetInst()->SetMouse(mouseAim);
    CameraManager::GetInst()->SetPlayer(player);
    CameraManager::GetInst()->SetAim(aimTrace);

    gameOver = false;

    NaveMeshManager::GetInst()->SetPlayer(player);
    NaveMeshManager::GetInst()->CreateLinkTable();

    enemyDir = true;

    //Audio
    bgm = ResourceManager::GetInst()->Get("BossBGM", "Assets/BossBgm.mp3");
    bgm_res = static_cast<AudioResource*>(bgm);
    bgm_res->PlayMusicOrSFX(bgm_res, Sound::MUSIC, 1.0f, 1.0f, -1);

    Boss_bullet_count1 = true;
    Boss_bullet_count2 = true;
    Boss_bullet_count3 = true;

}

void Level::StageBoss_Lvl::Update()
{
    TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
    TransComponent* bg_trs = (TransComponent*)background->FindComponent("Transform");

    bg_trs->SetPos(player_trs->GetPos());
    bg_trs->SetScale({ 1600,900 });

    

    //AEGfxSetBackgroundColor(0.3f, 0.3f, 0.3f);
    AEInputShowCursor(0);
    //Component Pointer        
    //Component 
    //SpriteComponent* player_spr = (SpriteComponent*)player->FindComponent("Sprite");
    RigidBodyComponent* player_rig = (RigidBodyComponent*)player->FindComponent("RigidBody");
    PlayerComponent* player_comp = (PlayerComponent*)player->FindComponent("PlayerComp");

    TransComponent* EnemyTest_trs = (TransComponent*)Enemy_TEST->FindComponent("Transform");
    //SpriteComponent* EnemyTest_spr = (SpriteComponent*)Enemy_TEST->FindComponent("Sprite");
    RigidBodyComponent* EnemyTest_rig = (RigidBodyComponent*)Enemy_TEST->FindComponent("RigidBody");
    EnemyAnimationComponent* Enemy_ani = (EnemyAnimationComponent*)Enemy_TEST->FindComponent("EnemyAnimation");

    TransComponent* boss_drone_trs = (TransComponent*)Boss_drone->FindComponent("Transform");
    EnemyAnimationComponent* boss_drone_ani = (EnemyAnimationComponent*)Boss_drone->FindComponent("EnemyAnimation");
    playerPos = player_trs->GetPos();
    enemyTestPos = EnemyTest_trs->GetPos();
    chaseVec.x = playerPos.x - enemyTestPos.x;
    chaseVec.y = playerPos.y - enemyTestPos.y;

    //먼저 보스 드론위치를 보스와 맞추기
    boss_drone_trs->SetPos(EnemyTest_trs->GetPos().x + 80, EnemyTest_trs->GetPos().y);
    if (ColliderManager::GetInst()->isFacingtheSameDirection(chaseVec, Boss_drone_dir))
    {
        Boss_drone_dir = !(Boss_drone_dir);
        boss_drone_ani->SetEnemyDir(!Boss_drone_dir);
    }

    if (Boss_drone_dir) 
    {
        boss_drone_trs->SetPos(EnemyTest_trs->GetPos().x - 80, EnemyTest_trs->GetPos().y);
    }
    else 
    {
        boss_drone_trs->SetPos(EnemyTest_trs->GetPos().x + 80, EnemyTest_trs->GetPos().y);
    }




    //Display Bullet===============
    auto pFont = static_cast<TextResource*>(ResourceManager::GetInst()->Get("esamanru", "Assets/esamanru-Bold.ttf"));
    std::string str1 = std::to_string(GetBullet());
    std::string str2 = "Bullet: ";
    const char* cstr1 = str1.c_str();
    const char* cstr2 = str2.c_str();

    AEGfxPrint(pFont->GetFont(), cstr1, -0.85f, 0.8f, 20.f / 72.f, 1.f, 1.f, 1.f, 1.f);
    AEGfxPrint(pFont->GetFont(), cstr2, -0.95f, 0.8f, 20.f / 72.f, 1.f, 1.f, 1.f, 1.f);

    f32 dt = static_cast<f32>(AEFrameRateControllerGetFrameTime());

    if (!(ColliderManager::GetInst()->isFacingtheSameDirection(chaseVec, enemyDir)))
    {
        //Chase_outTime = 0.0f;
        enemyDir = !(enemyDir);
        Enemy_ani->SetEnemyDir(!enemyDir);
    }

    if (player_comp->GetManiActive() == true)
    {
        float vol = bgm_res->GetPitch();
        if (vol >= 0.3)
        {
            bgm_res->SetPitch(vol - dt);
            AEAudioSetGroupPitch(bgm_res->GetAudioGroup(), bgm_res->GetPitch());
        }
        player_comp->SetTriggeredButton(true);
    }
    else if (player_comp->GetTriggeredButton() == true)
    {
        float vol = bgm_res->GetPitch();
        if (vol <= 1.0)
        {
            bgm_res->SetPitch(vol + dt);
            AEAudioSetGroupPitch(bgm_res->GetAudioGroup(), bgm_res->GetPitch());
        }
    }
    
    
    if (Enemy_TEST->GetHP() <= 0)
    {
        GSM::GameStateManager* gsm = GSM::GameStateManager::GetInst();
        gsm->ChangeLevel(new Level::Congratulation);
        return;
    }

    //패딩시 진동 
    if (IsVibration == false)
    {
        CameraManager::GetInst()->Update();
    }
    else
    {
        f32 deltaTime = static_cast<f32>(AEFrameRateControllerGetFrameTime());
        VibrationAccTime += deltaTime;
        f32 playerPosX = player_trs->GetPos().x;
        f32 playerPosY = player_trs->GetPos().y;
        if (IsVibration && VibrationAccTime >= 0 && VibrationAccTime < 0.1)
        {
            minusX += -10 * deltaTime;
            minusY += 10 * deltaTime;
            playerPosX += minusX;
            playerPosY += minusY;
            AEGfxSetCamPosition(playerPosX, playerPosY);
        }
        else if (IsVibration && VibrationAccTime >= 0.1 && VibrationAccTime < 0.2)
        {
            plusX += 10 * deltaTime;
            plusY += -10 * deltaTime;
            playerPosX += plusX;
            playerPosY += plusY;
            AEGfxSetCamPosition(playerPosX, playerPosY);
        }
        else if (IsVibration && VibrationAccTime >= 0.2 && VibrationAccTime < 0.3)
        {
            minusX += -10 * deltaTime;
            minusY += 10 * deltaTime;
            playerPosX += minusX;
            playerPosY += minusY;
            AEGfxSetCamPosition(playerPosX, playerPosY);
        }
        else if (IsVibration && VibrationAccTime >= 0.3)
        {
            AEGfxSetCamPosition(player_trs->GetPos().x, player_trs->GetPos().y);
            VibrationAccTime = 0.f;
            IsVibration = false;
        }
    }
    


    Collision();
 


    GoManager::GetInst()->RemoveDeathObj();

    if (AEInputCheckPrev(AEVK_0))
    {
        GSM::GameStateManager::GetInst()->Exit();
    }

    if (!(player_comp->IsAlive()))
    {
        GSM::GameStateManager* gsm = GSM::GameStateManager::GetInst();
        gsm->ChangeLevel(new Level::GameOver_Lvl);

        return;
    }
   
    


    //======================WARNING=============================
    //=======NEVER TOUCH DOWN CODE EXCEPT HWNAG JUHYUN==========        
    RigidBodyComponent* EnemyTEST_rg = static_cast<RigidBodyComponent*>(Enemy_TEST->FindComponent("RigidBody"));
    PathFindMoveComponent* EnemyTEST_pf = static_cast<PathFindMoveComponent*>(Enemy_TEST->FindComponent("PathFindMove"));
    EnemyAnimationComponent* Boss_drone_ani = (EnemyAnimationComponent*)Boss_drone->FindComponent("EnemyAnimation");
    

    NaveMeshManager::GetInst()->SetMinCost(10000.f);
    //플레이어한테서 가장 가까운 노드를 찾는다
    int player_node = NaveMeshManager::GetInst()->FindObjectNode(player);

    //보스의 현재위치의 가장 가까운 노드를 찾는다
    int EnemyTest_node = NaveMeshManager::GetInst()->FindObjectNode(Enemy_TEST);

    auto node_link = NaveMeshManager::GetInst()->GetvecLink();
    auto node = NaveMeshManager::GetInst()->GetallNode();
    
    /*for (auto it : NaveMeshManager::GetInst()->GetallNode())
        NaveMeshManager::GetInst()->DrawNode(it.node_pos.x - 25, it.node_pos.y - 35, it.node_pos.x + 25, it.node_pos.y + 35, 1.0f, 1.0f, 0);*/

    int i = 0;



    //for (auto it : NaveMeshManager::GetInst()->GetvecLink())
    //{
    //    //draw from
    //    for (auto n : it)
    //    {
    //        //If cost >0 then 
    //            //Draw line  from node[i] to node [n.first]
    //        if(n.second->cost > 0)
    //            NaveMeshManager::GetInst()->DrawNode(node[i].node_pos.x, node[i].node_pos.y, node[n.first].node_pos.x, node[n.first].node_pos.y, 0.0f, 0.0f, 1.0f);

    //        std::cout << i << " | " << n.first << "-> " << n.second->cost << std::endl;
    //    }

    //    i++;
    //}


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
        //costLink는 점프가 될수도 있고  walk가 될 수도 있음                                          
        int nodeID1 = FoundedPath[PathIndex];
        int nodeID2;
        
        if (FoundedPath.size() > PathIndex + 1)
            nodeID2 = FoundedPath[PathIndex + 1];
        else
            nodeID2 = nodeID1;

        int idx = 0;
        while (nodeID2 != node_link[nodeID1][idx].first && idx < 2)
        { 
            idx++;
        }
        auto costLink = node_link[FoundedPath[PathIndex]][idx].second;

        //해당 보스위치가 다음 서브노드의 도착지점에 도착하였다면!
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

    if (Enemy_TEST->GetHP() >= 15 && Enemy_TEST->GetHP() <= 20)
    {
        
        AEVec2 dVec = { -(EnemyTest_trs->GetPos().x - player_trs->GetPos().x), -(EnemyTest_trs->GetPos().y - player_trs->GetPos().y) }; //direction Vector
        AEVec2 nor_dVec{ 0,0 }; //Normailize direction Vector
        AEVec2Normalize(&nor_dVec, &dVec);
        float deltaTime = (f32)AEFrameRateControllerGetFrameTime();
        if (player_comp->GetManipulate()) 
        {
            AttackDelayTime += deltaTime * 0.1f;
        }
        else 
        {
            AttackDelayTime += deltaTime;
        }
        if (AttackDelayTime > 2.4f)
        {
            if (Boss_bullet_count1)
            {
                Boss_bullet_count1 = false;
                auto res_BossShotgun = ResourceManager::GetInst()->Get("sfx_BossShotgun", "Assets/BossShotgun.mp3");
                AudioResource* bgm_res = static_cast<AudioResource*>(res_BossShotgun);
                bgm_res->PlayMusicOrSFX(bgm_res, Sound::SFX, 1.f, 1.f, 0);
                CreateBullet(EnemyTest_trs->GetPos(), nor_dVec, "BossBullet", true);
            }
            if (AttackDelayTime > 4.8f)
            {
                AttackDelayTime = 0.f;
                Boss_bullet_count1 = true;
            }
        }
    }
    else if (Enemy_TEST->GetHP() >= 10&& Enemy_TEST->GetHP()<15)
    {
        Boss_drone_ani->ChangeAnimation("Boss_drone_Atk", 1, 12, 12, 0.3f);
        AEVec2 dVec = { -(EnemyTest_trs->GetPos().x - player_trs->GetPos().x), -(EnemyTest_trs->GetPos().y - player_trs->GetPos().y) }; //direction Vector
        AEVec2 nor_dVec{ 0,0 }; //Normailize direction Vector
        AEVec2Normalize(&nor_dVec, &dVec);
        float deltaTime = (f32)AEFrameRateControllerGetFrameTime();
        if (player_comp->GetManipulate())
        {
            AttackDelayTime += deltaTime * 0.1f;
        }
        else
        {
            AttackDelayTime += deltaTime;
        }
        if (AttackDelayTime > 1.8f)
        {
            if (Boss_bullet_count2)
            {
                Boss_bullet_count2 = false;
                auto res_BossShotgun = ResourceManager::GetInst()->Get("sfx_BossShotgun", "Assets/BossShotgun.mp3");
                AudioResource* bgm_res = static_cast<AudioResource*>(res_BossShotgun);
                bgm_res->PlayMusicOrSFX(bgm_res, Sound::SFX, 1.f, 1.f, 0);
                /* bgm_res->SetSFXorMusic(Sound::SFX);
                 auto bgm_audio = bgm_res->GetAudio();
                 auto bgm_audioGroup = bgm_res->GetAudioGroup();
                 AEAudioPlay(bgm_audio, bgm_audioGroup, 1.f, 1.f, 0);*/
                CreateBullet(EnemyTest_trs->GetPos(), nor_dVec, "BossBullet", true);
                nor_dVec.y += 0.05f;
                CreateBullet(EnemyTest_trs->GetPos(), nor_dVec, "BossBullet", true);
                nor_dVec.y += 0.05f;
                CreateBullet(EnemyTest_trs->GetPos(), nor_dVec, "BossBullet", true);
                nor_dVec.y -= 0.15f;
                CreateBullet(EnemyTest_trs->GetPos(), nor_dVec, "BossBullet", true);
                nor_dVec.y -= 0.30f;
            }
            if (AttackDelayTime > 3.6f) 
            {
                AttackDelayTime = 0.f;
                Boss_bullet_count2 = true;
            }

        }
    }
    else if (Enemy_TEST->GetHP() < 10)
    {
        Boss_drone_ani->ChangeAnimation("Boss_drone_Atk", 1, 12, 12, 0.1f);
        AEVec2 dVec = { -(EnemyTest_trs->GetPos().x - player_trs->GetPos().x), -(EnemyTest_trs->GetPos().y - player_trs->GetPos().y) }; //direction Vector
        AEVec2 nor_dVec{ 0,0 }; //Normailize direction Vector
        AEVec2Normalize(&nor_dVec, &dVec);
        float deltaTime = (f32)AEFrameRateControllerGetFrameTime();
        if (player_comp->GetManipulate())
        {
            AttackDelayTime += deltaTime * 0.1f;
        }
        else
        {
            AttackDelayTime += deltaTime;
        }
        if (AttackDelayTime > 0.6f)
        {
            if (Boss_bullet_count3) 
            {
                Boss_bullet_count3 = false;
                auto res_BossShotgun = ResourceManager::GetInst()->Get("sfx_BossShotgun", "Assets/BossShotgun.mp3");
                AudioResource* bgm_res = static_cast<AudioResource*>(res_BossShotgun);
                bgm_res->PlayMusicOrSFX(bgm_res, Sound::SFX, 1.f, 1.f, 0);
                CreateBullet(EnemyTest_trs->GetPos(), nor_dVec, "BossBullet", true);
            }
            else 
            {
                Boss_bullet_count3 = true;
                AttackDelayTime = 0.f;
            }
        }
    }
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
    TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
    TransComponent* EnemyTest_trs = (TransComponent*)Enemy_TEST->FindComponent("Transform");
   //SpriteComponent* EnemyTest_spr = (SpriteComponent*)Enemy_TEST->FindComponent("Sprite");
    RigidBodyComponent* EnemyTest_rig = (RigidBodyComponent*)Enemy_TEST->FindComponent("RigidBody");
    EnemyAnimationComponent* Enemy_ani = (EnemyAnimationComponent*)Enemy_TEST->FindComponent("EnemyAnimation");
    //Collision
    int cnt = 0;
    f32 m_fDt = static_cast<f32>(AEFrameRateControllerGetFrameTime());
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
            //총알 플랫폼 충돌처리 <- 총알과 플랫폼이 충돌 시 총알이 사라지게 하는 코드
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

        //패딩
        if (obj->GetName() == "BossBullet")
        {
            BulletComponent* bullet_comp = (BulletComponent*)obj->FindComponent("Bullet");
            if (ColliderManager::GetInst()->IsCollision(player_comp->GetMelee(), obj))
            {
                auto res_padding = ResourceManager::GetInst()->Get("sfx_paddingBoss", "Assets/padding2.wav");
                AudioResource* bgm_res = static_cast<AudioResource*>(res_padding);
                bgm_res->PlayMusicOrSFX(bgm_res, Sound::SFX, 1.f, 1.f, 0);

                //BulletComponent* bullet_comp = (BulletComponent*)obj->FindComponent("Bullet");

                if (!bullet_comp->GetState())
                {
                    bullet_comp->SetState();
                    bullet_comp->EnemyShoot = false;
                    AEVec2 bulletVec = bullet_comp->GetBulletVec();
                    AEVec2 nor_dVec{ 0,0 };
                    AEVec2Normalize(&nor_dVec, &bulletVec);
                    AEVec2Scale(&nor_dVec, &nor_dVec, -1);

                    bullet_comp->SetBulletVec(nor_dVec);       
                    //IsVibration = true;
                }
                /*bullet_comp->EnemyShoot = false;
                AEVec2 returnbullet = bullet_comp->GetBulletVec();
                float dt = AEFrameRateControllerGetFrameTime();

                if (AEInputCheckCurr(AEVK_LSHIFT))
                {
                    bullet_comp->SetBulletVec({ -1 * returnbullet.x * dt,-1 * returnbullet.y * dt });
                }
                else
                {
                    bullet_comp->SetBulletVec({ -1 * returnbullet.x,-1 * returnbullet.y });
                }*/
            }

            //Player Death
            //이 부분도 새론운 Collision 추가
            if (ColliderManager::GetInst()->handle_Player_EnemyAtk_Collision(player, obj) && !player_comp->GetInvincible() && bullet_comp->EnemyShoot)
            {
                auto resDead = ResourceManager::GetInst()->Get("sfx_PlayerDeadToBoss", "Assets/Dead1.wav");
                AudioResource* bgm_resDead = static_cast<AudioResource*>(resDead);
                bgm_resDead->PlayMusicOrSFX(bgm_resDead, Sound::SFX, 1.f, 1.f, 0);
                player_comp->TakeDamge();
            }
        }

        if (obj->GetName() == "Enemy_TEST")
        {
            //총알부분
            for (auto findObj : GoManager::GetInst()->Allobj())
            {
                if (findObj->GetName() == "PlayerBullet" || findObj->GetName() == "BossBullet")
                {
                    if (ColliderManager::GetInst()->IsCollision(findObj, obj))
                    {
                        BulletComponent* bullet_comp = (BulletComponent*)findObj->FindComponent("Bullet");
                        if (!bullet_comp->EnemyShoot)
                        {
                            bullet_comp->DestroyBullet();
                            obj->AddHP(-1);
                        }
                    }
                }
            }
            //플레이어의 MeleeAttack으로 보스 데미지 입는 부분
            if (ColliderManager::GetInst()->IsCollision(player_comp->GetMelee(), obj)&&obj->GetBossTakeDamage()==true)
            {                
                obj->SetSturn(true);                                
                obj->AddHP(-1); 
                obj->SetBossTakeDamage(false);                
            }
            
        }
        if (obj->GetBossTakeDamage() == false)
        {
           f32 m_fDt = static_cast<f32>(AEFrameRateControllerGetFrameTime());
           obj->TakeDamageCoolTime += m_fDt;
           if (obj->TakeDamageCoolTime >= 1.f)
           {
               obj->SetBossTakeDamage(true);
               obj->TakeDamageCoolTime = 0.f;
           }
        }
        if (obj->GetSturn() == true&& obj->GetHP() % 3 != 0)
        {
            f32 m_fDt = static_cast<f32>(AEFrameRateControllerGetFrameTime());
            obj->SturnAccTime += m_fDt;

            ColliderManager::GetInst()->SetPlayerSearchOnOff(false);
            EnemyTest_trs->AddPos(0.f, 0.f);
            Enemy_ani->ChangeAnimation("BossSturn", 1, 2, 2, 0.1f);
        }
        bool KnockBack = false;
        if (obj->SturnAccTime >= 1.0f)
        {
            obj->SetSturn(false);
            obj->SturnAccTime = 0.f;
            ColliderManager::GetInst()->SetPlayerSearchOnOff(true);            


            obj->KnockBackChase.x = player_trs->GetPos().x-EnemyTest_trs->GetPos().x;
            obj->KnockBackChase.y = player_trs->GetPos().y-EnemyTest_trs->GetPos().y;

            //obj->KnockBackChase.x = EnemyTest_trs->GetPos().x - player_trs->GetPos().x;
            //obj->KnockBackChase.y = EnemyTest_trs->GetPos().y - player_trs->GetPos().y;
            AEVec2Normalize(&obj->unitKnockBackChase, &obj->KnockBackChase);
            KnockBack = true;            
        }
        if (KnockBack)
        {            
            if (obj->KnockBackAccTime >= 3.f)
            {
                KnockBack = false;
                obj->KnockBackAccTime = 0.f;
            }
            obj->KnockBackAccTime += m_fDt;
            player_trs->AddPos({obj->unitKnockBackChase.x,0.f});
        }
    }        
    if (ColliderManager::GetInst()->IsCollision(player_comp->GetMelee(), Enemy_TEST) && Enemy_TEST->GetBossTakeDamage() == true)
    {
        Enemy_TEST->SetSturn(true);
        Enemy_TEST->AddHP(-1);
        Enemy_TEST->SetBossTakeDamage(false);
    }
    if (ColliderManager::GetInst()->KnockBackCollision(player_comp->GetMelee(), Enemy_TEST) && Enemy_TEST->GetHP() % 3 == 0)
    {
        Enemy_TEST->KnockBack = true;
        Enemy_TEST->KnockBackChase.x = player_trs->GetPos().x - EnemyTest_trs->GetPos().x;
        Enemy_TEST->KnockBackChase.y = player_trs->GetPos().y - EnemyTest_trs->GetPos().y;
        AEVec2Normalize(&Enemy_TEST->unitKnockBackChase, &Enemy_TEST->KnockBackChase);
    }
    //넉백
    if (Enemy_TEST->KnockBack == true)
    {
        Enemy_TEST->SetSturn(false);
        Enemy_TEST->KnockBackAccTime += m_fDt;
        if (Enemy_TEST->KnockBackAccTime >= 1.0f)
        {
            Enemy_TEST->KnockBack = false;
            Enemy_TEST->KnockBackAccTime = 0.f;
            Enemy_ani->ChangeAnimation("BossRun", 1, 6, 6, 0.1f);
        }
        else 
        {
            EnemyTest_trs->AddPos({ 0.f,0.f });
            player_trs->AddPos(Enemy_TEST->unitKnockBackChase.x * 500.f * m_fDt, Enemy_TEST->unitKnockBackChase.y * 500.f * m_fDt);
            Enemy_ani->ChangeAnimation("KnockBack", 1, 8, 8, 0.1f);
        }
    }
    //1초당 보스의 피격을 위해서
    if (Enemy_TEST->GetBossTakeDamage() == false)
    {
        Enemy_TEST->TakeDamageCoolTime += m_fDt;

        if (Enemy_TEST->TakeDamageCoolTime >= 1.f)
        {
            Enemy_TEST->SetBossTakeDamage(true);
            Enemy_TEST->TakeDamageCoolTime = 0.f;
        }
    }
    //스턴 상태
    if (Enemy_TEST->GetSturn() == true)
    {
        Enemy_TEST->SturnAccTime += m_fDt;
        ColliderManager::GetInst()->SetPlayerSearchOnOff(false);
        EnemyTest_trs->AddPos(0.f, 0.f);
        Enemy_ani->ChangeAnimation("BossSturn", 1, 2, 2, 0.1f);
    }
    //스턴이 끝났다면
    if (Enemy_TEST->SturnAccTime >= 1.0f)
    {
        Enemy_TEST->SetSturn(false);
        Enemy_TEST->SturnAccTime = 0.f;
        ColliderManager::GetInst()->SetPlayerSearchOnOff(true);
    }

    

    //여기가 보스랑 플레이어가 부딫히는 부분
    if (ColliderManager::GetInst()->GetPlayerSearchOnOff() == true)
    {
        if (ColliderManager::GetInst()->PlayerSearch(Enemy_TEST, player, enemyDir, 0.1f, 1.f, 1.f) && !player_comp->GetInvincible())
        {
            Enemy_ani->ChangeAnimation("BossAtk", 1, 4, 4, 0.1f);
            m_fDt = (f32)AEFrameRateControllerGetFrameTime();
            if (player_comp->GetManiActive())
            {
                melee_DelayAtk += m_fDt * 0.1f;
            }
            else
            {
                melee_DelayAtk += m_fDt;
            }

            if (melee_DelayAtk > 0.4f)
            {
                player_comp->TakeDamge();
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


