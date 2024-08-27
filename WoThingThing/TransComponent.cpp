#include "TransComponent.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include "AEGraphics.h"
#include "GoManager.h"


TransComponent::TransComponent(GameObject* _owner) : BaseComponent(_owner), m_matMatrix{}
{
	//이 코드들도 나중에 stage01 _init으로 옮겨야함
	if (_owner->GetName() == "Player1")
	{
		m_vPos = { -755,-380 };
		m_vScale = { 50,50 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "mouseAim")
	{
		m_vScale = { 20,20 };
		m_fRot = 0.77f;
	}
	if (_owner->GetName() == "Platform")
	{
		m_vPos = { 50.f,50.f };
		m_vScale = { 50.f,50.f };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Start")
	{
		m_vPos = { 50,0 };
		m_vScale = { 500,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Exit")
	{
		m_vPos = { 50,-200 };
		m_vScale = { 500,100 };
		m_fRot = 0.f;
	}


	//백무송 파트 플레이어와 적 추가 부분
	if (_owner->GetName() == "Player") 
	{

	}

	if (_owner->GetName()=="Enemy")
	{

	}

}

TransComponent::~TransComponent()
{
}

void TransComponent::CalculateMatrix()
{
	//이동 행렬 생성
	AEMtx33 translateMtx;
	AEMtx33Trans(&translateMtx, m_vPos.x, m_vPos.y);
	//회전 행렬 생성
	AEMtx33  rotationMtx;
	AEMtx33Rot(&rotationMtx, this->m_fRot);
	//크기 행렬 생성
	AEMtx33 scaleMtx;
	AEMtx33Scale(&scaleMtx, m_vScale.x, m_vScale.y);

	//Concat
	AEMtx33Concat(&m_matMatrix, &rotationMtx, &scaleMtx);
	AEMtx33Concat(&m_matMatrix, &translateMtx, &m_matMatrix);
}

void TransComponent::Update()
{
	CalculateMatrix();
}

BaseRTTI* TransComponent::CreateTransformComp()
{
	GameObject* lastObj = GoManager::GetInst()->GetLastObj();	//아마 여기가 문제일듯 <- 아니네	
	BaseRTTI* p = lastObj->AddComponent("Transform", new TransComponent(lastObj));
	//GameObjectManager::GetInst()->GetLastObj()->AddComponent("Transform", TransformComponent();
	//GetLast()->AddComp<TransformComp>();
	return p;
}

void TransComponent::LoadFromJson(const json& str)
{
	//Check how you saved. load from there

	auto compData = str.find("CompData");
	if (compData != str.end())
	{
		auto p = compData->find("Pos");
		m_vPos.x = p->begin().value();
		m_vPos.y = (p->begin() + 1).value();

		auto s = compData->find("sca");
		m_vScale.x = s->begin().value();
		m_vScale.y = (s->begin() + 1).value();

		auto r = compData->find("Rot");
		m_fRot = r.value();
	}
	//Data is loaded

	//Utilize the data
	CalculateMatrix();
}

json TransComponent::SaveToJson()
{
	json data;
	//Save the type
	data["Type"] = "Transform";

	//Save my data	
	json compData;
	//pos
	compData["Pos"] = { m_vPos.x,m_vPos.y };
	//sca
	compData["sca"] = { m_vScale.x,m_vScale.y };
	//rot
	compData["Rot"] = m_fRot;

	data["CompData"] = compData;

	return data;
}