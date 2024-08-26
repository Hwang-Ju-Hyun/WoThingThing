#include "Stage01_Lvl.h"
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


Level::Stage01_Lvl::Stage01_Lvl()
{
}

Level::Stage01_Lvl::~Stage01_Lvl()
{
}

void Level::Stage01_Lvl::Init()
{
    //Object and Component Init
	player1 = new GameObject("Player1");
	player2 = new GameObject("Player2");
	ball    = new GameObject("Ball");
    goalPost1 = new GameObject("GoalPost1");
    goalPost2 = new GameObject("GoalPost2");
    UpperPost = new GameObject("UpperPost");
    DownPost = new GameObject("DownPost");

	GoManager::GetInst()->AddObject(player1);
	GoManager::GetInst()->AddObject(player2);
	GoManager::GetInst()->AddObject(ball);
    GoManager::GetInst()->AddObject(goalPost1);
    GoManager::GetInst()->AddObject(goalPost2);
    GoManager::GetInst()->AddObject(UpperPost);
    GoManager::GetInst()->AddObject(DownPost);

	player1->AddComponent("Transform", new TransComponent(player1));
	player1->AddComponent("Sprite", new SpriteComponent(player1));

	player2->AddComponent("Transform", new TransComponent(player2));
	player2->AddComponent("Sprite", new SpriteComponent(player2));

	ball->AddComponent("Transform", new TransComponent(ball));
	ball->AddComponent("Sprite", new SpriteComponent(ball));  
    ball->AddComponent("RigidBody", new RigidBodyComponent(ball));

    goalPost1->AddComponent("Transform", new TransComponent(goalPost1));
    goalPost1->AddComponent("Sprite", new SpriteComponent(goalPost1));

    goalPost2->AddComponent("Transform", new TransComponent(goalPost2));
    goalPost2->AddComponent("Sprite", new SpriteComponent(goalPost2));

    UpperPost->AddComponent("Transform", new TransComponent(UpperPost));
    UpperPost->AddComponent("Sprite", new SpriteComponent(UpperPost));

    DownPost->AddComponent("Transform", new TransComponent(DownPost));
    DownPost->AddComponent("Sprite", new SpriteComponent(DownPost));
    

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
    //Component 
	TransComponent* player1_trs = (TransComponent*)player1->FindComponent("Transform");    
	SpriteComponent* player1_spr = (SpriteComponent*)player1->FindComponent("Sprite");   

    TransComponent* player2_trs = (TransComponent*)player2->FindComponent("Transform");    
    SpriteComponent* player2_spr = (SpriteComponent*)player2->FindComponent("Sprite");

    TransComponent* ball_trs = (TransComponent*)ball->FindComponent("Transform");
    SpriteComponent* ball_spr = (SpriteComponent*)ball->FindComponent("Sprite");        
    RigidBodyComponent* ball_rb = (RigidBodyComponent*)ball->FindComponent("RigidBody");

    TransComponent* goalPost1_trs = (TransComponent*)goalPost1->FindComponent("Transform");
    SpriteComponent* goalPost1_spr = (SpriteComponent*)goalPost1->FindComponent("Sprite");

    TransComponent* goalPost2_trs = (TransComponent*)goalPost2->FindComponent("Transform");
    SpriteComponent* goalPost2_spr = (SpriteComponent*)goalPost2->FindComponent("Sprite");          

    TransComponent*  UpperPost_trs = (TransComponent*) UpperPost->FindComponent("Transform");
    SpriteComponent* UpperPost_spr = (SpriteComponent*)UpperPost->FindComponent("Sprite");

    TransComponent*  DownPost_trs = (TransComponent*) DownPost->FindComponent("Transform");
    SpriteComponent* DownPost_spr = (SpriteComponent*)DownPost->FindComponent("Sprite");


    //Score Text
    auto text_res = ResourceManager::GetInst()->Get("text", "Assets/liberation-mono.ttf");
    TextResource* ScoreText_res = static_cast<TextResource*>(text_res);
    ScoreText_res->SetText("Score");
    
    auto font = ScoreText_res->GetFont();
    auto text = ScoreText_res->GetText();
    auto height = ScoreText_res->GetHeight();
            

    //PlayerMovement
    for (auto player : GoManager::GetInst()->Allobj())
    {        
        if (player->GetName() == "Player1")
        {
            if (AEInputCheckCurr(AEVK_W))
            {                
                if(player1_trs->GetPos().y< 380)
                    player1_trs->AddPos(0.f, 10.f);                
            }
            if (AEInputCheckCurr(AEVK_S))
            {   
                if (player1_trs->GetPos().y >-380)
                    player1_trs->AddPos(0.f, -10.f);                
            }                     
        }
        int x, y;
        AEInputGetCursorPosition(&x, &y);        
        if (player->GetName() == "Player2")
        {            
            if (-y + 350 < 380 &&-y+350>-380)
            {
                player2_trs->SetPos(750.f, -y + 350);                
            }                                  
        }       
    }


    //Check Collider and Add Collider Event
    if (ColliderManager::GetInst()->IsCollision(ball, player1))
    {        
        Collision* colEvent = new Collision(ball, player1);
        colEvent->SetEventName("Collision");
        RePosition* ballAndPlayer1 = new RePosition;                
        EventManager::GetInst()->AddEvent(colEvent);
        EventManager::GetInst()->AddEntity(ballAndPlayer1);        
        EventManager::GetInst()->AddEntityList("Collision", EventManager::GetInst()->GetEntityList());
                
        //audio
        auto res = ResourceManager::GetInst()->Get("sfx", "Assets/ore.mp3");
        AudioResource* sfx_res = static_cast<AudioResource*>(res);
        sfx_res->SetSFXorMusic(Sound::MUSIC);
        auto sfx_audio = sfx_res->GetAudio();
        auto sfx_audioGroup = sfx_res->GetAudioGroup();
        AEAudioPlay(sfx_audio, sfx_audioGroup, 1.f, 1.f, 0);
    }
    if (ColliderManager::GetInst()->IsCollision(ball, player2))
    {           
        Collision* colEvent = new Collision(ball, player2);
        colEvent->SetEventName("Collision");
        RePosition* ballAndPlayer2 = new RePosition;
        EventManager::GetInst()->AddEvent(colEvent);
        EventManager::GetInst()->AddEntity(ballAndPlayer2);
        EventManager::GetInst()->AddEntityList("Collision", EventManager::GetInst()->GetEntityList());

        //audio
        auto res = ResourceManager::GetInst()->Get("sfx", "Assets/ore.mp3");
        AudioResource* sfx_res = static_cast<AudioResource*>(res);
        sfx_res->SetSFXorMusic(Sound::MUSIC);
        auto sfx_audio = sfx_res->GetAudio();
        auto sfx_audioGroup = sfx_res->GetAudioGroup();
        AEAudioPlay(sfx_audio, sfx_audioGroup, 1.f, 1.f, 0);
    }    
        
    if (ColliderManager::GetInst()->IsCollision(ball, DownPost))
    {        
        Collision* colEvent = new Collision(ball, DownPost);
        colEvent->SetEventName("Collision");
        RePosition* ballAndDownPost = new RePosition;
        EventManager::GetInst()->AddEvent(colEvent);
        EventManager::GetInst()->AddEntity(ballAndDownPost);
        EventManager::GetInst()->AddEntityList("Collision", EventManager::GetInst()->GetEntityList());
    }    
    if (ColliderManager::GetInst()->IsCollision(ball, UpperPost))
    {
        Collision* colEvent = new Collision(ball, UpperPost);
        colEvent->SetEventName("Collision");
        RePosition* ballAndUpperPost = new RePosition;
        EventManager::GetInst()->AddEvent(colEvent);
        EventManager::GetInst()->AddEntity(ballAndUpperPost);
        EventManager::GetInst()->AddEntityList("Collision", EventManager::GetInst()->GetEntityList());
        
    }
        
    //When player getScore     
    if (ColliderManager::GetInst()->IsCollision(ball, goalPost1))
    {
        Collision* colEvent = new Collision(ball, goalPost1);
        colEvent->SetEventName("Collision");
        RePosition* ballAndgoalPost1 = new RePosition;
        EventManager::GetInst()->AddEvent(colEvent);
        EventManager::GetInst()->AddEntity(ballAndgoalPost1);
        EventManager::GetInst()->AddEntityList("Collision", EventManager::GetInst()->GetEntityList());
        score[1]++;
    }        
    if (ColliderManager::GetInst()->IsCollision(ball, goalPost2))
    {   
        Collision* colEvent = new Collision(ball, goalPost2);
        colEvent->SetEventName("Collision");
        RePosition* ballAndgoalPost2 = new RePosition;
        EventManager::GetInst()->AddEvent(colEvent);
        EventManager::GetInst()->AddEntity(ballAndgoalPost2);
        EventManager::GetInst()->AddEntityList("Collision", EventManager::GetInst()->GetEntityList());
        
        score[0]++;
    }


    //Win Condition
    if (score[0] >= 11)
    {                
        ball_rb->SetVelocityZero();   
        m_bWin = true;
    }
    else if (score[1] >= 11)
    {                
        ball_rb->SetVelocityZero();        
        m_bWin = true;
    }    

    //Sprite
    for (auto comp : CompManager::GetInst()->AllComp())
    {                
        if (comp->GetName()=="Sprite")
        {
            if (comp->m_pOwner->GetName() == "GoalPost1"|| comp->m_pOwner->GetName() == "GoalPost2")
            {
                SpriteComponent::Color& goalPostColor = static_cast<SpriteComponent*>(comp)->GetColor();
                goalPostColor.red = 255;
                goalPostColor.green = 0;
                goalPostColor.blue = 0;
            }
            else if (comp->m_pOwner->GetName() == "Player1" || comp->m_pOwner->GetName() == "Player2")
            {
                SpriteComponent::Color& playerColor = static_cast<SpriteComponent*>(comp)->GetColor();
                playerColor.red = 255;
                playerColor.green = 255;
                playerColor.blue = 255;
            }
            else if (comp->m_pOwner->GetName() == "UpperPost" || comp->m_pOwner->GetName() == "DownPost")
            {
                SpriteComponent::Color& PostColor = static_cast<SpriteComponent*>(comp)->GetColor();
                PostColor.red = 255;
                PostColor.green = 255;
                PostColor.blue = 255;
            }
            else
            {                
                SpriteComponent::Color& Color = static_cast<SpriteComponent*>(comp)->GetColor();
                float time = TimeManager::GetInst()->GetAccTime();
                if (time / 4 < 0.5)
                {
                    if (score[0] >2|| score[1] > 2)
                    {
                        Color.red = Utility::GetInst()->lerp(0.f, 1.0f, time / 2) * 255;                        
                        Color.blue = 0.f;
                        Color.green = 0.f;
                    }
                    else
                    {
                        Color.red = 255.f;
                        Color.blue = 0.f;
                        Color.green = 0.f;
                    }                    
                }
                else if (time / 4 >= 0.5 && time / 4 < 1)
                {
                    if (score[0] > 2 || score[1] > 2)
                    {
                        Color.red = Utility::GetInst()->lerp(1.f, 0.0f, time / 2 - 1) * 255;
                        Color.blue = 0.f;
                        Color.green = 0.f;
                    }
                    else
                    {
                        Color.red = 255.f;
                        Color.blue = 0.f;
                        Color.green = 0.f;
                    }                    
                }
                else
                {
                    TimeManager::GetInst()->SetAccTime(0.f);
                }
            }
            
        }              
    }    


    if (m_bWin == false)
    {        
        AEGfxPrint(font, text, -0.1f, 1.f - (height + 0.057), 1, 1, 1, 1, 1);

        ScoreText_res->SetText(std::to_string(score[0]));
        AEGfxPrint(font, text, -0.1f, 1.f - (height + 0.3), 1, 1, 1, 1, 1);


        ScoreText_res->SetText(std::to_string(score[1]));
        AEGfxPrint(font, text, 0.1f, 1.f - (height + 0.3), 1, 1, 1, 1, 1);
    }
    else
    {
        if (score[1] > score[0])
        {
            ScoreText_res->SetText("Player2 WIN ! !");
            AEGfxPrint(font, text, -0.35f, 1.f - (height + 0.15), 1, 1, 1, 1, 1);
        }
        else
        {
            ScoreText_res->SetText("Player1 WIN ! !");
            AEGfxPrint(font, text, -0.35f, 1.f - (height + 0.15), 1, 1, 1, 1, 1);
        }
        ScoreText_res->SetText("Retry : R");
        AEGfxPrint(font, text, -0.35f, 1.f - (height + 0.35), 0.5, 1, 1, 1, 1);
        ScoreText_res->SetText("Go Title : T");
        AEGfxPrint(font, text, -0.35f, 1.f - (height + 0.55), 0.5, 1, 1, 1, 1);
        ScoreText_res->SetText("Exit : E");
        AEGfxPrint(font, text, -0.35f, 1.f - (height + 0.75), 0.5, 1, 1, 1, 1);

        if (AEInputCheckCurr(AEVK_R) == true)
        {
            GSM::GameStateManager::GetInst()->ChangeLevel(new Level::Stage01_Lvl);
        }
        else if (AEInputCheckCurr(AEVK_E) == true)
        {
            GSM::GameStateManager::GetInst()->ChangeLevel(nullptr);
        }
        else if (AEInputCheckCurr(AEVK_T) == true)
        {            
            GSM::GameStateManager::GetInst()->ChangeLevel(new Level::MainMenu_Lvl);
        }
    }
    
}

void Level::Stage01_Lvl::Exit()
{
    //std::cout << "Stage01 : Exit" << std::endl;  
    //delete All Object 컴포넌트와 컴포넌트 매니저는 game오브젝트 소멸되면서 자동으로 됨
    //이게 최선일까....
    //MemoryLeak Problem solved ↓    
    auto res = ResourceManager::GetInst()->GetReource();      
    //밑에 있는거 이렇게 지우면 안됨 수정하셈    
    //res.FindRes("bgm")->second->UnLoad(); <- 수정중
    ResourceManager::GetInst()->RemoveAllRes();
    GoManager::GetInst()->RemoveAllObj();    
}
