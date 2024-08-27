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
		m_vPos = { -755,0 };
		//m_vScale = { 50,300 };
		m_vScale = { 10,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Player2")
	{
		m_vPos = { 755,0 };
		//m_vScale = { 50,300 };
		m_vScale = { 10,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Ball")
	{
		m_vPos = { 0,0 };
		m_vScale = { 50,50 };
		m_fRot = 0.f;
	}

	if (_owner->GetName() == "GoalPost1")
	{
		m_vPos = { -800,0 };
		m_vScale = { 30,1000 };
		m_fRot = 0.f;
	}

	if (_owner->GetName() == "GoalPost2")
	{
		m_vPos = { 800,0 };
		m_vScale = { 30,1000 };
		m_fRot = 0.f;
	}

	if (_owner->GetName() == "UpperPost")
	{
		s32 window_width=AEGfxGetWindowWidth();
		s32 window_height = AEGfxGetWindowHeight();
		m_vPos = { 0,float(window_height/2.f)};
		m_vScale = { float(window_width),30};
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "DownPost")
	{
		s32 window_width = AEGfxGetWindowWidth();
		s32 window_height = AEGfxGetWindowHeight();
		m_vPos = {  0,-float(window_height / 2.f)};
		m_vScale = { float(window_width),30 };
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
