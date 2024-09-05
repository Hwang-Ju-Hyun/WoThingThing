#include "MultiAnimationComponent.h"

MultiAnimationComponent::MultiAnimationComponent(GameObject* _owner) : BaseComponent(_owner)
{

}

MultiAnimationComponent::~MultiAnimationComponent()
{
	AEGfxMeshFree(mesh);
	AEGfxTextureUnload(pTex);
}

void MultiAnimationComponent::Update()
{


}


//#include "AnimationComponent.h"
//#include "GameObject.h"
//#include "TransComponent.h"

//AnimationComponent::AnimationComponent(GameObject* _owner) : BaseComponent(_owner)
//{
//	AEGfxMeshStart();
//
//	AEGfxTriAdd(
//		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
//		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
//		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
//
//	AEGfxTriAdd(
//		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
//		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
//		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
//
//	mesh = AEGfxMeshEnd();
//
//
//	//pTex = AEGfxTextureLoad("Assets/idle_1.png");
//
//	testArr.push_back(AEGfxTextureLoad("Assets/idle_1.png"));
//	testArr.push_back(AEGfxTextureLoad("Assets/idle_2.png"));
//	testArr.push_back(AEGfxTextureLoad("Assets/idle_3.png"));
//	testArr.push_back(AEGfxTextureLoad("Assets/idle_4.png"));
//	testArr.push_back(AEGfxTextureLoad("Assets/idle_5.png"));
//
//	animation_timer = 0.f;
//	animation_duration_per_frame = 0.1f;
//}
//
//AnimationComponent::~AnimationComponent()
//{
//	AEGfxMeshFree(mesh);
//	AEGfxTextureUnload(pTex);
//}
//
//int i = 0;
//void AnimationComponent::Update()
//{
//	if (mesh == nullptr)
//		return;
//
//	animation_timer += (f32)AEFrameRateControllerGetFrameTime();
//
//	if (animation_timer >= animation_duration_per_frame)
//	{
//		//Doing Animation
//
//		// Reset the timer.
//		animation_timer = 0;
//
//		//pTex = AEGfxTextureLoad("Assets/idle_1.png");
//		pTex = testArr[i++];
//
//	}
//	if (i > 4)
//		i = 0;
//	//AEGfxSetRenderMode(AE_GFX_RM_COLOR);
//	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
//
//	AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
//
//	AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
//
//	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
//	AEGfxSetTransparency(1.0f);
//
//	AEGfxTextureSet(pTex, 0, 0);
//
//	TransComponent* trans = static_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));
//	if (trans)
//	{
//		AEMtx33 transf = trans->GetMatrix();
//		AEGfxSetTransform(transf.m);
//	}
//
//	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
//
//	return;
//}
