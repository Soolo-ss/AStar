#include "AStarSearch.h"
#include "AStar.h"

#include <algorithm>

#include <iostream>

namespace AStar
{
	void AStarSearch::SetMethod(AStarMethod* method)
	{
		method_ = method;
	}

	bool AStarSearch::Search(Tile& start, Tile& end, std::vector<Tile>& path, int maxStep)
	{
		if (start == end)
			return true;

		AStarTask task(start, end);

		AStarNodeSharedPtr startNode = pools_.GetNodeByKey(start.GetKey());
		startNode->SetG(0);
		startNode->SetH(method_->GetH(start, end));
		startNode->SetState(AStarNodeState::Open);

		openList_.Push(startNode);

		do
		{
			AStarNodeSharedPtr node = openList_.Top();
			openList_.Pop();
			node->SetState(AStarNodeState::Close);

			jumpSearcher_.GetJumpPoints(node, startNode, end, pools_, method_);

			/*
			for (int directionIndex = 0; directionIndex != (int)AStarDirection::Max; ++directionIndex)
			{
				//Copy, new tile
				Tile tmpOffsetTile(node->GetTile());
				AStarDirection direction = static_cast<AStarDirection>(directionIndex);
				tmpOffsetTile.AddDirectionOffset(direction);
				AStarTestNode(tmpOffsetTile, method_->GetG(node->GetTile(), direction), node, task);
			}
			*/

			if (task.endNode != nullptr)
			{
				break;
			}
		} while (!(openList_.Count() <= 0) || (maxStep > 0 && openList_.Count() > maxStep));

		AStarNodeSharedPtr endNode = task.endNode;

		if (endNode != nullptr)
		{
			path.clear();

			for (AStarNodeSharedPtr node = endNode; node != nullptr; node = node->GetParent())
			{
				path.push_back(node->GetTile());
			}

			std::reverse(path.begin(), path.end());
		}

		//清理所有资源
		openList_.Clear();
		pools_.Clear();

		return true;
	}

	void AStarSearch::AStarTestNode(Tile& tile, int g, AStarNodeSharedPtr parent, AStarTask& task)
	{
		if (!method_->CanMove(parent->GetTile(), tile))
		{
			return;
		}

		AStarNodeSharedPtr node = pools_.GetNodeByKey(tile.GetKey());

		AStarNodeSharedPtr ppNode = parent->GetParent();
		if (ppNode != nullptr)
		{
			Tile ppTile = ppNode->GetTile();
			Tile pTile = parent->GetTile();
			if ((ppTile - pTile) != (pTile - tile))
			{
				g += method_->GetGOnTurn();
			}
		}

		int newG = parent->GetG() + g;

		switch (node->GetState())
		{
		case AStarNodeState::Init:
			node->SetG(newG);
			node->SetH(method_->GetH(tile, task.endTile));
			node->SetParent(parent);
			node->SetState(AStarNodeState::Open);
			openList_.Push(node);

			if (tile == task.endTile)
			{
				task.endNode = node;
			}
			break;
		case AStarNodeState::Open:
			if (node->GetG() > newG)
			{
				node->SetG(newG);
				node->SetParent(parent);
			}
			break;
		case AStarNodeState::Close:
			break;
		default:
			break;
		}
	}

	
}