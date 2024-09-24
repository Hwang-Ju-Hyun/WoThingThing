#include "SpriteComponent.h"
#include "GameObject.h"
#include "TransComponent.h"
#include "GoManager.h"

#include "ResourceManager.h"
#include "ImageResource.h"

SpriteComponent::SpriteComponent(GameObject* _owner) : BaseComponent(_owner)
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
	
	pTex = nullptr;
	m_color = { 255,255,255 };
	
	alpha = 1.f;
}

SpriteComponent::~SpriteComponent()
{	
	AEGfxMeshFree(mesh);
}

void SpriteComponent::Update()
{
	if (mesh == nullptr)
	{
		return;
	}
	if (pTex != nullptr)
	{
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

		AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, alpha);

		AEGfxSetColorToAdd(0, 0, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.f);
		AEGfxTextureSet(pTex, 0, 0);
		TransComponent* trans = static_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));
		if (trans)
		{
			AEMtx33 transf = trans->GetMatrix();
			AEGfxSetTransform(transf.m);
		}

		AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
	}
	else
	{
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		AEGfxSetColorToMultiply(m_color.red / 255.f, m_color.green / 255.f, m_color.blue / 255.f, 1);
		AEGfxSetColorToAdd(0, 0, 0, 0);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.f);
		AEGfxTextureSet(pTex, 0, 0);
		TransComponent* trans = static_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));
		if (trans)
		{
			AEMtx33 transf = trans->GetMatrix();
			AEGfxSetTransform(transf.m);
		}

		AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
	}

	return;
}

void SpriteComponent::SetTexture(AEGfxTexture* inputTex)
{
	pTex = inputTex;
}
void SpriteComponent::SetAlpha(f32 value)
{
	alpha = value;
}

BaseRTTI* SpriteComponent::CreateSpriteComponent()
{
	GameObject* lastObj = GoManager::GetInst()->GetLastObj();	//아마 여기가 문제일듯 <- 아니네	
	BaseRTTI* p = lastObj->AddComponent("Sprite", new SpriteComponent(lastObj));
	return p;
}

void SpriteComponent::LoadFromJson(const json& str)
{


	auto compData = str.find("CompData");
	if (compData != str.end())
	{
		auto r = compData->find("RED");
		m_color.red = r.value();
		
		auto b = compData->find("BLUE");
		m_color.blue= b.value();

		auto g = compData->find("GREEN");
		m_color.green = g.value();

		auto pfName = compData->find("TextureName");
		auto pfPath = compData->find("TexturePath");
		if(pfName != compData->end() && pfPath != compData->end())
		{
			ResourceManager::GetInst()->Get(pfName.value(), pfPath.value());
			ImageResource* bgResource = (ImageResource*)ResourceManager::GetInst()->FindRes(pfName.value());
			this->SetTexture(bgResource->GetImage());
		}
	}	
}

json SpriteComponent::SaveToJson()
{
	json data;
	data["Type"] = "Sprite";

	json compData;
	compData["RED"] = m_color.red;
	compData["BLUE"] = m_color.blue;
	compData["GREEN"] = m_color.green;


	data["CompData"] = compData;
	return data;
}
