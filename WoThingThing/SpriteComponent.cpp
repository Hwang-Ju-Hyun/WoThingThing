#include "SpriteComponent.h"
#include "GameObject.h"
#include "TransComponent.h"

SpriteComponent::SpriteComponent(GameObject* _owner)
	:BaseComponent(_owner)
{
	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	mesh = AEGfxMeshEnd();

	m_color = { 255,255,255 };
}

SpriteComponent::~SpriteComponent()
{
	AEGfxMeshFree(mesh);
}

void SpriteComponent::Update()
{
	
	if (mesh == nullptr)
	{
		//std::cout << "Failed to create mesh" << std::endl;
		return;
	}

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	//AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);


	//Set color to Multiply	
	AEGfxSetColorToMultiply(m_color.red/255.f, m_color.green/255.f, m_color.blue/255.f,1);
	//AEGfxSetColorToMultiply(m_color.red , m_color.green , m_color.blue, 1);
	//AEGfxSetColorToMultiply(1, 0, 0, 1);

	//Set color to add
	AEGfxSetColorToAdd(0, 0, 0, 0);

	//Set Blend Mode
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1);

	TransComponent* trans = static_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));
	if (trans)
	{
		AEMtx33 transf = trans->GetMatrix();
		AEGfxSetTransform(transf.m);
	}

	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
	
	return;
}
