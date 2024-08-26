#include "Main.h"
#include "GameStateManager.h"
#include "header.h"
#include "MainMenu_Lvl.h"
#include "Stage01_Lvl.h"
#include "TimeManager.h"
#include "CompManager.h"
#include "EventManager.h"
#include <memory>

//float	 g_dt;
//double	 g_appTime;

int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	UNREFERENCED_PARAMETER(prevInstanceH);
	UNREFERENCED_PARAMETER(command_line);

	//// Enable run-time memory check for debug builds.
	//#if defined(DEBUG) | defined(_DEBUG)
	//	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//#endif	

	// Initialize the system
	AESysInit(instanceH, show, 1600, 900, 0, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle("Asteriods Demo!");

	AESysReset();
	
	//Initialize GSM;
	GSM::GameStateManager* gsm = GSM::GameStateManager::GetInst();
	
		
	Level::MainMenu_Lvl MainMenu_lvl;
	Level::Stage01_Lvl Stage01_lvl;


	gsm->ChangeLevel(new Level::MainMenu_Lvl);


	while(gsm->ShouldExit()==false)
	{
		AESysFrameStart();

		//set background color
		AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

		//Update;
		CompManager::GetInst()->Update();
		TimeManager::GetInst()->Update();
		EventManager::GetInst()->Update();
		gsm->Update();


		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if ((AESysDoesWindowExist() == false) || AEInputCheckTriggered(AEVK_ESCAPE))
		{			
			gsm->ChangeLevel(nullptr);
			gsm->Exit();
		}							
	}

	// free the system
	AESysExit();
}