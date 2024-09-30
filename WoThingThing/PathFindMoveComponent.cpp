#include "PathFindMoveComponent.h"
#include "GameObject.h"
#include "TransComponent.h"
#include "ColliderManager.h"
#include <limits>

PathFindMoveComponent::PathFindMoveComponent(GameObject* _owner)
	:BaseComponent(_owner)
{
	PathToPathIndex = 0;
}

PathFindMoveComponent::~PathFindMoveComponent()
{

}

void PathFindMoveComponent::SetFoundBestPath(std::vector<int> _vecPath)
{
	FoundBestPath = _vecPath;
}

const std::vector<int>& PathFindMoveComponent::GetFoundBestPath()
{
	return FoundBestPath;
}

int PathFindMoveComponent::GetPathToPathIndex()
{
	return PathToPathIndex;
}

void PathFindMoveComponent::PlusPathToPathIndex()
{
	PathToPathIndex++;
}

f32 PathFindMoveComponent::CalculateDistance(AEVec2 _pos1,AEVec2 _scale1, AEVec2 _pos2, AEVec2 _scale2)
{
	f32 distance = static_cast<f32>(std::sqrt(std::pow(0, 2) + std::pow((_pos1.y-(_scale1.y/2.f)) - (_pos2.y+(_scale2.y/2.f)), 2)));
	return distance;
}

bool PathFindMoveComponent::IsArrivedTargetNode(GameObject* _objPos, TransComponent::Node _nodePos)
{
	TransComponent* obj_trs = static_cast<TransComponent*>(_objPos->FindComponent("Transform"));
	AEVec2 objPos = obj_trs->GetPos();
	AEVec2 objScale = obj_trs->GetScale();
	AEVec2 nodeScale = { 50.f,70.f };
	float epsilon = std::numeric_limits<float>::epsilon();
	/*if (CalculateDistance(objPos, objScale, _nodePos, nodeScale) <= epsilon)
	{
		return true;
	}*/
	if (ColliderManager::GetInst()->IsCollision(_objPos, _nodePos))
		return true;
	return false;
}

void PathFindMoveComponent::Update()
{
	
}
