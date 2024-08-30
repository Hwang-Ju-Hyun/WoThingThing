#include "TransComponent.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include "AEGraphics.h"
#include "GoManager.h"
#include "RigidBodyComponent.h"


TransComponent::TransComponent(GameObject* _owner) : BaseComponent(_owner), m_matMatrix{}
{

	//이 코드들도 나중에 stage01 _init으로 옮겨야함
	if (_owner->GetName() == "Player")
	{
		m_vPos = { -750,550 };
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

	//추가 파트(백무송)

	if (_owner->GetName() == "Test_player")
	{
		m_vPos = {-200,-200 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}

	if (_owner->GetName() == "Enemy")
	{
		m_vPos = { 300,300 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}

	if (_owner->GetName() == "EnemySniper")
	{
		m_vPos = { 100,300 };
		m_vScale = { 50,100 };
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
		//dt *= 0.1f;
		/*m_vPos.x += _posX * (dt * 4.f);
		m_vPos.y += _posY * (dt * 4.f);*/
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
	float plat_right = m_vPos.x + m_vScale.x / 2.f;
	float plat_left = m_vPos.x - m_vScale.x / 2.f;
	float plat_top = m_vPos.y + m_vScale.y / 2.f;
	float plat_bot = m_vPos.y - m_vScale.y / 2.f;

	float scale_x = m_vScale.x;
	float scale_y = m_vScale.y;	

	
	/*std::string node_nameLeft = "Node";
	GameObject* node_left = new GameObject(node_nameLeft);
	GoManager::GetInst()->AddObject(node_left);
	node_left->AddComponent("Transform", new TransComponent(node_left));
	TransComponent* node_trsLeft = static_cast<TransComponent*>(node_left->FindComponent("Transform"));
	node_trsLeft->SetPos({ plat_left - 10.f,plat_bot + 10.f });
	node_trsLeft->SetScale({ 15.f,15.f });
	node_trsLeft->SetRot(0.f);

	std::string node_nameRight = "Node";
	GameObject* node_right = new GameObject(node_nameRight);
	GoManager::GetInst()->AddObject(node_right);
	node_right->AddComponent("Transform", new TransComponent(node_right));
	TransComponent* node_trsRight = static_cast<TransComponent*>(node_right->FindComponent("Transform"));
	node_trsRight->SetPos({ plat_right + 10.f,plat_bot + 10.f });
	node_trsRight->SetScale({ 15.f,15.f });
	node_trsRight->SetRot(0.f);

	std::string node_nameTop = "Node";
	GameObject* Node_top = new GameObject(node_nameTop);
	GoManager::GetInst()->AddObject(Node_top);
	Node_top->AddComponent("Transform", new TransComponent(Node_top));
	TransComponent* node_trsTop = static_cast<TransComponent*>(Node_top->FindComponent("Transform"));
	node_trsTop->SetPos({ m_vPos.x,plat_top + 10.f});
	node_trsTop->SetScale({ 15.f,15.f });
	node_trsTop->SetRot(0.f);*/



	//노드 생성
	int node_Wcnt = m_vScale.x / 20; //20(너비) 단위로 노드를 생성하겠음
	int node_Hcnt = m_vScale.y / 20; //20(높이) 단위로 노드를 생성하겠음



	//Create Upper Node	
	for (int i = 0; i < node_Wcnt+2; i++) //+2한 이유 좌우측 모서리도 노드를 표현하기위해서
	{
		std::string node_name = "Node";
		GameObject* Node = new GameObject(node_name);
		GoManager::GetInst()->AddObject(Node);
		Node->AddComponent("Transform", new TransComponent(Node));
		TransComponent* node_trs = static_cast<TransComponent*>(Node->FindComponent("Transform"));
		node_trs->SetPos({ plat_left + (i * 20.f),plat_top + 20.f });
		node_trs->SetScale({ 10.f,10.f });
		node_trs->SetRot(0.f);
	}
	/*Create Left Node
	for (int i = 0; i < node_Hcnt+1; i++)
	{
		std::string node_name = "Node";
		GameObject* Node = new GameObject(node_name);
		GoManager::GetInst()->AddObject(Node);
		Node->AddComponent("Transform", new TransComponent(Node));
		TransComponent* node_trs = static_cast<TransComponent*>(Node->FindComponent("Transform"));
		node_trs->SetPos({ plat_left-10.f,plat_top-(i*20.f)});
		node_trs->SetScale({ 10.f,10.f });
		node_trs->SetRot(0.f);
	}
	Create Right Node
	for (int i = 0; i < node_Hcnt+1; i++)
	{
		std::string node_name = "Node";
		GameObject* Node = new GameObject(node_name);
		GoManager::GetInst()->AddObject(Node);
		Node->AddComponent("Transform", new TransComponent(Node));
		TransComponent* node_trs = static_cast<TransComponent*>(Node->FindComponent("Transform"));
		node_trs->SetPos({ plat_right + 10.f,plat_top - (i * 20.f) });
		node_trs->SetScale({ 10.f,10.f });
		node_trs->SetRot(0.f);
	}*/

	
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