#include "Tail.h"

namespace AStar
{
	void Tile::AddDirectionOffset(AStarDirection direction)
	{
		switch (direction)
		{
		case AStar::AStarDirection::Up:
			z_ += 1;
			break;
		case AStar::AStarDirection::RightUp:
			x_ += 1;
			z_ += 1;
			break;
		case AStar::AStarDirection::Right:
			x_ += 1;
			break;
		case AStar::AStarDirection::RightDown:
			x_ += 1;
			z_ -= 1;
			break;
		case AStar::AStarDirection::Down:
			z_ -= 1;
			break;
		case AStar::AStarDirection::LeftDown:
			x_ -= 1;
			z_ -= 1;
			break;
		case AStar::AStarDirection::Left:
			x_ -= 1;
			break;
		case AStar::AStarDirection::LeftUp:
			x_ -= 1;
			z_ += 1;
			break;
		default:
			break;
		}
	}

	AStarDirection GetFromDirection(Tile parent)
	{
		std::pair<int, int> directionNum;
	}
}
