#include "SpriteComponent.h"
#include "GameObject.h"
#include "TransComponent.h"
#include "GoManager.h"

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
	//pTex = AEGfxTextureLoad("Assets/idle_1.png");

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
	if (m_pOwner->GetName() == "BackGround")
	{
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	}
	else
	{
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	}		


	//Set color to Multiply	
	//AEGfxSetColorToMultiply(155/255.f, 155/255.f, 255/255.f,1);	

	AEGfxSetColorToMultiply(m_color.red/255.f, m_color.green/255.f, m_color.blue/255.f,1);	
	//AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

	//Set color to add
	AEGfxSetColorToAdd(0, 0, 0, 0);

	//Set Blend Mode
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1);
	

	//AEGfxTextureSet(pTex, 0, 0);

	TransComponent* trans = static_cast<TransComponent*>(m_pOwner->FindComponent("Transform"));
	if (trans)
	{
		AEMtx33 transf = trans->GetMatrix();
		AEGfxSetTransform(transf.m);
	}

	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
	
	return;
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
