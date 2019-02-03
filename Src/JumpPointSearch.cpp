#include "JumpPointSearch.h"

namespace AStar
{
	std::vector<Tile> JumpPointSearch::GetJumpPoints(Tile current, Tile start, Tile end) 
	{
		std::vector<Tile> jumpPoints;

		Tile tile;
		AStarDirection direction;
		Tile neighbour;
		Tile jumpNode;

		for (int i = 0; i != static_cast<int>(AStarDirection::Max); ++i)
		{
			tile = current;
			direction = static_cast<AStarDirection>(i);
			tile.AddDirectionOffset(direction);

			if (!method_->CanMove(current, tile))
				continue;

			jumpNode = Jump(current, direction, start, end);

			if (jumpNode)
				jumpPoints.push_back(jumpNode);
		}

		return jumpPoints;
	}

	Tile JumpPointSearch::Jump(Tile current,  AStarDirection direction, Tile start, Tile end)
	{
		if (current == end)
			return current;

		if (IsDiagonal(direction))
		{
			//check forced neighbour
			Tile leftTile(current);
			leftTile.AddDirectionOffset(AStarDirection::Left);

			Tile downTile(current);
			downTile.AddDirectionOffset(AStarDirection::Down);

			if ((!method_->CanMove(current, leftTile)) || (!method_->CanMove(current, downTile)))
			{
				return current;
			}

			auto straighDirection = ResolveDiagonalDirection(direction);
			if (Jump(current, straighDirection.first, start, end) != nullptr ||
				Jump(current, straighDirection.second, start, end) != nullptr)
			{
				return current;
			}
		}
		else
		{
			if (IsVertical)
			{
				//check vertical forced neighbour
				Tile leftTile(current);
				leftTile.AddDirectionOffset(AStarDirection::Left);

				Tile rightTile(current);
				rightTile.AddDirectionOffset(AStarDirection::Right);

				if ((!method_->CanMove(current, leftTile)) || (!method_->CanMove(current, rightTile)))
					return current;
			}
			else
			{
				//check horizontal forced neighbour
				Tile upTile(current);
				upTile.AddDirectionOffset(AStarDirection::Up);

				Tile downTile(current);
				downTile.AddDirectionOffset(AStarDirection::Down);

				//up and down is blocked, so n has neighbour is forced
				if ((!method_->CanMove(current, upTile)) || (!method_->CanMove(current, downTile)))
					return current;
			}
		}

		Tile nextTile(current);
		nextTile.AddDirectionOffset(direction);

		return Jump(nextTile, direction, start, end);
	}

	bool JumpPointSearch::IsNaturalNode(AStarNodeSharedPtr current, AStarNodeSharedPtr checkNode, AStarDirection direction)
	{
		Tile currentTile(current->GetTile());

		currentTile.AddDirectionOffset(direction);

		if (currentTile == checkNode->GetTile())
			return true;
		else
			return false;
}