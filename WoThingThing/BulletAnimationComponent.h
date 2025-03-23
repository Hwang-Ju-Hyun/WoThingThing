#pragma once
#include "BaseComponent.h"
#include<iostream>

class GameObject;

class BulletAnimationComponent : public BaseComponent
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

    std::string current;

public:
    BulletAnimationComponent(GameObject* _owner);
    ~BulletAnimationComponent();

    void Initialize();
    void ChangeAnimation(std::string _name, f32 rows, f32 cols, f32 max, f32 duration);

    virtual void Update() override;
};