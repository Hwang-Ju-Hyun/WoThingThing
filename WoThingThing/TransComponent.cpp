#include "TransComponent.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include "AEGraphics.h"
#include "GoManager.h"
#include "RigidBodyComponent.h"
#include "NaveMeshManager.h"

TransComponent::TransComponent(GameObject* _owner) : BaseComponent(_owner), m_matMatrix{}
{

	//�� �ڵ�鵵 ���߿� stage01 _init���� �Űܾ���
	if (_owner->GetName() == "Player")
	{
		m_vPos = {200,0 };
		m_vScale = { 35,35 };
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

	//�߰� ��Ʈ(�鹫��)

	if (_owner->GetName() == "Test_player")
	{
		m_vPos = {-200,-200 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}

	if (_owner->GetName() == "Enemy")
	{
		m_vPos = { 600,-1250 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}

	if (_owner->GetName() == "EnemySniper")
	{
		m_vPos = { 900,300 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	//enemy bullet��
	if (_owner->GetName() == "e_bullet") 
	{
		m_vPos = { 0,0 };
		m_vScale = { 0,0 };
		m_fRot = 0.f;
	}
	//Boss��
	if (_owner->GetName() == "Boss")
	{
		m_vPos = { 600,600 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "BulletHellProjectile") 
	{
		m_vPos = { 0,0 };
		m_vScale = { 10,10 };
		m_fRot = 0.f;
	}
	

	//test Ȳ����
	if (_owner->GetName() == "Enemy_TEST")
	{
		m_vPos = { 1920,90 };
		m_vScale = { 30,30 };
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

void TransComponent::AddPos(const AEVec2& _pos)
{
	m_vPos.x += _pos.x;
	m_vPos.y += _pos.y;
}

void TransComponent::AddPos(float _posX, float _posY)
{
	float dt = AEFrameRateControllerGetFrameTime();
	if (AEInputCheckCurr(AEVK_LSHIFT))
	{
		_posX *= 50.f;
		dt *= 0.1f;
		m_vPos.x += _posX * (dt * 4.f);
		m_vPos.y += _posY * (dt * 4.f);
	}
	else
	{
		m_vPos.x += _posX;
		m_vPos.y += _posY;
	}
}

void TransComponent::MovePos(float _posX, float _posY, bool active, f32 m_fDt)
{
	if (active)
	{
		_posX *= 50.f;
		m_fDt *= 0.1f;
		m_vPos.x += _posX * (m_fDt * 4.f);
		m_vPos.y += _posY * (m_fDt * 4.f);
	}
	else
	{
		m_vPos.x += _posX;
		m_vPos.y += _posY;
	}
}

void TransComponent::SetPos(const AEVec2& _pos)
{
	m_vPos = _pos;
}
void TransComponent::SetPos(float _posX, float _posY)
{
	m_vPos.x = _posX;
	m_vPos.y = _posY;
}

void TransComponent::SetScale(const AEVec2& _scale)
{
	m_vScale = _scale;
}

void TransComponent::SetRot(const float& _rot)
{
	m_fRot = _rot;
}
//void TransComponent::SetRot(AEVec2 _rot)
//{
//	m_fRot = AEVec2Length(&_rot);
//}

void TransComponent::Update()
{
	CalculateMatrix();

	if (AEInputCheckReleased(AEVK_P))
		CalculateNodes();

	
}

BaseRTTI* TransComponent::CreateTransformComp()
{
	GameObject* lastObj = GoManager::GetInst()->GetLastObj();	//�Ƹ� ���Ⱑ �����ϵ� <- �ƴϳ�	
	BaseRTTI* p = lastObj->AddComponent("Transform", new TransComponent(lastObj));
	//GameObjectManager::GetInst()->GetLastObj()->AddComponent("Transform", TransformComponent();
	//GetLast()->AddComp<TransformComp>();
	return p;
}

void TransComponent::CalculateNodes()
{
	NaveMeshManager::GetInst()->ClearNode();	
	
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


	
	//Utilize the data
	CalculateMatrix();
	
}
static int nodeID = 0;
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

	//A section for the nodes
	json nodejson;	
	auto listNode=NaveMeshManager::GetInst()->GetallNode();
	for (auto it : listNode)
	{
		//Save its position
		nodejson[it.node_id] = { it.node_pos.x,it.node_pos.y };		
	}

	data["Nodes"] = nodejson;

	return data;
}