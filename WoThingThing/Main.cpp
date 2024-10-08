#include "Main.h"
#include "header.h"

#include "GameStateManager.h"
#include "GameStart_Lvl.h" 
#include "MainMenu_Lvl.h"

#include "TimeManager.h"
#include "Stage01_Lvl.h"
#include "CompManager.h"
#include "EventManager.h"
#include "CameraManager.h"
#include <memory>
#include "StageTutorial.h"
#include "TestLevel.h"//추가부분(백무송)

#include "ResourceManager.h"
#include"Stage01_Lvl.h"


int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	UNREFERENCED_PARAMETER(prevInstanceH);
	UNREFERENCED_PARAMETER(command_line);

	// Enable run-time memory check for debug builds.
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif	

	/*
		*/
	// Initialize the system
	AESysInit(instanceH, show, 1600, 900, 0, 60, true, NULL);


	// Changing the window title
	AESysSetWindowTitle("WoThingThing");

	AESysReset();

	//Initialize GSM;
	GSM::GameStateManager* gsm = GSM::GameStateManager::GetInst();
	gsm->ChangeLevel(new Level::MainMenu_Lvl);

	while(gsm->ShouldExit()==false)
	{
		AEFrameRateControllerReset();

		AESysFrameStart();

		//set background color
		AEGfxSetBackgroundColor(0.f, 0.f, 0.f);

		//Update;
		CompManager::GetInst()->Update();
		TimeManager::GetInst()->Update();
		EventManager::GetInst()->Update();
		gsm->Update();
		
		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if ((AESysDoesWindowExist() == false))
		{			
			gsm->ChangeLevel(nullptr);			
		}							

		std::cout << AEFrameRateControllerGetFrameRate()<< std::endl;
	}

	// free the system
	AESysExit();
}