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
#include "Serializer.h"
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
	//player1 = new GameObject("Player1");
    Platform = new GameObject("Platform");

	//GoManager::GetInst()->AddObject(player1);	    

	/*player1->AddComponent("Transform", new TransComponent(player1));
	player1->AddComponent("Sprite", new SpriteComponent(player1));	    */

    std::ifstream StageMapFile("../Extern/Platform/Platform.txt");
    int PlatformNum;
    AEVec2 PlatformScale;
    int PlatformKey; //플랫폼 킷값
    AEVec2 PlatformPos;
    if (!StageMapFile.is_open())
    {
        std::cerr << "StageMapFile can't open : Stage01_Lvl Init()" << std::endl;
        return;
    }
    else
    {
        StageMapFile >> PlatformNum;
        StageMapFile >> PlatformScale.x>> PlatformScale.y;
        while (!StageMapFile.eof())
        {
            Platform = new GameObject("Platform");
            GoManager::GetInst()->AddObject(Platform);            
            StageMapFile >> PlatformPos.x;
            StageMapFile >> PlatformPos.y;
            
            Platform->AddComponent("Transform", new TransComponent(Platform));
            TransComponent* Platform_trs = (TransComponent*)Platform->FindComponent("Transform");
            Platform_trs->SetPos(PlatformPos.x, PlatformPos.y);
            Platform_trs->SetScale({ PlatformScale.x, PlatformScale.y });                        
            Platform->AddComponent("Sprite", new SpriteComponent(Platform));
            

            
            m_vecPlatforms.push_back(Platform);
        }
    }    

    Serializer::GetInst()->LoadLevel("temp.json");

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
	/*TransComponent* player1_trs = (TransComponent*)player1->FindComponent("Transform");    
	SpriteComponent* player1_spr = (SpriteComponent*)player1->FindComponent("Sprite");          */





    //Score Text
    auto text_res = ResourceManager::GetInst()->Get("text", "Assets/liberation-mono.ttf");
    TextResource* ScoreText_res = static_cast<TextResource*>(text_res);
    ScoreText_res->SetText("Score");
    
    auto font = ScoreText_res->GetFont();
    auto text = ScoreText_res->GetText();
    auto height = ScoreText_res->GetHeight();
                
        
    ////When player getScore     
    //if (ColliderManager::GetInst()->IsCollision(ball, goalPost1))
    //{
    //    Collision* colEvent = new Collision(ball, goalPost1);
    //    colEvent->SetEventName("Collision");
    //    RePosition* ballAndgoalPost1 = new RePosition;
    //    EventManager::GetInst()->AddEvent(colEvent);
    //    EventManager::GetInst()->AddEntity(ballAndgoalPost1);
    //    EventManager::GetInst()->AddEntityList("Collision", EventManager::GetInst()->GetEntityList());
    //    
    //}        
    //if (ColliderManager::GetInst()->IsCollision(ball, goalPost2))
    //{   
    //    Collision* colEvent = new Collision(ball, goalPost2);
    //    colEvent->SetEventName("Collision");
    //    RePosition* ballAndgoalPost2 = new RePosition;
    //    EventManager::GetInst()->AddEvent(colEvent);
    //    EventManager::GetInst()->AddEntity(ballAndgoalPost2);
    //    EventManager::GetInst()->AddEntityList("Collision", EventManager::GetInst()->GetEntityList());
    //         
    //}        

   
    
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
