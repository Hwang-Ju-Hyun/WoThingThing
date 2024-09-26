#include "NaveMeshManager.h"
#include "RigidBodyComponent.h"
#include "GameObject.h"
#include "TransComponent.h"
#include "ColliderManager.h"
#include "PathFindMoveComponent.h"

#include"PlayerComponent.h"
#include"GoManager.h"
#include"EnemyAnimationComponent.h"

bool NaveMeshManager::isStunned = false;

NaveMeshManager::NaveMeshManager()
{
	//m_vecNode	
	minCost = 100000.f;
	currentCost = 0.f;
}

NaveMeshManager::~NaveMeshManager()
{		
	ClearNode();
}

TransComponent::Node NaveMeshManager::AddNode(TransComponent::Node Node)
{
	m_vecNode.push_back(Node);
	visited.push_back(false);
	return m_vecNode.back();
}

const std::vector<TransComponent::Node>& NaveMeshManager::GetallNode()
{
	return m_vecNode;
}

//==========NEVER NEVER TOUCH DOWN FUNCTION============
void NaveMeshManager::FindShortestPath(int startNode, int endNode,int currentCost)
{
	//만약 해당 노드까지 탐색하였다면
	if (startNode == endNode)
	{
		if (currentCost < minCost)
		{			
			minCost = currentCost;
			FoundedPath = path;
			FoundedPath.push_back(endNode);
		}
		return;
	}
	//방문 처리
	visited[startNode] = true;
	//방문했으니깐 path에 넣어주고
	path.push_back(startNode);

	for (auto link : m_vecLink[startNode])
	{
		int nextNode = link.first;

		int cost=-1;
		Walk* costWalk = dynamic_cast<Walk*>(link.second);
		if (costWalk != nullptr)
		{
			cost = 1;
		}
		else
		{
			Jump* costJump = dynamic_cast<Jump*>(link.second);
			if (costJump != nullptr)
			{
				cost = 4;
			}		
		}		
		if (!visited[nextNode])
		{
			FindShortestPath(nextNode, endNode,currentCost+cost);
		}
	}
	//중요
	//다 탐색하였으면 다시 하나씩 빼줘야함
	path.pop_back();
	//빼줬으면 visited=false로 가야함
	visited[startNode] = false;
}
//==========NEVER NEVER TOUCH UPPER FUNCTION============

void NaveMeshManager::CreateLinkTable()
{
	
	Walk* walk = new Walk;
	Jump* jump = new Jump;

	std::vector<std::pair<int/*nodeID*/, CostLink*>> link0;
	link0.push_back({ 0,walk });
	link0.push_back({ 1,walk });

	std::vector<std::pair<int/*nodeID*/, CostLink*>> link1;
	link1.push_back({ 0, walk });
	link1.push_back({ 12,jump });
	link1.push_back({ 2,walk });

	std::vector<std::pair<int/*nodeID*/, CostLink*>> link2;
	link2.push_back({ 3, walk });
	link2.push_back({ 12,jump });
	link2.push_back({ 1,walk });

	std::vector<std::pair<int/*nodeID*/, CostLink*>> link3;
	link3.push_back({ 2, walk });
	link3.push_back({ 4, walk });
	link3.push_back({ 9, jump });

	std::vector<std::pair<int/*nodeID*/, CostLink*>> link4;
	link4.push_back({ 3, walk });
	link4.push_back({ 6, walk });

	std::vector<std::pair<int/*nodeID*/, CostLink*>> link5;
	link5.push_back({ 6, walk });
	link5.push_back({ 4, walk });

	std::vector<std::pair<int/*nodeID*/, CostLink*>> link6;
	link6.push_back({ 5, walk });
	link6.push_back({ 7, walk });
	link6.push_back({ 8, jump });

	std::vector<std::pair<int/*nodeID*/, CostLink*>> link7;
	link7.push_back({ 6, walk });


	std::vector<std::pair<int/*nodeID*/, CostLink*>> link8;
	link8.push_back({ 5, walk });
	link8.push_back({ 9, walk });
	link8.push_back({ 17, jump });


	std::vector<std::pair<int/*nodeID*/, CostLink*>> link9;
	link9.push_back({ 4, walk });
	link9.push_back({ 8, walk });
	link9.push_back({ 10, jump });
	link9.push_back({ 17, jump });


	std::vector<std::pair<int/*nodeID*/, CostLink*>> link10;
	link10.push_back({ 4, walk });
	link10.push_back({ 11, walk });
	link10.push_back({ 15, jump });

	std::vector<std::pair<int/*nodeID*/, CostLink*>> link11;
	link11.push_back({ 12, jump });
	link11.push_back({ 2,  walk });
	link11.push_back({ 10,  walk });
	link11.push_back({ 13,  jump });

	std::vector<std::pair<int/*nodeID*/, CostLink*>> link12;
	link12.push_back({ 2, walk });
	link12.push_back({ 1, walk });
	link12.push_back({ 11, jump });


	std::vector<std::pair<int/*nodeID*/, CostLink*>> link13;
	link13.push_back({ 12, walk });
	link13.push_back({ 1, walk });
	link13.push_back({ 14, walk });

	std::vector<std::pair<int/*nodeID*/, CostLink*>> link14;
	link14.push_back({ 20, jump });
	link14.push_back({ 13, walk });
	link14.push_back({ 0, walk });
	link14.push_back({ 11, jump });


	std::vector<std::pair<int/*nodeID*/, CostLink*>> link15;
	link15.push_back({ 10, walk });
	link15.push_back({ 16, walk });

	std::vector<std::pair<int/*nodeID*/, CostLink*>> link16;
	link16.push_back({ 9, walk });
	link16.push_back({ 4, walk });


	std::vector<std::pair<int/*nodeID*/, CostLink*>> link17;
	link17.push_back({ 8, walk });
	link17.push_back({ 18, jump });
	link17.push_back({ 5, walk });
	link17.push_back({ 16, jump });


	std::vector<std::pair<int/*nodeID*/, CostLink*>> link18;
	link18.push_back({ 17, walk });
	link18.push_back({ 19, jump });
	link18.push_back({ 7, walk });

	std::vector<std::pair<int/*nodeID*/, CostLink*>> link19;
	link19.push_back({ 18, walk });
	link19.push_back({ 7, walk });

	std::vector<std::pair<int/*nodeID*/, CostLink*>> link20;
	link20.push_back({ 20, walk });
	link20.push_back({ 14, walk });
	link20.push_back({ 0, walk });

	std::vector<std::pair<int/*nodeID*/, CostLink*>> link21;
	link21.push_back({ 4, walk });
	link21.push_back({ 3, walk });

	m_vecLink.push_back(link0);
	m_vecLink.push_back(link1);
	m_vecLink.push_back(link2);
	m_vecLink.push_back(link3);
	m_vecLink.push_back(link4);
	m_vecLink.push_back(link5);
	m_vecLink.push_back(link6);
	m_vecLink.push_back(link7);
	m_vecLink.push_back(link8);
	m_vecLink.push_back(link9);
	m_vecLink.push_back(link10);
	m_vecLink.push_back(link11);
	m_vecLink.push_back(link12);
	m_vecLink.push_back(link13);
	m_vecLink.push_back(link14);
	m_vecLink.push_back(link15);
	m_vecLink.push_back(link16);
	m_vecLink.push_back(link17);
	m_vecLink.push_back(link18);
	m_vecLink.push_back(link19);
	m_vecLink.push_back(link20);
	m_vecLink.push_back(link21);
	
}

void NaveMeshManager::ClearNode()
{
	std::map<CostLink*, bool> m_map;
	for (int i = 0; i < m_vecLink.size(); i++)
	{
		for (int j = 0; j < m_vecLink[i].size(); j++)
		{
			auto a = m_map.find(m_vecLink[i][j].second);
			if (a == m_map.end())
			{
				delete m_vecLink[i][j].second;
				m_map.insert({ m_vecLink[i][j].second,true });
				m_vecLink[i][j].second = nullptr;
			}
		}
	}
    m_vecNode.clear();
}


void NaveMeshManager::DrawAllNode()
{	
}

void NaveMeshManager::DrawNode(float bottomleft_x, float bottomleft_y, float topRight_x, float topRight_y, float r, float g, float b)
{
	ColliderManager::GetInst()->DrawRect(bottomleft_x, bottomleft_y, topRight_x, topRight_y, r, g, b);
	return;
}


void NaveMeshManager::SetPlayer(GameObject* _player)
{
	player = _player;
}

int NaveMeshManager::FindObjectNode(GameObject* _player)
{
	TransComponent* player_trs = dynamic_cast<TransComponent*>(_player->FindComponent("Transform"));
	int nodeNum = 0;
	if (player_trs != nullptr)
	{
		double minDistance = 1000000;				
		for (int i = 0; i < m_vecNode.size(); i++)
		{			
			double distance = CalculateDistanceNode(player_trs->GetPos(), m_vecNode[i].node_pos);
			
			if (minDistance > distance)
			{
				minDistance = distance;
				nodeNum=i;
			}
		}
	}	
	return nodeNum;
}

double NaveMeshManager::CalculateDistanceNode(AEVec2 _playerPos, AEVec2 _nodePos)
{
	double distance = std::sqrt(std::pow(_playerPos.x - _nodePos.x,2) + std::pow(_playerPos.y - _nodePos.y,2));
	return distance;
}


void NaveMeshManager::Walk::Move(GameObject* _obj, TransComponent::Node _nodeInfo, int startNode, int endNode, TransComponent::Node _nextNode, GameObject* _player)
{
	TransComponent* obj_trs = static_cast<TransComponent*>(_obj->FindComponent("Transform"));
	RigidBodyComponent* obj_rb = static_cast<RigidBodyComponent*>(_obj->FindComponent("RigidBody"));
	EnemyAnimationComponent* obj_ani = (EnemyAnimationComponent*)(_obj->FindComponent("EnemyAnimation"));
	PlayerComponent* player_comp = (PlayerComponent*)_player->FindComponent("PlayerComp");
	AEVec2 objPos = obj_trs->GetPos();
	AEVec2 nodePos = _nodeInfo.node_pos;
	if (endNode)//n+1 is Valid
	{
		for (auto obj : GoManager::GetInst()->Allobj())
		{
			if (obj->GetName() == "Enemy_TEST")
			{				
				// 이동 방향 계산
				if (obj->GetSturn() == false && _obj->KnockBack == false)
				{
					float dt = AEFrameRateControllerGetFrameTime();
					AEVec2 direction = { _nextNode.node_pos.x - _nodeInfo.node_pos.x, 0 };
					AEVec2 normalize_dir;
					AEVec2Normalize(&normalize_dir, &direction);
					if (player_comp->GetManiActive())
					{
						obj_trs->AddPos({ normalize_dir.x * dt * 10.f, 0.f });
					}
					else
					{
						obj_trs->AddPos({ normalize_dir.x * 10.f, 0.f });
					}
					//obj_trs->AddPos({ normalize_dir.x * 10.f, 0.f }); // 이동
					obj_ani->ChangeAnimation("BossRun", 1, 6, 6, 0.1);
				}
				else
				{
					obj_trs->AddPos({ 0.f,0.f });
				}				
			}
			
		}
	}
}

void NaveMeshManager::Jump::Move(GameObject* _obj, TransComponent::Node _nodeInfo, int startNode, int endNode, TransComponent::Node _nextNode, GameObject* _player)
{
	TransComponent* obj_trs = static_cast<TransComponent*>(_obj->FindComponent("Transform"));
	RigidBodyComponent* obj_rb = static_cast<RigidBodyComponent*>(_obj->FindComponent("RigidBody"));
	PathFindMoveComponent*obj_pf= static_cast<PathFindMoveComponent*>(_obj->FindComponent("PathFindMove"));
	PlayerComponent* player_comp = (PlayerComponent*)_player->FindComponent("PlayerComp");
	AEVec2 objPos = obj_trs->GetPos();
	AEVec2 objScale = obj_trs->GetScale();
	AEVec2 nodePos = _nodeInfo.node_pos;	
	AEVec2 nodeScale = { 50.f,70.f };
	//이 부분에 대한 고민 쉬프트를 누르면 점프가 느려지게 하는데 높이는 그만큼 오르게 만들게 해야함  
	
	if (ColliderManager::GetInst()->IsCollision(_obj, _nodeInfo)&&IsJumpDone==false)
	{
		if ( _nodeInfo.node_id == 9
			|| _nodeInfo.node_id == 8)
		{
			Height = 570;
		}
		else if (_nodeInfo.node_id == 1)
		{
			Height = 650;
		}
		else if(_nodeInfo.node_id == 2)
		{
			Height = 670;
		}
		else if(_nodeInfo.node_id==12)
		{
			Height =900;
		}
		else if (_nodeInfo.node_id == 4 || _nodeInfo.node_id == 5)
		{
			Height = 550;
		}
		else if (_nodeInfo.node_id == 11 || _nodeInfo.node_id == 10)
		{
			Height = 540;
		}
		if (_obj->GetSturn() == false && _obj->KnockBack == false)
		{
			obj_rb->jump(Height);
			//Height = 600;
			IsJumpDone = true;
		}
		else
		{
			obj_trs->AddPos({ 0.f,0.f });
		}
	}
	else
	{
		if (_obj->GetSturn() == false && _obj->KnockBack == false)
		{
			AEVec2 direction = { _nextNode.node_pos.x - _nodeInfo.node_pos.x, _nextNode.node_pos.y - _nodeInfo.node_pos.y };
			AEVec2 normalize_dir;
			AEVec2Normalize(&normalize_dir, &direction);
			float dt = AEFrameRateControllerGetFrameTime();
			if (player_comp->GetManiActive())
			{
				obj_trs->AddPos({ normalize_dir.x * dt * 10.f, 0.f });
			}
			else
			{
				obj_trs->AddPos({ normalize_dir.x * 10.f, 0.f });
			}

			//obj_rb->AddVelocity(normalize_dir.x * 500.f, normalize_dir.y * 500.f);
			IsJumpDone = false;
		}		
	}
		
	//ERROR I have to fix CalculateDistance
	/*float epsilon = std::numeric_limits<float>::epsilon();
	
	if (obj_pf->CalculateDistance(objPos,objScale,nodePos,nodeScale) <= epsilon)
	{		
		obj_rb->jump(900);
	}*/
}

void NaveMeshManager::Jump::ExtraParam(float _val)
{
}

void NaveMeshManager::CostLink::Move(GameObject* _obj, TransComponent::Node _nodeInfo, int startNode, int endNode, TransComponent::Node _nextNode, GameObject* _player)
{
}

void NaveMeshManager::CostLink::ExtraParam(float _val)
{
}
