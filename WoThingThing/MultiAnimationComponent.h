#pragma once
#include "BaseComponent.h"

class GameObject;

class MultiAnimationComponent : public BaseComponent
{
    AEGfxVertexList* mesh;
    AEGfxTexture* pTex;//���� �ִºκ�

    f32 animation_timer;
    f32 animation_duration_per_frame;

    
    u32 spritesheet_rows;//���� ����
    u32 spritesheet_cols;//���� ���� 
    u32 spritesheet_max_sprites;//�������� �ѷ� 
    f32 sprite_uv_width = 1.f / spritesheet_cols;//
    f32 sprite_uv_height = 1.f / spritesheet_rows;
public:
    MultiAnimationComponent(GameObject* _owner);
    ~MultiAnimationComponent();

    virtual void Update() override;
};
