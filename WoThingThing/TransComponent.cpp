#include "TransComponent.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include "AEGraphics.h"
#include "GoManager.h"

TransComponent::TransComponent(GameObject* _owner)
	:BaseComponent(_owner)	
	, m_matMatrix{}
{
	//�� �ڵ�鵵 ���߿� stage01 _init���� �Űܾ���
	if (_owner->GetName() == "Player1")
	{
		m_vPos = { -755,0 };
		//m_vScale = { 50,300 };
		m_vScale = { 10,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Platform")
	{
		m_vPos = { 50.f,50.f };
		m_vScale = { 50.f,50.f };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Start")
	{
		m_vPos = {50,0};
		m_vScale = { 500,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Exit")
	{
		m_vPos = { 50,-200 };
		m_vScale = { 500,100 };
		m_fRot = 0.f;
	}

}

TransComponent::~TransComponent()
{
}

void TransComponent::CalculateMatrix()
{	
	//�̵� ��� ����
	AEMtx33 translateMtx;
	AEMtx33Trans(&translateMtx, m_vPos.x, m_vPos.y);
	//ȸ�� ��� ����
	AEMtx33  rotationMtx;
	AEMtx33Rot(&rotationMtx, this->m_fRot);
	//ũ�� ��� ����
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
	GameObject* lastObj = GoManager::GetInst()->GetLastObj();	//�Ƹ� ���Ⱑ �����ϵ�
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

		auto s = compData->find("Sca");
		m_vPos.x = p->begin().value();
		m_vPos.y = (p->begin() + 1).value();

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
