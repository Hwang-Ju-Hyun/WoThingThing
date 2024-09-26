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
#include "Chase.h"
#include "AudioResource.h"

#include "AEAudio.h"
#include "AEInput.h"
#include "AEUtil.h"
#include "AEMath.h"
#include <random>
#include "Bullet.h"
#include"TargetAim_Sniper.h"
#include"AnimationComponent.h"
#include"EnemyAnimationComponent.h"
#include"StageBoss_Lvl.h"
AEVec2 enemyDvec{ 1, 0 };

Level::Stage01_Lvl::Stage01_Lvl()
{    
}

Level::Stage01_Lvl::~Stage01_Lvl()
{
}

void Level::Stage01_Lvl::Init()
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

    //Object and Component Init
    ResourceManager::GetInst()->Get("MeleeIdle", "Assets/meleeEnemyIdle.png");
    ResourceManager::GetInst()->Get("MeleeChase", "Assets/meleeEnemyChase.png");
    ResourceManager::GetInst()->Get("MeleeAttack", "Assets/meleeEnemyAtk.png");//("MeleeAttack", 1, 5, 5, 0.1);
    ResourceManager::GetInst()->Get("SniperIdle", "Assets/sniperEnemyIdle.png");//12
    ResourceManager::GetInst()->Get("SniperShootIdle", "Assets/sniperEnemyShootIdle.png");//1
    ResourceManager::GetInst()->Get("SniperShoot", "Assets/sniperEnemyShoot.png");//5

    //stage01���� �ҷ�����
    Serializer::GetInst()->LoadLevel("Assets/stage01.json");


    player = new GameObject("Player");
    GoManager::GetInst()->AddObject(player); //GetInst() == GetPtr()
    player->AddComponent("Transform", new TransComponent(player));
    player->AddComponent("PlayerComp", new PlayerComponent(player));
    //player->AddComponent("Sprite", new SpriteComponent(player));
    //Add Image Resource??
    TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
    player_trs->SetScale({ 80, 80 });

    playerAnim = new GameObject("PlayerAnim");
    GoManager::GetInst()->AddObject(playerAnim); //GetInst() == GetPtr()
    playerAnim->AddComponent("Transform", new TransComponent(playerAnim));
    playerAnim->AddComponent("Animation", new AnimationComponent(playerAnim));

    CameraManager::GetInst()->SetMouse(mouseAim);
    CameraManager::GetInst()->SetPlayer(player);

    for (int i = 0; i < Enemy.size(); i++)
    {
        Enemy[i] = new GameObject("Enemy");
        Enemy[i]->SetID(i);
        GoManager::GetInst()->AddObject(Enemy[i]);
        Enemy[i]->AddComponent("Transform", new TransComponent(Enemy[i]));
        //Enemy[i]->AddComponent("Sprite", new SpriteComponent(Enemy[i]));
        Enemy[i]->AddComponent("EnemyAnimation", new EnemyAnimationComponent(Enemy[i]));
        Enemy[i]->AddComponent("RigidBody", new RigidBodyComponent(Enemy[i]));
        Enemy[i]->AddComponent("Ai", new AiComponent(Enemy[i]));
        TransComponent* Enemy_trs = (TransComponent*)Enemy[i]->FindComponent("Transform");
        AiComponent* Enemy_state = (AiComponent*)Enemy[i]->FindComponent("Ai");

        EnemyAnimationComponent* Enemy_ani = (EnemyAnimationComponent*)Enemy[i]->FindComponent("EnemyAnimation");        
        Enemy_ani->ChangeAnimation("MeleeIdle", 1, 8, 8, 0.1);

        Enemy_state->SetTarget(player);//�����߿� trager���� ���� ���� ���ش� �׸��� ���� palyer���� ������ش�.
        Enemy_state->Setdir(true);//true�� ������, false�� ����
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
        //EnemySniper[i]->AddComponent("Sprite", new SpriteComponent(EnemySniper[i]));
        EnemySniper[i]->AddComponent("EnemyAnimation", new EnemyAnimationComponent(EnemySniper[i]));
        EnemySniper[i]->AddComponent("RigidBody", new RigidBodyComponent(EnemySniper[i]));
        EnemySniper[i]->AddComponent("Ai", new AiComponent(EnemySniper[i]));
        AiComponent* EnemySniper_state = (AiComponent*)EnemySniper[i]->FindComponent("Ai");
        EnemyAnimationComponent* Enemy_sniperani = (EnemyAnimationComponent*)EnemySniper[i]->FindComponent("EnemyAnimation");
        //Enemy_sniperani->ChangeAnimation("SniperIdle", 1, 12, 12, 0.1);
        EnemySniper_state->SetTarget(player);//�����߿� trager���� ���� ���� ���ش� �׸��� ���� palyer���� ������ش�.
        EnemySniper_state->Setdir(true);//true�� ������, false�� ����
        EnemySniper_state->Setdir_time(1.0f);
        EnemySniper_state->SetState("IDLE_Sniper", "Sniper");
    }

    CameraManager::GetInst()->SetMouse(mouseAim);
    CameraManager::GetInst()->SetPlayer(player);

    //Audio Init    
    bgm = ResourceManager::GetInst()->Get("bgm", "Assets/BGM01.mp3");
    bgm_res = static_cast<AudioResource*>(bgm);        
    bgm_res->PlayMusicOrSFX(bgm_res, Sound::MUSIC, bgm_volume, bgm_pitch, -1);
    Level::StageBoss_Lvl::Stage2 = false;
}

void Level::Stage01_Lvl::Update()
{                   
    TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
    RigidBodyComponent* player_rig = (RigidBodyComponent*)player->FindComponent("RigidBody");
    PlayerComponent* player_comp = (PlayerComponent*)player->FindComponent("PlayerComp"); 
    float dt = AEFrameRateControllerGetFrameTime();
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
    else if(player_comp->GetTriggeredButton()==true)
    {
        float vol = bgm_res->GetPitch();
        if (vol <= 1.0)
        {
            bgm_res->SetPitch(vol + dt);
            AEAudioSetGroupPitch(bgm_res->GetAudioGroup(), bgm_res->GetPitch());
        }
    }


    TransComponent* bg_trs = (TransComponent*)background->FindComponent("Transform");
    bg_trs->SetPos(player_trs->GetPos());
    bg_trs->SetScale({ 1600,900 });

    AEInputShowCursor(0);
    //Component Pointer
    
    Collision();
    
    if(player_comp->GetObtain())
    {
        auto pFont = static_cast<TextResource*>(ResourceManager::GetInst()->Get("esamanru","Assets/esamanru-Bold.ttf"));
        std::string str1 = std::to_string(GetBullet());
        std::string str2 = "Bullet: ";
        const char* cstr1 = str1.c_str();
        const char* cstr2 = str2.c_str();
    
        AEGfxPrint(pFont->GetFont(), cstr1, -0.85, 0.8, 20/72.f, 1, 1, 1, 1);
        AEGfxPrint(pFont->GetFont(), cstr2, -0.95, 0.8, 20/72.f, 1, 1, 1, 1);
    }
    
    
    if(player_trs->GetPos().y<-1800)
        player_comp->SetHealth(-1);
    
    
    
    //�е��� ���� 
    if (IsVibration == false)
    {
        CameraManager::GetInst()->Update();
    }
    else
    {
        float deltaTime = AEFrameRateControllerGetFrameTime();
        AccTime += deltaTime;
        f32 playerPosX = player_trs->GetPos().x;
        f32 playerPosY = player_trs->GetPos().y;
        if (IsVibration && AccTime >= 0 && AccTime < 0.1)
        {
           minusX += -10 * deltaTime;
           minusY +=  10 * deltaTime;
           playerPosX += minusX;
           playerPosY += minusY;
           AEGfxSetCamPosition(playerPosX, playerPosY);
        }
        else if (IsVibration && AccTime >= 0.1&& AccTime < 0.2)
        {
            plusX +=  10*deltaTime;
            plusY += -10*deltaTime;
            playerPosX += plusX;
            playerPosY += plusY;
            AEGfxSetCamPosition(playerPosX, playerPosY);
        }
        else if (IsVibration && AccTime >= 0.2 && AccTime < 0.3)
        {
            minusX += -10*deltaTime;
            minusY +=  10*deltaTime;
            playerPosX += minusX;
            playerPosY += minusY;
            AEGfxSetCamPosition(playerPosX, playerPosY);
        }       
        else if (IsVibration && AccTime >= 0.3)
        {
            AEGfxSetCamPosition(player_trs->GetPos().x, player_trs->GetPos().y);
            AccTime = 0.f;
            IsVibration = false;
        }
    }
    
    
    
    //��������
    if ((player_trs->GetPos().x>-3000 && player_trs->GetPos().x < 5000 )&&player_trs->GetPos().y < -1800)
    {        
        player_comp->SetHealth(-1);
    }
    else  if (player_trs->GetPos().x >= 5000 &&player_trs->GetPos().y < -900)
    {
        player_comp->SetHealth(-1);
    }    
    
    //���� ���� ����
    if (player_trs->GetPos().x >= 11170)
    {
        GSM::GameStateManager::GetInst()->ChangeLevel(new Level::StageBoss_Lvl);
        return;
    }
    
    
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
    
    if (AEInputCheckTriggered(AEVK_ESCAPE))
    {
        AEInputShowCursor(1);
        AEGfxSetCamPosition(0.f,0.f);
        GSM::GameStateManager::GetInst()->ChangeLevel(new MainMenu_Lvl);
    }
      
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
    TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
    PlayerComponent* player_comp = (PlayerComponent*)player->FindComponent("PlayerComp");
    
    
      
    //Collision       
    for (auto obj : GoManager::GetInst()->Allobj())
    {
        //Platform
        if (obj->GetName() == "Platform")//IsCollision
        {
            //�÷��̾� �÷��� �浹ó��
            //with Player
            if (ColliderManager::GetInst()->IsCollision(player, obj))
            {
                HandleCollision(player, obj);
            }
            //Enemy �÷��� �浹ó��
            for (int i = 0; i < Enemy.size(); i++)
            {
                if (ColliderManager::GetInst()->IsCollision(Enemy[i], obj))
                {
                    HandleCollision(Enemy[i], obj);
                    //AI COMP������ ���ְ�
                    Enemy_Platform_Collision_Event* e_p_c_e = new Enemy_Platform_Collision_Event(obj, Enemy[i]);
                    EventManager::GetInst()->AddEvent(e_p_c_e);
                    
                }               
            }
            //EnemySniper �÷��� �浹ó��
            for (int i = 0; i < EnemySniper.size(); i++)
            {
                if (ColliderManager::GetInst()->IsCollision(EnemySniper[i], obj))
                {
                    HandleCollision(EnemySniper[i], obj);
                }
            }           
            //�Ѿ� �÷��� �浹ó��
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
        //�е� (�ݻ�)
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
                    AEVec2 nor_dVec{ 0,0 };
                    AEVec2Normalize(&nor_dVec, &bulletVec);
                    AEVec2Scale(&nor_dVec, &nor_dVec, -1);
                                        
                    bullet_comp->SetBulletVec(nor_dVec);
                    IsVibration = true;                                    
                    
                    auto res_padding = ResourceManager::GetInst()->Get("sfx_padding1", "Assets/padding2.wav");      
                    AudioResource* bgm_res = static_cast<AudioResource*>(res_padding);
                    bgm_res->PlayMusicOrSFX(bgm_res, Sound::SFX, 1.f, 1.f, 0);
                }
            }
           //Player Death
           //���ο� Collision box���
            if (ColliderManager::GetInst()->handle_Player_EnemyAtk_Collision(player, obj) && !player_comp->GetInvincible())
            {               

               //BulletComponent* bullet_comp = (BulletComponent*)obj->FindComponent("Bullet");

               //gameOver = true;
               player_comp->TakeDamge();
               //bullet_comp->DestroyBullet(); ��� �غ��� (������ ü�� 1�̴ϱ�)
                //audio
               auto resDead = ResourceManager::GetInst()->Get("sfx_PlayerDead", "Assets/Dead1.wav");               
               AudioResource* bgm_res = static_cast<AudioResource*>(resDead);
               bgm_res->PlayMusicOrSFX(bgm_res, Sound::SFX, 1.f, 1.f, 0);
            }
        }


        //Sniper�״�����
        if (obj->GetName() == "EnemySniper")
        {           
            int SniperObjID = 0;
            //Test: Collision Enemy with Player's Bullet
            for (auto findObj : GoManager::GetInst()->Allobj())
            {
                //�Ѿ˷� ������
                if (findObj->GetName() == "PlayerBullet" || findObj->GetName() == "EnemyBullet")
                {
                    if (ColliderManager::GetInst()->IsCollision(findObj, obj))
                    {
                        SniperObjID = obj->GetID();

                        //Create Gun && Bullet
                        TransComponent* EnemyMelee_trs = static_cast<TransComponent*>(EnemySniper[SniperObjID]->FindComponent("Transform"));
                        if (!player_comp->GetObtain())
                        {
                            CreateGun(EnemyMelee_trs->GetPos());
                        }
                        if (player_comp->GetObtain())
                        {
                            CreateSupplement(EnemyMelee_trs->GetPos());
                        }
                        //===========================

                        BulletComponent* bullet_comp = (BulletComponent*)findObj->FindComponent("Bullet");
                        if (!bullet_comp->EnemyShoot)
                        {
                            EnemySniper[SniperObjID]->SetActive(false);
                            EnemySniper[SniperObjID] = nullptr; 
                            
                            auto resSniperDead = ResourceManager::GetInst()->Get("sfx_SniperDeadToBullet", "Assets/Dead2.mp3");                            
                            AudioResource* bgm_res = static_cast<AudioResource*>(resSniperDead);
                            bgm_res->SetSFXorMusic(Sound::SFX);
                            auto bgm_audio = bgm_res->GetAudio();
                            auto bgm_audioGroup = bgm_res->GetAudioGroup();
                            AEAudioPlay(bgm_audio, bgm_audioGroup, 1.f, 1.f, 0);
                        }
                        bullet_comp->DestroyBullet();
                    }
                }             
            }
            //�÷��̾��� �и��������� �������۰� ������
            if (ColliderManager::GetInst()->IsCollision(player_comp->GetMelee(), obj))
            {
                SniperObjID = obj->GetID();

                //Create Gun && Bullet
                TransComponent* EnemyMelee_trs = static_cast<TransComponent*>(EnemySniper[SniperObjID]->FindComponent("Transform"));
                if (!player_comp->GetObtain())
                {
                    CreateGun(EnemyMelee_trs->GetPos());
                }
                if (player_comp->GetObtain())
                {
                    CreateSupplement(EnemyMelee_trs->GetPos());
                }
                //========================

                EnemySniper[SniperObjID]->SetActive(false);
                EnemySniper[SniperObjID] = nullptr;

                auto resDeadfromMelee = ResourceManager::GetInst()->Get("sfx_SniperDeadToMelee", "Assets/kill2.wav");
                AudioResource* bgm_res = static_cast<AudioResource*>(resDeadfromMelee);
                bgm_res->SetSFXorMusic(Sound::MUSIC);
                auto bgm_audio = bgm_res->GetAudio();
                auto bgm_audioGroup = bgm_res->GetAudioGroup();
                AEAudioPlay(bgm_audio, bgm_audioGroup, 1.f, 1.f, 0);
            }
        }        
        if (obj->GetName() == "Enemy") 
        {    
            //�Ѿ˺κ�
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
                            //Create Gun && Bullet
                            TransComponent* EnemyMelee_trs = static_cast<TransComponent*>(Enemy[meeleObjID]->FindComponent("Transform"));
                            if (!player_comp->GetObtain())
                            {
                                CreateGun(EnemyMelee_trs->GetPos());
                            }
                            if (player_comp->GetObtain())
                            {
                                CreateSupplement(EnemyMelee_trs->GetPos());
                            }
                            //================================

                            Enemy[meeleObjID]->SetActive(false);
                            Enemy[meeleObjID] = nullptr;
                            bullet_comp->DestroyBullet();

                            auto res = ResourceManager::GetInst()->Get("sfx_EnemyDeadToBullet", "Assets/Dead2.mp3");
                            AudioResource* bgm_res = static_cast<AudioResource*>(res);
                            bgm_res->PlayMusicOrSFX(bgm_res, Sound::SFX, 1.0f, 1.0f, 0.f);
                        }
                    }
                }
            }
            //����
            if (ColliderManager::GetInst()->IsCollision(player_comp->GetMelee(), obj)) 
            {
                 meeleObjID = obj->GetID();

                //Create Gun && Bullet
                TransComponent* EnemyMelee_trs = static_cast<TransComponent*>(Enemy[meeleObjID]->FindComponent("Transform"));
                if (!player_comp->GetObtain())
                {
                    CreateGun(EnemyMelee_trs->GetPos());
                }
                if (player_comp->GetObtain())
                {
                    CreateSupplement(EnemyMelee_trs->GetPos());
                }
                //==========================

                Enemy[meeleObjID]->SetActive(false);
                Enemy[meeleObjID] = nullptr;
             
                //audio
                auto res = ResourceManager::GetInst()->Get("sfx_EnemyDeadToMelee", "Assets/kill1.mp3");
                AudioResource* sfx_res = static_cast<AudioResource*>(res);
                sfx_res->PlayMusicOrSFX(sfx_res, Sound::SFX, 1.0f, 1.0f, 0.f);
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

//�ٴ��̶� obj Collision�̸鼭 ��ġ����
void Level::Stage01_Lvl::HandleCollision(GameObject* obj1, GameObject* obj2)
{
    // Transform �� RigidBody ������Ʈ ��������
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