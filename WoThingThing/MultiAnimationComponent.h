#pragma once
#include "BaseComponent.h"

class GameObject;

class MultiAnimationComponent : public BaseComponent
{
    AEGfxVertexList* mesh;
    AEGfxTexture* pTex;//파일 넣는부분

    f32 animation_timer;
    f32 animation_duration_per_frame;

    
    u32 spritesheet_rows;//가로 갯수
    u32 spritesheet_cols;//세로 갯수 
    u32 spritesheet_max_sprites;//실질적인 총량 
    f32 sprite_uv_width = 1.f / spritesheet_cols;//
    f32 sprite_uv_height = 1.f / spritesheet_rows;
public:
    MultiAnimationComponent(GameObject* _owner);
    ~MultiAnimationComponent();

    virtual void Update() override;
};
