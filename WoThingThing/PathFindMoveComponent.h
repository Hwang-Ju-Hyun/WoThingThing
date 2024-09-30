#pragma once
#include "BaseComponent.h"
#include "header.h"
#include "TransComponent.h"

class GameObject;

class PathFindMoveComponent:public BaseComponent
{
public:
	PathFindMoveComponent(GameObject* _owner);
	~PathFindMoveComponent();
private:
	std::vector<int> FoundBestPath;
	int PathToPathIndex = 0;
public:
	void SetFoundBestPath(std::vector<int> _vecPath);
	const std::vector<int>& GetFoundBestPath();
	int GetPathToPathIndex();
	void PlusPathToPathIndex();
public:
	f32 CalculateDistance(AEVec2 _pos1, AEVec2 _scale1, AEVec2 _pos2, AEVec2 _scale2);
public:
	bool IsArrivedTargetNode(GameObject* _objPos, TransComponent::Node _nodePos);
public:
	virtual void Update()override;
};

