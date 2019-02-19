#include "AStarSearch.h"
#include "AStar.h"

#include <algorithm>

#include <iostream>

namespace AStar
{
	void AStarSearch::SetMethod(AStarMethod* method)
	{
		method_ = method;
		jumpSearcher_.SetMethod(method);
	}

	bool AStarSearch::Search(AStarTileSharedPtr start, AStarTileSharedPtr end, std::vector<Tile>& path, int maxStep)
	{
		if (*start == *end)
			return true;

		AStarTask task(start, end);

		AStarNodeSharedPtr startNode = pools_.GetNodeByTile(start);
		startNode->SetG(0);
		startNode->SetH(method_->GetH(start, end));
		startNode->SetState(AStarNodeState::Open);

		openList_.Push(startNode);

		do
		{
			AStarNodeSharedPtr node = openList_.Top();
			openList_.Pop();
			node->SetState(AStarNodeState::Close);

			AStarDirection parentDirection = node->GetParentDirection();

			std::vector<std::pair<int, AStarTileSharedPtr>> jumpPoints = jumpSearcher_.GetJumpPoints(node->GetTile(), startNode->GetTile(), end, parentDirection);

			for (auto jumpPoint : jumpPoints)
			{
				int cost = jumpPoint.first;

				AStarTestNode(jumpPoint.second, cost, node, task);
			}
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

			Tile tile;
			for (AStarNodeSharedPtr node = endNode; ; )
			{
				AStarNodeSharedPtr pnode = node->GetParent();

				if (pnode == nullptr)
					break;

				//get intermediary point
				std::vector<AStarNodeSharedPtr> internalNodes = GetInternalNodes(node, pnode);

				for (auto internalNode : internalNodes)
				{
					tile.SetX(internalNode->GetTile()->GetX());
					tile.SetZ(internalNode->GetTile()->GetZ());
					path.push_back(tile);
				}

				node = pnode;
			}

			path.push_back(*startNode->GetTile());
			std::reverse(path.begin(), path.end());
		}

		//清理所有资源
		openList_.Clear();
		pools_.Clear();

		return true;
	}

	std::vector<AStarNodeSharedPtr> AStarSearch::GetInternalNodes(AStarNodeSharedPtr start, AStarNodeSharedPtr end)
	{
		AStarTileSharedPtr startTile = start->GetTile();
		AStarTileSharedPtr endTile = end->GetTile();

		std::vector<AStarNodeSharedPtr> internalNodes;

		if (*startTile == *endTile)
			return internalNodes;

		int subx = endTile->GetX() - startTile->GetX();
		int subz = endTile->GetZ() - startTile->GetZ();

		AStarDirection direction = AStarDirection::None;
		int distance = 0;

		if (subx == 0)
		{
			distance = labs(subz);
			if (subz > 0)
				direction = AStarDirection::Up;
			else
				direction = AStarDirection::Down;
		}
		else if (subx < 0)
		{
			distance = labs(subx);
			if (subz == 0)
				direction = AStarDirection::Left;
			else if (subz < 0)
				direction = AStarDirection::LeftDown;
			else
				direction = AStarDirection::LeftUp;
		}
		else if (subx > 0)
		{
			distance = labs(subx);

			if (subz == 0)
				direction = AStarDirection::Right;
			else if (subz < 0)
				direction = AStarDirection::RightDown;
			else
				direction = AStarDirection::RightUp;
		}

		AStarTileSharedPtr tile = Tile::GetPool().acquire();
		tile->Copy(start->GetTile());

		for (int i = 0; i != distance; ++i)
		{
			AStarTileSharedPtr nextTile = Tile::GetPool().acquire();
			nextTile->Copy(tile);
			tile->AddDirectionOffset(direction);
			AStarNodeSharedPtr node = pools_.GetNodeByTile(nextTile);

			internalNodes.push_back(node);
		}

		return internalNodes;
	}
		
	void AStarSearch::AStarTestNode(AStarTileSharedPtr tile, int g, AStarNodeSharedPtr parent, AStarTask& task)
	{
		AStarNodeSharedPtr node = pools_.GetNodeByTile(tile);

		int newG = parent->GetG() + g;

		switch (node->GetState())
		{
		case AStarNodeState::Init:
			node->SetG(newG);
			node->SetH(method_->GetH(tile, task.endTile));
			node->SetParent(parent);
			node->SetState(AStarNodeState::Open);
			openList_.Push(node);

			if (*tile == *task.endTile)
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
		/*
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
			node->SetH(method_->GetH(tile, *task.endTile));
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
		*/
	}

	
}