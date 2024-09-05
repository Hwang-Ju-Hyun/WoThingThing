#include "Main.h"
#include "GameStateManager.h"
#include "header.h"
#include "MainMenu_Lvl.h"
#include "Stage01_Lvl.h"
#include "TimeManager.h"
#include "CompManager.h"
#include "EventManager.h"
#include "CameraManager.h"
#include <memory>
#include "TestLevel.h"//추가부분(백무송)

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
	AESysSetWindowTitle("Asteriods Demo!");

	AESysReset();
	
	//Initialize GSM;
	GSM::GameStateManager* gsm = GSM::GameStateManager::GetInst();
	
		
	//Level::MainMenu_Lvl MainMenu_lvl;
	//Level::Stage01_Lvl Stage01_lvl;
	//Level::TestLevel Test;
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
		if ((AESysDoesWindowExist() == false) || AEInputCheckTriggered(AEVK_SCROLLLOCK))
		{			
			gsm->ChangeLevel(nullptr);
			//gsm->Exit();
		}							
	}

	// free the system
	AESysExit();
}

/*
//
// Spritesheet animation 
// 
// AUTHORS: 
//   Gerald Wong
//  
// DESCRIPTION:
//   The code below shows how to swap between different sprites
//   within a spritesheet over time, emulating sprite animation. 
//
//   Press [0] to decrease animation speed.
//   Press [1] to increase animation speed.
//
//   Students should not take this code as a reference to
//   "good architecture". That's not the point of this demo.
//


#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"


int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(prevInstanceH);
    UNREFERENCED_PARAMETER(command_line);


    int gGameRunning = 1;


    // Initialization of your own variables go here

    // Using custom window procedure
    AESysInit(instanceH, show, 1600, 900, 1, 60, true, NULL);

    // Changing the window title
    AESysSetWindowTitle("Spritesheet Demo!");

    // (Not so good) hardcoded values about our spritesheet

    //사진 파일을 짜르는 기준 (행,열,갯수,한 프레임에 나올 사이즈(가로,세로))
    const u32 spritesheet_rows = 5;
    const u32 spritesheet_cols = 4;
    const u32 spritesheet_max_sprites = 19;
    const f32 sprite_uv_width = 1.f / spritesheet_cols;
    const f32 sprite_uv_height = 1.f / spritesheet_rows;

    // (Not so good) hardcoded values about our animation
    //이부분이 몇초동안 애니메이션을 재생할껀지
    f32 animation_timer = 0.f;
    f32 animation_duration_per_frame = 0.1f;
    u32 current_sprite_index = 0; // 시작되는 스프라이트 위치(왼쪽위가 0임)
    f32 current_sprite_uv_offset_x = 0.f;//시작하는 스프라이트 좌표값x
    f32 current_sprite_uv_offset_y = 0.f;//시작하는 스프라이트 좌표값y


    // Pointer to Mesh
    AEGfxVertexList* pMesh = 0;

    // Informing the library that we're about to start adding triangles
    AEGfxMeshStart();

    // This shape has 2 triangles that makes up a square
    // Color parameters represent colours as ARGB
    // UV coordinates to read from loaded textures
    AEGfxTriAdd(
        -0.5f, -0.5f, 0xFFFFFFFF, 0.0f, sprite_uv_height, // bottom left
        0.5f, -0.5f, 0xFFFFFFFF, sprite_uv_width, sprite_uv_height, // bottom right 
        -0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);  // top left

    AEGfxTriAdd(
        0.5f, -0.5f, 0xFFFFFFFF, sprite_uv_width, sprite_uv_height, // bottom right 
        0.5f, 0.5f, 0xFFFFFFFF, sprite_uv_width, 0.0f,   // top right
        -0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);  // bottom left


    // Saving the mesh (list of triangles) in pMesh
    pMesh = AEGfxMeshEnd();

    // Load texture
    AEGfxTexture* pTex = AEGfxTextureLoad("Assets/ame.png");


    // Game Loop
    while (gGameRunning)
    {

        // Informing the system about the loop's start
        AESysFrameStart();

        // Input that controls animation speed


        //
        // Update animation.
        // This is where all the animation magic happens.
        //

        // Update the animation timer.
        // animation_timer should go up to animation_duration_per_frame.
        animation_timer += (f32)AEFrameRateControllerGetFrameTime();

        if (animation_timer >= animation_duration_per_frame) {
            // When the time is up go to the next sprite.

            // Reset the timer.
            animation_timer = 0;

            // Calculate the next sprite UV
            current_sprite_index = ++current_sprite_index % spritesheet_max_sprites;//사이클을 만드는 구간

            //현재 진행되고있는 스프라이트 위치를 index에서 row,col으로 변환 시켜주는 방법
            u32 current_sprite_row = current_sprite_index / spritesheet_cols;
            u32 current_sprite_col = current_sprite_index % spritesheet_cols;

            //스프라이트의 좌표를 구하는 방법
            current_sprite_uv_offset_x = sprite_uv_width * current_sprite_col;
            current_sprite_uv_offset_y = sprite_uv_height * current_sprite_row;

        }



        // Your own rendering logic goes here
        // Set the background to black.
        AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

        // Tell the engine to get ready to draw something with texture.
        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

        // Set the the color to multiply to white, so that the sprite can 
        // display the full range of colors (default is black).
        AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
        AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);

        // Set blend mode to AE_GFX_BM_BLEND
        // This will allow transparency.
        AEGfxSetBlendMode(AE_GFX_BM_BLEND);
        AEGfxSetTransparency(1.0f);

        // Set the texture to pTex
        AEGfxTextureSet(pTex, current_sprite_uv_offset_x, current_sprite_uv_offset_y);

        AEMtx33 scale = { 0 };
        AEMtx33Scale(&scale, 800.f, 800.f);

        // Choose the transform to use
        AEGfxSetTransform(scale.m);

        // Actually drawing the mesh 
        AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

        // Informing the system about the loop's end
        AESysFrameEnd();


        // check if forcing the application to quit
        if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
            gGameRunning = 0;
    }



    AEGfxMeshFree(pMesh);
    AEGfxTextureUnload(pTex);
    // free the system
    AESysExit();

}*/
