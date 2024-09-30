#include "StageTutorial.h"
#include "GameObject.h"
#include "GameStateManager.h"
#include  "GoManager.h"
#include "TransComponent.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "ImageResource.h"
#include "Resource.h"
#include "Stage01_Lvl.h"
#include "AudioResource.h"
#include "EventManager.h"
#include "PlayerComponent.h"
#include "Serializer.h"
#include "TextResource.h"
#include "AiComponent.h"
#include "EnemyAnimationComponent.h"
#include "Bullet.h"
#include "AnimationComponent.h"
#include "BulletComponent.h"
#include "CameraManager.h"
#include "ColliderManager.h"
#include "RigidBodyComponent.h"

Level::StageTutorial_Lvl::StageTutorial_Lvl()
{    
}

Level::StageTutorial_Lvl::~StageTutorial_Lvl()
{
}

void Level::StageTutorial_Lvl::Init()
{
    //Object and Component Init
    ResourceManager::GetInst()->Get("MeleeIdle", "Assets/meleeEnemyIdle.png");
    ResourceManager::GetInst()->Get("MeleeChase", "Assets/meleeEnemyChase.png");
    ResourceManager::GetInst()->Get("MeleeAttack", "Assets/meleeEnemyAtk.png");//("MeleeAttack", 1, 5, 5, 0.1);
    ResourceManager::GetInst()->Get("SniperIdle", "Assets/sniperEnemyIdle.png");//12
    ResourceManager::GetInst()->Get("SniperShootIdle", "Assets/sniperEnemyShootIdle.png");//1
    ResourceManager::GetInst()->Get("SniperShoot", "Assets/sniperEnemyShoot.png");//5

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

    //player
    player = new GameObject("Player");
    GoManager::GetInst()->AddObject(player); //GetInst() == GetPtr()
    player->AddComponent("Transform", new TransComponent(player));
    //player->AddComponent("Sprite", new SpriteComponent(player));
    player->AddComponent("PlayerComp", new PlayerComponent(player));
    player->AddComponent("Animation", new AnimationComponent(player));
    player_trs = (TransComponent*)player->FindComponent("Transform");
    player_trs->SetScale({ 80, 80 });            

    //PlayerAim
    aimTrace = new GameObject("aimTrace");
    GoManager::GetInst()->AddObject(aimTrace);
    aimTrace->AddComponent("Transform", new TransComponent(aimTrace));
    aimTrace->AddComponent("Sprite", new SpriteComponent(aimTrace));


    //GameObject* EnemySniper=new GameObject("EnemySniper");
    //EnemySniper->SetID(0);
    //GoManager::GetInst()->AddObject(EnemySniper);
    //EnemySniper->AddComponent("Transform", new TransComponent(EnemySniper));
    ////Enemy->AddComponent("Sprite", new SpriteComponent(Enemy));
    //EnemySniper->AddComponent("EnemyAnimation", new EnemyAnimationComponent(EnemySniper));
    //EnemySniper->AddComponent("RigidBody", new RigidBodyComponent(EnemySniper));
    //EnemySniper->AddComponent("Ai", new AiComponent(EnemySniper));
    //TransComponent* Enemy_trs = (TransComponent*)EnemySniper->FindComponent("Transform");
    //AiComponent* Enemy_state = (AiComponent*)EnemySniper->FindComponent("Ai");
    //
    //EnemyAnimationComponent* Enemy_ani = (EnemyAnimationComponent*)EnemySniper->FindComponent("EnemyAnimation");
    //Enemy_ani->ChangeAnimation("SniperIdle", 1, 12, 12, 0.1);
    //
    //Enemy_state->SetTarget(player);//순서중요 trager부터 먼저 세팅 해준다 그리고 먼저 palyer부터 만들어준다.
    //Enemy_state->Setdir(true);//true가 오른쪽, false가 왼쪽
    //Enemy_state->Setdir_time(2.0f);
    //Enemy_state->SetFirstPlace(Enemy_trs->GetPos());
    //Enemy_state->SetState("IDLE_Sniper", "Sniper");



    //Serializer    
    Serializer::GetInst()->LoadLevel("Assets/stageTutorial.json");
    //Serializer::GetInst()->SaveEnemy("Assets/stageTutorial_Enemy.json");
    //Serializer::GetInst()->SaveEnemySniper("Assets/stageTutorial_EnemySniper.json");
    //Serializer::GetInst()->LoadEnemy("Assets/stageTutorial_Enemy.json");        
    //Serializer::GetInst()->LoadEnemySniper("Assets/stageTutorial_EnemySniper.json");
    

    for (int i = 0; i <Enemy.size(); i++)
    {
        Enemy[i] = Serializer::GetInst()->LoadEnemy("Assets/stageTutorial_Enemy.json");
        TransComponent* enemy_trs=static_cast<TransComponent*>(Enemy[i]->FindComponent("Transform"));
        RigidBodyComponent* enemy_rg= static_cast<RigidBodyComponent*>(Enemy[i]->FindComponent("RigidBody"));
        EnemyAnimationComponent* enemy_ani = static_cast<EnemyAnimationComponent*>(Enemy[i]->FindComponent("EnemyAnimation"));
        //AiComponent* enemy_ai = static_cast<AiComponent*>(Enemy[i]->FindComponent("Ai"));
        Enemy[i]->SetID(i);
        Enemy[i]->SetName("Enemy");
        switch (i)
        {
        case 0:
            enemy_trs->SetPos({ 3200,120 });
            enemy_ani->ChangeAnimation("MeleeIdle", 1, 8, 8, 0.1f);
            //enemy_ai->SetTarget(player);//순서중요 trager부터 먼저 세팅 해준다 그리고 먼저 palyer부터 만들어준다.
            //enemy_ai->Setdir(true);//true가 오른쪽, false가 왼쪽
            //enemy_ai->Setdir_time(2.0f);
            //enemy_ai->SetFirstPlace(enemy_trs->GetPos());
            //enemy_ai->SetState("IDLE", "Melee");
            break;
        case 1:
            enemy_trs->SetPos({ 3900,120 });
            enemy_ani->ChangeAnimation("MeleeIdle", 1, 8, 8, 0.1f);
            //enemy_ai->SetTarget(player);//순서중요 trager부터 먼저 세팅 해준다 그리고 먼저 palyer부터 만들어준다.
            //enemy_ai->Setdir(true);//true가 오른쪽, false가 왼쪽
            //enemy_ai->Setdir_time(2.0f);
            //enemy_ai->SetFirstPlace(enemy_trs->GetPos());
            //enemy_ai->SetState("IDLE", "Melee");
            break;
        case 2:
            enemy_trs->SetPos({ 4700,120 });
            enemy_ani->ChangeAnimation("MeleeIdle", 1, 8, 8, 0.1f);
            //enemy_ai->SetTarget(player);//순서중요 trager부터 먼저 세팅 해준다 그리고 먼저 palyer부터 만들어준다.
            //enemy_ai->Setdir(true);//true가 오른쪽, false가 왼쪽
            //enemy_ai->Setdir_time(2.0f);
            //enemy_ai->SetFirstPlace(enemy_trs->GetPos());
            //enemy_ai->SetState("IDLE", "Melee");
            break;
        }
    }
    
    for (int i = 0; i < EnemySniper.size(); i++)
    {
        EnemySniper[i] = Serializer::GetInst()->LoadEnemySniper("Assets/stageTutorial_EnemySniper.json");
        TransComponent* enemy_trs = static_cast<TransComponent*>(EnemySniper[i]->FindComponent("Transform"));
        RigidBodyComponent* enemy_rg = static_cast<RigidBodyComponent*>(EnemySniper[i]->FindComponent("RigidBody"));
        EnemyAnimationComponent* enemy_ani = static_cast<EnemyAnimationComponent*>(EnemySniper[i]->FindComponent("EnemyAnimation"));
        AiComponent* enemy_ai = static_cast<AiComponent*>(EnemySniper[i]->FindComponent("Ai"));
        EnemySniper[i]->SetID(i);
        EnemySniper[i]->SetName("EnemySniper");
        switch (i)
        {
        case 0:
            enemy_trs->SetPos({ 7800,100 });
            //enemy_ani->ChangeAnimation("SniperIdle", 1, 12, 12, 0.1);
            enemy_ai->SetTarget(player);//순서중요 trager부터 먼저 세팅 해준다 그리고 먼저 palyer부터 만들어준다.
            enemy_ai->Setdir(true);//true가 오른쪽, false가 왼쪽
            enemy_ai->Setdir_time(1.0f);            
            enemy_ai->SetState("IDLE_Sniper", "Sniper");
            break;
        case 1:
            enemy_trs->SetPos({ 8340,100 });
            //enemy_ani->ChangeAnimation("SniperIdle", 1, 12, 12, 0.1);
            enemy_ai->SetTarget(player);//순서중요 trager부터 먼저 세팅 해준다 그리고 먼저 palyer부터 만들어준다.
            enemy_ai->Setdir(true);//true가 오른쪽, false가 왼쪽
            enemy_ai->Setdir_time(1.0f);            
            enemy_ai->SetState("IDLE_Sniper", "Sniper");
            break;
        }
    }

    
   
    //Camera
    CameraManager::GetInst()->SetMouse(mouseAim);
    CameraManager::GetInst()->SetPlayer(player);
    CameraManager::GetInst()->SetAim(aimTrace);

    //Audio
    /*bgm = ResourceManager::GetInst()->Get("BossBGM", "Assets/BossBgm.mp3");
    bgm_res = static_cast<AudioResource*>(bgm);
    bgm_res->PlayMusicOrSFX(bgm_res, Sound::MUSIC, 1.0f, 1.0f, -1);    */

    const std::vector<GameObject*> all_objs = GoManager::GetInst()->Allobj();

    for (auto platform : all_objs)
    {
        if (
            platform->GetName() == "Platform")
        {
            if (platform->GetID() == 10)
            {
                platform_attack = platform;
            }
            else if (platform->GetID() == 8)
            {
                platform_move = platform;
            }
            else if (platform->GetID() == 17)
            {
                platform_time = platform;
            }
        }
    }

    player_trs = (TransComponent*)player->FindComponent("Transform");
    player_rig = (RigidBodyComponent*)player->FindComponent("RigidBody");
    player_comp = (PlayerComponent*)player->FindComponent("PlayerComp");
    player_comp->SetIsTutorialStage(true);

    bg_trs = (TransComponent*)background->FindComponent("Transform");
}


void Level::StageTutorial_Lvl::Update()
{
   
    bg_trs->SetPos(player_trs->GetPos());
    bg_trs->SetScale({ 1600,900 });
    
    AEInputShowCursor(0);
    
    f32 dt = static_cast<f32>(AEFrameRateControllerGetFrameTime());
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
    
    GoManager::GetInst()->RemoveDeathObj();

    //Display Bullet===============
    //auto pFont = static_cast<TextResource*>(ResourceManager::GetInst()->Get("esamanru", "Assets/esamanru-Bold.ttf"));
    //std::string str1 = std::to_string(GetBullet());
    //std::string str2 = "Bullet: ";
    //const char* cstr1 = str1.c_str();
    //const char* cstr2 = str2.c_str();
    //
    //AEGfxPrint(pFont->GetFont(), cstr1, -0.85, 0.8, 20 / 72.f, 1, 1, 1, 1);
    //AEGfxPrint(pFont->GetFont(), cstr2, -0.95, 0.8, 20 / 72.f, 1, 1, 1, 1);
    

    //tutorial
    static bool MovementTutorial = false;
    static bool AttackTutorial = false;
    static bool ParringAndTimeManiTutorial = false;
    if (player_trs->GetPos().x < 2000)
    {
        player_comp->SetIsMovementTutorial(true);        
    }   

    if (player_trs->GetPos().x >= 1400 && player_trs->GetPos().y >= 950&&MovementTutorial==false)
    {
        MovementTutorial = true;
        player_comp->SetDoNotMove(true);        
    }

    if (player_trs->GetPos().x >= 2300)
    {
        player_comp->SetIsAttackTutorial(true);
    }


    if (player_trs->GetPos().x >= 5500 && EnemyDeathCnt <= 0 && AttackTutorial == false)
    {
        AttackTutorial = true;
        player_comp->SetDoNotMove(true);
        SetMoveAccTime(0.f);
    }

    if (AttackTutorial == true)
    {

        for (auto platform : GoManager::GetInst()->Allobj())
        {
            if (platform->GetName() == "Platform")
            {
                if (platform->GetID() == 10)
                {
                    TransComponent* platform_trs = (TransComponent*)platform->FindComponent("Transform");
                    AEVec2 plat_pos = platform_trs->GetPos();
                    AEVec2 plat_scale = platform_trs->GetScale();
                    plat_pos.y -= dt * 500.f;
                    platform_trs->SetPos({ plat_pos.x,plat_pos.y });
                }
            }
        }

    }

    if (player_comp->GetDoNotMove() == true)
    {
        AddMoveAccTime(dt);
        SetVibration(true);
        if (GetMoveAccTime() >= 3.0f)
        {
            player_comp->SetDoNotMove(false);
            SetVibration(false);
        }
    }
    
    if (MovementTutorial == true)
    {

        for (auto platform : GoManager::GetInst()->Allobj())
        {
            if (platform->GetName() == "Platform")
            {
                if (platform->GetID() == 8)
                {
                    TransComponent* platform_trs = (TransComponent*)platform->FindComponent("Transform");
                    AEVec2 plat_pos = platform_trs->GetPos();
                    AEVec2 plat_scale = platform_trs->GetScale();
                    plat_pos.y -= dt * 650.f;
                    platform_trs->SetPos({ plat_pos.x,plat_pos.y });
                }
            }
        }
    }  

    if (player_trs->GetPos().x >= 5500 && EnemyDeathCnt <= 0 && AttackTutorial == false)
    {
        AttackTutorial = true;
        player_comp->SetDoNotMove(true);
        SetMoveAccTime(0.f);
    }

    if (AttackTutorial == true)
    {
        for (auto platform : GoManager::GetInst()->Allobj())
        {
            if (platform->GetName() == "Platform")
            {
                if (platform->GetID() == 10)
                {
                    TransComponent* platform_trs = (TransComponent*)platform->FindComponent("Transform");
                    AEVec2 plat_pos = platform_trs->GetPos();
                    AEVec2 plat_scale = platform_trs->GetScale();
                    plat_pos.y -= dt * 500.f;
                    platform_trs->SetPos({ plat_pos.x,plat_pos.y });
                }
            }
        }
    }


    if (player_trs->GetPos().x >= 6800)
    {
        player_comp->SetIsTimeManipulateTutorial(true);        
    }

    
    if (EnemySniperDeathCnt <= 0)
    {
        for (auto platform : GoManager::GetInst()->Allobj())
        {
            if (platform->GetName() == "Platform")
            {
                if (platform->GetID() == 17)
                {
                    TransComponent* platform_trs = (TransComponent*)platform->FindComponent("Transform");
                    AEVec2 plat_pos = platform_trs->GetPos();
                    AEVec2 plat_scale = platform_trs->GetScale();
                    plat_scale.x -= dt * 100;
                    platform_trs->SetScale({ plat_scale.x,plat_pos.y });
                    if (plat_scale.x <= 0)
                        platform_trs->SetPos(-5000.f, -5000.f);//ㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋㅋ
                }
            }
        }
    }
    

    if (IsVibration == false)
    {
        CameraManager::GetInst()->Update();
    }
    else
    {
        f32 deltaTime = static_cast<f32>(AEFrameRateControllerGetFrameTime());
        AccTime += deltaTime;
        f32 playerPosX = player_trs->GetPos().x;
        f32 playerPosY = player_trs->GetPos().y;
        if (IsVibration && AccTime >= 0 && AccTime < 0.1)
        {
            minusX += -10 * deltaTime;
            minusY += 10 * deltaTime;
            playerPosX += minusX;
            playerPosY += minusY;
            AEGfxSetCamPosition(playerPosX, playerPosY);
        }
        else if (IsVibration && AccTime >= 0.1 && AccTime < 0.2)
        {
            plusX += 10 * deltaTime;
            plusY += -10 * deltaTime;
            playerPosX += plusX;
            playerPosY += plusY;
            AEGfxSetCamPosition(playerPosX, playerPosY);
        }
        else if (IsVibration && AccTime >= 0.2 && AccTime < 0.3)
        {
            minusX += -10 * deltaTime;
            minusY += 10 * deltaTime;
            playerPosX += minusX;
            playerPosY += minusY;
            AEGfxSetCamPosition(playerPosX, playerPosY);
        }
        else if (IsVibration && AccTime >= 0.3)
        {
            AEGfxSetCamPosition(player_trs->GetPos().x, player_trs->GetPos().y);                       
            
            plusX = 0.f;
            plusY = 0.f;
            minusX = 0.f;
            minusY = 0.f;

            AccTime = 0.f;

            IsVibration = false;
        }
    }

    Collision();
    
        
    if (player_trs->GetPos().x >= 8900 && player_trs->GetPos().y <= -1500 && EnemySniperDeathCnt <= 0)
    {
        GSM::GameStateManager::GetInst()->ChangeLevel(new Level::Stage01_Lvl);
        return;
    }
}

void Level::StageTutorial_Lvl::Exit()
{
    ResourceManager::GetInst()->RemoveAllRes();
    EventManager::GetInst()->RemoveAllEvent();
    GoManager::GetInst()->RemoveAllObj();
}


void Level::StageTutorial_Lvl::HandleCollision(GameObject* obj1, GameObject* obj2)
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
    else if (obj1->GetName() == "Player")
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


//Wall vs Player or Snper

void Level::StageTutorial_Lvl::Collision_WallvsPlayer(GameObject* wall, GameObject* p, bool b)
{
    if (p->GetName() == "Platform")
    {
        return;
    }

    if (ColliderManager::GetInst()->IsCollision(wall, p))
    {
        BulletComponent* bullet_comp = (BulletComponent*)p->FindComponent("Bullet");

        if (bullet_comp)
            bullet_comp->DestroyBullet();
        else
            HandleCollision(p, wall);
         
        Enemy_Platform_Collision_Event* e_p_c_e = new Enemy_Platform_Collision_Event(wall, p);
        EventManager::GetInst()->AddEvent(e_p_c_e);
    }
}


void Level::StageTutorial_Lvl::Collision_Bullet_Parry(GameObject* bull, GameObject* p)

{
    //with Player's Melee ==> Parrying
    if (ColliderManager::GetInst()->IsCollision(p, bull))
    {
        BulletComponent* bullet_comp = (BulletComponent*)bull->FindComponent("Bullet");
        if (!bullet_comp->GetState())
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
}

void Level::StageTutorial_Lvl::Collision_Bullet_Player(GameObject* bull, GameObject* p)
{
    if (ColliderManager::GetInst()->handle_Player_EnemyAtk_Collision(p, bull) && !player_comp->GetInvincible())
    {
        //BulletComponent* bullet_comp = (BulletComponent*)obj->FindComponent("Bullet");

        //gameOver = true;
        player_comp->TakeDamge();
        //bullet_comp->DestroyBullet(); 고민 해보기 (어차피 체력 1이니까)
         //audio
        auto resDead = ResourceManager::GetInst()->Get("sfx_PlayerDead", "Assets/Dead1.wav");
        AudioResource* bgm_res = static_cast<AudioResource*>(resDead);
        bgm_res->PlayMusicOrSFX(bgm_res, Sound::SFX, 1.f, 1.f, 0);
    }
}


void Level::StageTutorial_Lvl::Collision()
{
    const std::vector<GameObject*> all_objs = GoManager::GetInst()->Allobj();
    TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
    PlayerComponent* player_comp = (PlayerComponent*)player->FindComponent("PlayerComp");



   

    //Collision       
    for (auto obj : all_objs)
    {
        //Platform
        if (obj->GetName() == "Platform")//IsCollision
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
            for (auto findObj : all_objs)
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
               if (!bullet_comp->GetState())
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
           //새로운 Collision box사용
           if (ColliderManager::GetInst()->handle_Player_EnemyAtk_Collision(player, obj) && !player_comp->GetInvincible())
           {
               auto resDead = ResourceManager::GetInst()->Get("sfx_PlayerDead", "Assets/Dead1.wav");
               AudioResource* bgm_res = static_cast<AudioResource*>(resDead);
               bgm_res->PlayMusicOrSFX(bgm_res, Sound::SFX, 1.f, 1.f, 0);
           }
        }


        //Sniper죽는판정
        if (obj->GetName() == "EnemySniper")
         {
            int SniperObjID = 0;
            ////Test: Collision Enemy with Player's Bullet
            for (auto findObj : all_objs)
            {
                //총알로 죽을시
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
                            EnemySniperDeathCnt--;
            
                            auto resSniperDead = ResourceManager::GetInst()->Get("sfx_SniperDeadToBullet", "Assets/Dead2.mp3");
                            AudioResource* bgm_res = static_cast<AudioResource*>(resSniperDead);
                            bgm_res->PlayMusicOrSFX(bgm_res, Sound::SFX, 1.0f, 1.0f, 0);
                        }
                        bullet_comp->DestroyBullet();
                    }
                }
            }
            ////플레이어의 밀리어택으로 스나이퍼가 죽을시
            //if (ColliderManager::GetInst()->IsCollision(player_comp->GetMelee(), obj))
            //{
            //    SniperObjID = obj->GetID();
            //
            //    //Create Gun && Bullet
            //    TransComponent* EnemyMelee_trs = static_cast<TransComponent*>(EnemySniper[SniperObjID]->FindComponent("Transform"));
            //    if (!player_comp->GetObtain())
            //    {
            //        CreateGun(EnemyMelee_trs->GetPos());
            //    }
            //    if (player_comp->GetObtain())
            //    {
            //        CreateSupplement(EnemyMelee_trs->GetPos());
            //    }
            //    //========================
            //
            //    EnemySniper[SniperObjID]->SetActive(false);
            //    EnemySniper[SniperObjID] = nullptr;
            //    EnemySniperDeathCnt--;
            //}
        }
        
        if (obj->GetName() == "Enemy")
        {
            //총알부분
            int meeleObjID = 0;
            for (auto findObj : all_objs)
            {
                if (findObj->GetName() == "PlayerBullet" || findObj->GetName() == "EnemyBullet")
                {
                    if (ColliderManager::GetInst()->IsCollision(findObj, obj))
                    {
                        meeleObjID = obj->GetID();
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
                            EnemyDeathCnt--;
                            bullet_comp->DestroyBullet();

                            auto res = ResourceManager::GetInst()->Get("sfx_EnemyDeadToBullet", "Assets/Dead2.mp3");
                            AudioResource* bgm_res = static_cast<AudioResource*>(res);
                            bgm_res->PlayMusicOrSFX(bgm_res, Sound::SFX, 1.0f, 1.0f, 0);
                        }
                    }
                }
            }
            //근접
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
                EnemyDeathCnt--;
                //audio
                auto res = ResourceManager::GetInst()->Get("sfx_EnemyDeadToMelee", "Assets/kill1.mp3");
                AudioResource* sfx_res = static_cast<AudioResource*>(res);
                sfx_res->PlayMusicOrSFX(sfx_res, Sound::SFX, 1.0f, 1.0f, 0);
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
