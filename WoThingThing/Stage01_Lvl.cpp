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
#include "AnimationComponent.h"
#include "CompManager.h"

#include "EventManager.h"
#include "ColliderManager.h"
#include "ResourceManager.h"
#include "TimeManager.h"

#include "AudioResource.h"
#include "TextResource.h"
#include "ImageResource.h"


#include "Serializer.h"
#include "NaveMeshManager.h"
#include "Utility.h"
#include "AiComponent.h"
#include "CameraManager.h"
#include "PathFindMoveComponent.h"
#include "StageBoss_Lvl.h"

#include "AudioResource.h"

#include "AEAudio.h"
#include "AEInput.h"
#include "AEUtil.h"
#include "AEMath.h"

#include "Bullet.h"
#include"TargetAim_Sniper.h"
#include"AnimationComponent.h"

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
    //player->AddComponent("Animation", new AnimationComponent(player));
    player->AddComponent("PlayerComp", new PlayerComponent(player));
    //Add Image Resource??
    TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
    player_trs->SetScale({ 80, 80 });




    aimTrace = new GameObject("aimTrace");
    GoManager::GetInst()->AddObject(aimTrace);
    aimTrace->AddComponent("Transform", new TransComponent(aimTrace));
    aimTrace->AddComponent("Sprite", new SpriteComponent(aimTrace));   


          

    //Enemy
    for (int i = 0; i < Enemy.size(); i++)
    {
        Enemy[i] = new GameObject("Enemy");       
        Enemy[i]->SetID(i);
        GoManager::GetInst()->AddObject(Enemy[i]);
        Enemy[i]->AddComponent("Transform", new TransComponent(Enemy[i]));
        Enemy[i]->AddComponent("Sprite", new SpriteComponent(Enemy[i]));
        Enemy[i]->AddComponent("RigidBody", new RigidBodyComponent(Enemy[i]));
        Enemy[i]->AddComponent("Ai", new AiComponent(Enemy[i]));
        TransComponent* Enemy_trs = (TransComponent*)Enemy[i]->FindComponent("Transform");
        AiComponent* Enemy_state = (AiComponent*)Enemy[i]->FindComponent("Ai");
        Enemy_state->SetTarget(player);//순서중요 trager부터 먼저 세팅 해준다 그리고 먼저 palyer부터 만들어준다.
        Enemy_state->Setdir(true);//true가 오른쪽, false가 왼쪽
        Enemy_state->Setdir_time(2.0f);
        Enemy_state->SetFirstPlace(Enemy_trs->GetPos());
        Enemy_state->SetState("IDLE", "Melee");
    }
    


    for (int i = 0; i < EnemySniper.size(); i++)
    {
        EnemySniper[i] = new GameObject("EnemySniper");
        EnemySniper[i]->SetID(i);
        GoManager::GetInst()->AddObject(EnemySniper[i]);
        EnemySniper[i]->AddComponent("Transform", new TransComponent(EnemySniper[i]));
        EnemySniper[i]->AddComponent("Sprite", new SpriteComponent(EnemySniper[i]));
        EnemySniper[i]->AddComponent("RigidBody", new RigidBodyComponent(EnemySniper[i]));
        EnemySniper[i]->AddComponent("Ai", new AiComponent(EnemySniper[i]));
        AiComponent* EnemySniper_state = (AiComponent*)EnemySniper[i]->FindComponent("Ai");
        EnemySniper_state->SetTarget(player);//순서중요 trager부터 먼저 세팅 해준다 그리고 먼저 palyer부터 만들어준다.
        EnemySniper_state->Setdir(true);//true가 오른쪽, false가 왼쪽
        EnemySniper_state->Setdir_time(1.0f);
        EnemySniper_state->SetState("IDLE_Sniper", "Sniper");
    }


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

    //gameOver = false;

    NaveMeshManager::GetInst()->SetPlayer(player);
    NaveMeshManager::GetInst()->CreateLinkTable();


    //Audio Init
    auto res = ResourceManager::GetInst()->Get("bgm", "Assets/bouken.mp3");
    AudioResource* bgm_res = static_cast<AudioResource*>(res);
    bgm_res->SetSFXorMusic(Sound::MUSIC);
    auto bgm_audio = bgm_res->GetAudio();
    auto bgm_audioGroup = bgm_res->GetAudioGroup();
    AEAudioPlay(bgm_audio, bgm_audioGroup, 1.f, 1.f, 0);
}

void Level::Stage01_Lvl::Update()
{
    //Component Pointer

    TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
    //SpriteComponent* player_spr = (SpriteComponent*)player->FindComponent("Sprite");
    RigidBodyComponent* player_rig = (RigidBodyComponent*)player->FindComponent("RigidBody");
    PlayerComponent* player_comp = (PlayerComponent*)player->FindComponent("PlayerComp");
        

    Collision();    

    if(player_trs->GetPos().y<-1800)
        player_comp->SetHealth(-1);
    else
    {
        //Camera Update
        CameraManager::GetInst()->Update();
    }
    GoManager::GetInst()->RemoveDeathObj();

    if (AEInputCheckPrev(AEVK_0))
    {
        GSM::GameStateManager::GetInst()->Exit();
    }

    //Player->GetHeath() == 0
    //    gameOver = true

    if (!(player_comp->IsAlive()))
    {
        GSM::GameStateManager* gsm = GSM::GameStateManager::GetInst();
        gsm->ChangeLevel(new Level::GameOver_Lvl);

        return;
    }

    //std::cout << std::endl;
    if (AEInputCheckTriggered(AEVK_ESCAPE))
        GSM::GameStateManager::GetInst()->ChangeLevel(new MainMenu_Lvl);



    if (AEInputCheckTriggered(AEVK_F1))
        GSM::GameStateManager::GetInst()->ChangeLevel(new StageBoss_Lvl);


}


void Level::Stage01_Lvl::Exit()
{    
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
            //플레이어 플랫폼 충돌처리
            //with Player
            if (ColliderManager::GetInst()->IsCollision(player, obj))
            {
                HandleCollision(player, obj);
            }
            //Enemy 플랫폼 충돌처리
            for (int i = 0; i < Enemy.size(); i++)
            {
                if (ColliderManager::GetInst()->IsCollision(Enemy[i], obj))
                {
                    HandleCollision(Enemy[i], obj);
                    //AI COMP세팅을 해주고
                    Enemy_Platform_Collision_Event* e_p_c_e = new Enemy_Platform_Collision_Event(obj, Enemy[i]);
                    EventManager::GetInst()->AddEvent(e_p_c_e);
                    
                }               
            }
            //EnemySniper 플랫폼 충돌처리
            for (int i = 0; i < EnemySniper.size(); i++)
            {
                if (ColliderManager::GetInst()->IsCollision(EnemySniper[i], obj))
                {
                    HandleCollision(EnemySniper[i], obj);
                }
            }           
            //총알 플랫폼 충돌처리
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
        //패딩 (반사)
        //Enemy Bullet
        if (obj->GetName() == "EnemyBullet")
        {
            //with Player's Melee ==> Parrying
            if (ColliderManager::GetInst()->IsCollision(player_comp->GetMelee(), obj))
            {
                BulletComponent* bullet_comp = (BulletComponent*)obj->FindComponent("Bullet");
                if(!bullet_comp->GetState())
                {
                    bullet_comp->SetState();
                    bullet_comp->EnemyShoot = false;
                    AEVec2 bulletVec = bullet_comp->GetBulletVec();
                    AEVec2 nor_dVec{ 0,0 }; //Normailize direction Vector
                    AEVec2Normalize(&nor_dVec, &bulletVec);
                    AEVec2Scale(&nor_dVec, &nor_dVec, -1);

                    bullet_comp->SetBulletVec(nor_dVec);
                }
            }
           //Player Death           
           if (ColliderManager::GetInst()->IsCollision(player, obj))
           {               
               //gameOver = true;
               player_comp->TakeDamge();
                //audio
                auto res = ResourceManager::GetInst()->Get("sfx", "Assets/ore.mp3");
                AudioResource* sfx_res = static_cast<AudioResource*>(res);
                sfx_res->SetSFXorMusic(Sound::MUSIC);
                auto sfx_audio = sfx_res->GetAudio();
                auto sfx_audioGroup = sfx_res->GetAudioGroup();
                AEAudioPlay(sfx_audio, sfx_audioGroup, 1.f, 1.f, 0);
           }
        }


        //Sniper죽는판정
        if (obj->GetName() == "EnemySniper")
        {           
            int SniperObjID = 0;
            //Test: Collision Enemy with Player's Bullet
            for (auto findObj : GoManager::GetInst()->Allobj())
            {
                if (findObj->GetName() == "PlayerBullet" || findObj->GetName() == "EnemyBullet")
                {
                    if (ColliderManager::GetInst()->IsCollision(findObj, obj))
                    {
                        SniperObjID = obj->GetID();

                        BulletComponent* bullet_comp = (BulletComponent*)findObj->FindComponent("Bullet");
                        if (!bullet_comp->EnemyShoot)
                        {
                            EnemySniper[SniperObjID]->SetActive(false);
                            EnemySniper[SniperObjID] = nullptr; 
                            
                            auto res = ResourceManager::GetInst()->Get("sfx", "Assets/ore.mp3");
                            AudioResource* bgm_res = static_cast<AudioResource*>(res);
                            bgm_res->SetSFXorMusic(Sound::MUSIC);
                            auto bgm_audio = bgm_res->GetAudio();
                            auto bgm_audioGroup = bgm_res->GetAudioGroup();
                            AEAudioPlay(bgm_audio, bgm_audioGroup, 1.f, 1.f, 0);
                        }
                        bullet_comp->DestroyBullet();

                    }
                }             
            }
            //플레이어의 밀리어택 
            if (ColliderManager::GetInst()->IsCollision(player_comp->GetMelee(), obj))
            {
                SniperObjID = obj->GetID();
                EnemySniper[SniperObjID]->SetActive(false);
                EnemySniper[SniperObjID] = nullptr;

                auto res = ResourceManager::GetInst()->Get("sfx", "Assets/ore.mp3");
                AudioResource* bgm_res = static_cast<AudioResource*>(res);
                bgm_res->SetSFXorMusic(Sound::MUSIC);
                auto bgm_audio = bgm_res->GetAudio();
                auto bgm_audioGroup = bgm_res->GetAudioGroup();
                AEAudioPlay(bgm_audio, bgm_audioGroup, 1.f, 1.f, 0);
            }
        }        
        if (obj->GetName() == "Enemy") 
        {    
            //총알부분
            int meeleObjID = 0;
            for (auto findObj : GoManager::GetInst()->Allobj())            
            {                       
                if (findObj->GetName() == "PlayerBullet" || findObj->GetName() == "EnemyBullet") 
                {                    
                    if (ColliderManager::GetInst()->IsCollision(findObj, obj)) 
                    {
                        meeleObjID=obj->GetID();
                        BulletComponent* bullet_comp = (BulletComponent*)findObj->FindComponent("Bullet");
                        if (!bullet_comp->EnemyShoot)
                        {
                            Enemy[meeleObjID]->SetActive(false);
                            Enemy[meeleObjID] = nullptr;
                            bullet_comp->DestroyBullet();

                            auto res = ResourceManager::GetInst()->Get("sfx", "Assets/ore.mp3");
                            AudioResource* bgm_res = static_cast<AudioResource*>(res);
                            bgm_res->SetSFXorMusic(Sound::MUSIC);
                            auto bgm_audio = bgm_res->GetAudio();
                            auto bgm_audioGroup = bgm_res->GetAudioGroup();
                            AEAudioPlay(bgm_audio, bgm_audioGroup, 1.f, 1.f, 0);
                        }
                    }
                }
            }
            //근접
            if (ColliderManager::GetInst()->IsCollision(player_comp->GetMelee(), obj)) 
            {
                meeleObjID = obj->GetID();
                Enemy[meeleObjID]->SetActive(false);
                Enemy[meeleObjID] = nullptr;
             
                //audio
                auto res = ResourceManager::GetInst()->Get("sfx", "Assets/ore.mp3");
                AudioResource* sfx_res = static_cast<AudioResource*>(res);
                sfx_res->SetSFXorMusic(Sound::MUSIC);
                auto sfx_audio = sfx_res->GetAudio();
                auto sfx_audioGroup = sfx_res->GetAudioGroup();
                AEAudioPlay(sfx_audio, sfx_audioGroup, 1.f, 1.f, 0);
            }
        }

        //supply bullet
        if (obj->GetName() == "BulletSupplement")
        {
            if (ColliderManager::GetInst()->IsCollision(player, obj))
            {
                AddBullet();
                obj->SetActive(false);
            }
        }
        //obtain gun
        if (obj->GetName() == "Gun")
        {
            if (ColliderManager::GetInst()->IsCollision(player, obj))
            {
                player_comp->SetObtain();

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