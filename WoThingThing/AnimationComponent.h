#pragma once
#include "BaseComponent.h"
#include<iostream>

class GameObject;

class AnimationComponent : public BaseComponent
{
    AEGfxVertexList* mesh;
    AEGfxTexture* pTex;

    u32 spritesheet_rows;
    u32 spritesheet_cols;
    u32 spritesheet_max_sprites;
    f32 sprite_uv_width;
    f32 sprite_uv_height;

    f32 animation_timer;
    f32 animation_duration_per_frame;
    u32 current_sprite_index; // start from first sprite
    f32 current_sprite_uv_offset_x;
    f32 current_sprite_uv_offset_y;

public:
    AnimationComponent(GameObject* _owner);
    ~AnimationComponent();

    virtual void Update() override;
};