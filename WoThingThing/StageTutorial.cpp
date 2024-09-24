#include "StageTutorial.h"
#include "GameObject.h"
#include "GameStateManager.h"
#include  "GoManager.h"
#include "TransComponent.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "ImageResource.h"
#include "Resource.h"
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
    ResourceManager::GetInst()->Get("BackgroundImg", "Assets/BossBackgroundImage.png");
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
    TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
    player_trs->SetScale({ 80, 80 });

    //PlayerAim
    aimTrace = new GameObject("aimTrace");
    GoManager::GetInst()->AddObject(aimTrace);
    aimTrace->AddComponent("Transform", new TransComponent(aimTrace));
    aimTrace->AddComponent("Sprite", new SpriteComponent(aimTrace));


    //GameObject* Enemy=new GameObject("Enemy");
    //Enemy->SetID(0);
    //GoManager::GetInst()->AddObject(Enemy);
    //Enemy->AddComponent("Transform", new TransComponent(Enemy));
    ////Enemy->AddComponent("Sprite", new SpriteComponent(Enemy));
    //Enemy->AddComponent("EnemyAnimation", new EnemyAnimationComponent(Enemy));
    //Enemy->AddComponent("RigidBody", new RigidBodyComponent(Enemy));
    //Enemy->AddComponent("Ai", new AiComponent(Enemy));
    //TransComponent* Enemy_trs = (TransComponent*)Enemy->FindComponent("Transform");
    //AiComponent* Enemy_state = (AiComponent*)Enemy->FindComponent("Ai");
    //
    //EnemyAnimationComponent* Enemy_ani = (EnemyAnimationComponent*)Enemy->FindComponent("EnemyAnimation");   
    //Enemy_ani->ChangeAnimation("MeleeIdle", 1, 8, 8, 0.1);
    //
    //Enemy_state->SetTarget(player);//순서중요 trager부터 먼저 세팅 해준다 그리고 먼저 palyer부터 만들어준다.
    //Enemy_state->Setdir(true);//true가 오른쪽, false가 왼쪽
    //Enemy_state->Setdir_time(2.0f);
    //Enemy_state->SetFirstPlace(Enemy_trs->GetPos());
    //Enemy_state->SetState("IDLE", "Melee");

    //Serializer
    Serializer::GetInst()->LoadLevel("Assets/stageTutorial.json");
    //Serializer::GetInst()->SaveEnemy("Assets/stageTutorial_Enemy.json");
    Serializer::GetInst()->LoadEnemy("Assets/stageTutorial_Enemy.json");    
    
    for (int i = 0; i <5; i++)
    {
        GameObject* enemy=Serializer::GetInst()->LoadEnemy("Assets/stageTutorial_Enemy.json");
        TransComponent* enemy_trs=static_cast<TransComponent*>(enemy->FindComponent("Transform"));
        RigidBodyComponent* enemy_rg= static_cast<RigidBodyComponent*>(enemy->FindComponent("RigidBody"));
        EnemyAnimationComponent* enemy_ani = static_cast<EnemyAnimationComponent*>(enemy->FindComponent("EnemyAnimation"));
        AiComponent* enemy_ai = static_cast<AiComponent*>(enemy->FindComponent("Ai"));
        enemy->SetID(i);

        if (i == 0)
        {
            enemy_trs->SetPos({ 300,120 });
            enemy_ani->ChangeAnimation("MeleeIdle", 1, 8, 8, 0.1);
            enemy_ai->SetTarget(player);//순서중요 trager부터 먼저 세팅 해준다 그리고 먼저 palyer부터 만들어준다.
            enemy_ai->Setdir(true);//true가 오른쪽, false가 왼쪽
            enemy_ai->Setdir_time(2.0f);
            enemy_ai->SetFirstPlace(enemy_trs->GetPos());
            enemy_ai->SetState("IDLE", "Melee");
        }
            
    }


   
    //Camera
    CameraManager::GetInst()->SetMouse(mouseAim);
    CameraManager::GetInst()->SetPlayer(player);
    CameraManager::GetInst()->SetAim(aimTrace);

    //Audio
    bgm = ResourceManager::GetInst()->Get("BossBGM", "Assets/BossBgm.mp3");
    bgm_res = static_cast<AudioResource*>(bgm);
    bgm_res->PlayMusicOrSFX(bgm_res, Sound::MUSIC, 1.0f, 1.0f, -1);
}


void Level::StageTutorial_Lvl::Update()
{
    TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
    RigidBodyComponent* player_rig = (RigidBodyComponent*)player->FindComponent("RigidBody");
    PlayerComponent* player_comp = (PlayerComponent*)player->FindComponent("PlayerComp");

    TransComponent* bg_trs = (TransComponent*)background->FindComponent("Transform");
    bg_trs->SetPos(player_trs->GetPos());
    bg_trs->SetScale({ 1600,900 });
    
    AEInputShowCursor(0);

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
    auto pFont = static_cast<TextResource*>(ResourceManager::GetInst()->Get("esamanru", "Assets/esamanru-Bold.ttf"));
    std::string str1 = std::to_string(GetBullet());
    std::string str2 = "Bullet: ";
    const char* cstr1 = str1.c_str();
    const char* cstr2 = str2.c_str();

    AEGfxPrint(pFont->GetFont(), cstr1, -0.85, 0.8, 20 / 72.f, 1, 1, 1, 1);
    AEGfxPrint(pFont->GetFont(), cstr2, -0.95, 0.8, 20 / 72.f, 1, 1, 1, 1);

    CameraManager::GetInst()->Update();

    Collision();

    std::cout << player_trs->GetPos().x << "," << player_trs->GetPos().y << std::endl;
    
}

void Level::StageTutorial_Lvl::Exit()
{
    auto res = ResourceManager::GetInst()->GetReource();
    ResourceManager::GetInst()->RemoveAllRes();
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

void Level::StageTutorial_Lvl::Collision()
{
    TransComponent* player_trs = (TransComponent*)player->FindComponent("Transform");
    PlayerComponent* player_comp = (PlayerComponent*)player->FindComponent("PlayerComp");



    //Collision       
    for (auto obj : GoManager::GetInst()->Allobj())
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
            //for (int i = 0; i < Enemy.size(); i++)
            //{
            //    if (ColliderManager::GetInst()->IsCollision(Enemy[i], obj))
            //    {
            //        HandleCollision(Enemy[i], obj);
            //        //AI COMP세팅을 해주고
            //        Enemy_Platform_Collision_Event* e_p_c_e = new Enemy_Platform_Collision_Event(obj, Enemy[i]);
            //        EventManager::GetInst()->AddEvent(e_p_c_e);

            //    }
            //}
            for (auto enemy : GoManager::GetInst()->Allobj())
            {
                if (ColliderManager::GetInst()->IsCollision(enemy, obj))
                {
                    if (enemy->GetID() == 0)
                    {
                        HandleCollision(enemy, obj);
                        //AI COMP세팅을 해주고
                        Enemy_Platform_Collision_Event* e_p_c_e = new Enemy_Platform_Collision_Event(obj, enemy);
                        EventManager::GetInst()->AddEvent(e_p_c_e);
                    }                    
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
