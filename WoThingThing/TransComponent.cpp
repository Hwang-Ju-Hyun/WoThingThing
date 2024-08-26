#include "TransComponent.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include "AEGraphics.h"

TransComponent::TransComponent(GameObject* _owner)
	:BaseComponent(_owner)	
	, m_matMatrix{}
{
	//이 코드들도 나중에 stage01 _init으로 옮겨야함
	if (_owner->GetName() == "Player1")
	{
		m_vPos = { -755,-380 };
		m_vScale = { 50,50 };
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
