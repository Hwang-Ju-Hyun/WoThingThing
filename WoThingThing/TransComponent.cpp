#include "TransComponent.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include "AEGraphics.h"
#include "GoManager.h"
#include "RigidBodyComponent.h"
#include "NaveMeshManager.h"

TransComponent::TransComponent(GameObject* _owner) : BaseComponent(_owner), m_matMatrix{}
{

	//이 코드들도 나중에 stage01 _init으로 옮겨야함
	if (_owner->GetName() == "Player")
	{
		//pos 절대 고정해 
		m_vPos = {200,0 };
		m_vScale = { 80,80 };
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
		m_vPos = { -200,-200 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}

	if (_owner->GetName() == "Enemy" && _owner->GetID() == 0)
	{
		////pos 절대 고정해 
		m_vPos = { 600,-1250 };
		m_vScale = { 70,50 };
		m_fRot = 0.f;
	}

	if (_owner->GetName() == "Enemy" && _owner->GetID() == 1)
	{
		//pos 절대 고정해 
		m_vPos = { 900,300 };
		m_vScale = { 60,60 };
		m_fRot = 0.f;
	}

	if (_owner->GetName() == "Enemy" && _owner->GetID() == 2)
	{
		m_vPos = { 850,-1282 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Enemy" && _owner->GetID() == 3)
	{
		m_vPos = { 1150,-970 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Enemy" && _owner->GetID() == 4)
	{
		m_vPos = { 1920,-970 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Enemy" && _owner->GetID() == 5)
	{
		m_vPos = { 2220,-970 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Enemy" && _owner->GetID() == 6)
	{
		m_vPos = { 1020,-970 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Enemy" && _owner->GetID() == 7)
	{
		m_vPos = { 1743,-707 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Enemy" && _owner->GetID() == 8)
	{
		m_vPos = { 2282,-692 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Enemy" && _owner->GetID() == 9)
	{
		m_vPos = { 2942,-932 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Enemy" && _owner->GetID() == 10)
	{
		m_vPos = { 3297,-662 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Enemy" && _owner->GetID() == 11)
	{
		m_vPos = { 3547,-872 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Enemy" && _owner->GetID() == 11)
	{
		m_vPos = { 3547,-872 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Enemy" && _owner->GetID() == 11)
	{
		m_vPos = { 4455,-167 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Enemy" && _owner->GetID() == 12)
	{
		m_vPos = { 4965,-167 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Enemy" && _owner->GetID() == 13)
	{
		m_vPos = { 5722,58 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Enemy" && _owner->GetID() == 14)
	{
		m_vPos = { 6257,58 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Enemy" && _owner->GetID() == 15)
	{
		m_vPos = { 7512,752 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Enemy" && _owner->GetID() == 16)
	{
		m_vPos = { 9504,762 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Enemy" && _owner->GetID() == 17)
	{
		m_vPos = { 10000,762 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Enemy" && _owner->GetID() == 18)
	{
		m_vPos = { 9800,762 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Enemy" && _owner->GetID() == 18)
	{
		m_vPos = { 9800,762 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "Enemy" && _owner->GetID() == 19)
	{
		m_vPos = { 3607,-872 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}

	if (_owner->GetName() == "EnemySniper" && _owner->GetID() == 0)
	{
		m_vPos = { -850,-1250 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "EnemySniper"&&_owner->GetID()==1)
	{
		m_vPos = { 930,-1250 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "EnemySniper" && _owner->GetID() == 2)
	{
		m_vPos = { 1387,-970 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "EnemySniper" && _owner->GetID() == 3)
	{
		m_vPos = { 2600,-1160 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "EnemySniper" && _owner->GetID() == 4)
	{
		m_vPos = { 2092,-472 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "EnemySniper" && _owner->GetID() == 5)
	{
		m_vPos = { 1733,-257 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "EnemySniper" && _owner->GetID() == 6)
	{
		m_vPos = { 3761,-662 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "EnemySniper" && _owner->GetID() == 7)
	{
		m_vPos = { 3796,-407 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "EnemySniper" && _owner->GetID() == 8)
	{
		m_vPos = { 3133,-27.5 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "EnemySniper" && _owner->GetID() == 9)
	{
		m_vPos = { 6554,57.5 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "EnemySniper" && _owner->GetID() == 10)
	{
		m_vPos = { 6063,327 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "EnemySniper" && _owner->GetID() == 11)
	{
		m_vPos = { 6806,752 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "EnemySniper" && _owner->GetID() == 12)
	{
		m_vPos = { 8060,752 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}
	if (_owner->GetName() == "EnemySniper" && _owner->GetID() == 13)
	{
		m_vPos = { 10775,762 };
		m_vScale = { 50,100 };
		m_fRot = 0.f;
	}

	//enemy bullet용
	if (_owner->GetName() == "e_bullet") 
	{
		m_vPos = { 0,0 };
		m_vScale = { 0,0 };
		m_fRot = 0.f;
	}
	//Boss용
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
	

	//test 황주현
	if (_owner->GetName() == "Enemy_TEST")
	{

		m_vPos = { 1920,90 };
		m_vScale = { 100,100 };
		m_fRot = 0.f;
	}

	if (_owner->GetName() == "BackGround")
	{
		m_vPos = { 0,0 };
		m_vScale = { 30,30 };
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

	//반전 행렬
	AEMtx33 reverseMtx;
	AEMtx33Scale(&reverseMtx, -1, 1);


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