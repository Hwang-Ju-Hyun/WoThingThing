#pragma once
#include "header.h"
#include "TransComponent.h"
#include <list>

class GameObject;

class NaveMeshManager
{
public:
	SINGLE(NaveMeshManager);
private:
	GameObject* player;
public:
	enum COST
	{
		NONE = 0,
		WALK = 1,
		JUMP = 4
	};


public:
	struct CostLink
	{
	public:
		enum COST
		{
			NONE = 0,
			WALK = 1,
			JUMP = 4,			
		};		
	public:
		virtual void Move(GameObject* _obj, TransComponent::Node _nodeInfo,int startNode,int endNode, TransComponent::Node _nextNode);
		virtual void ExtraParam(float _val);		
		int cost = 0;
	public:
		CostLink() {}
		virtual ~CostLink() {}
	};
	struct Walk :public CostLink
	{
		virtual void Move(GameObject* _obj,TransComponent::Node _nodeInfo,int startNode, int endNode, TransComponent::Node _nextNode) override;
	};
	struct Jump :public CostLink
	{
		virtual void Move(GameObject* _obj, TransComponent::Node _nodeInfo, int startNode, int endNode, TransComponent::Node _nextNode) override;
		virtual void ExtraParam(float _val) override;
		bool IsJumpDone = false;
		//Extra Params
		float Height=100.f;
	};	


public:
	CostLink* costLink;
private:
	std::vector<TransComponent::Node> m_vecNode;
	std::vector<std::vector<std::pair<int/*NodeID*/, enum COST/*cost*/>>> m_vecLinktemp;
	std::vector<std::vector<std::pair<int/*NodeID*/, CostLink*/*cost*/>>> m_vecLink;
public:
	std::vector<bool> visited;
private:
	std::vector<int> FoundedPath;
	std::vector<int> path;
	float minCost;
	float currentCost;
public:
	TransComponent::Node AddNode(TransComponent::Node Node);
	const std::vector<TransComponent::Node>& GetallNode();

	const std::vector<std::vector<std::pair<int, enum COST>>>& GetvecLink_temp(){return m_vecLinktemp;}


	const std::vector<std::vector<std::pair<int, CostLink*>>>& GetvecLink() { return m_vecLink; }
	//==========NEVER NEVER TOUCH DOWN FUNCTION============
	void FindShortestPath(int startNode,int endNode,int currentCost);	
	//==========NEVER NEVER TOUCH UPPER FUNCTION============
public:
	void CreateLinkTable();
	void ClearNode();
public:	
	void DrawAllNode();
	void DrawNode(float bottomleft_x, float bottomleft_y, float topRight_x, float topRight_y, float r, float g, float b);
public:
	void SetMinCost(float _cost) { minCost = _cost; }
	float GetMinCost() { return minCost; }
	std::vector<int> GetPath(){ return FoundedPath; }	
public:	
	void SetPlayer(GameObject* _player);
	int FindObjectNode(GameObject* _player);
public:
	double CalculateDistanceNode(AEVec2 _playerPos,AEVec2 _nodePos);
};