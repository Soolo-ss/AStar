#pragma once

#include "ObjectPool.h"

namespace AStar
{
	enum class AStarNodeState
	{
		Init,
		Open,
		Close
	};

	enum class AStarDirection
	{
		Up,
		RightUp,
		Right,
		RightDown,
		Down,
		LeftDown,
		Left,
		LeftUp,

		Max,
		None
	};

	enum class AStarSearchMethod
	{
		PathSearchMethod,
		GuildPathSearchMethod
	};

	inline bool IsDiagonal(AStarDirection direction)
	{
		switch (direction)
		{
		case AStar::AStarDirection::Up:
		case AStar::AStarDirection::Right:
		case AStar::AStarDirection::Down:
		case AStar::AStarDirection::Left:
			return false;
		default:
			break;
		}

		return true;
	}

	inline bool IsVertical(AStarDirection direction)
	{
		switch (direction)
		{
		case AStar::AStarDirection::Up:
		case AStar::AStarDirection::Down:
			return true;
		default:
			break;
		}

		return false;
	}

	inline bool IsHorizontal(AStarDirection direction)
	{
		switch (direction)
		{
		case AStar::AStarDirection::Right:
		case AStar::AStarDirection::Left:
			return true;
		default:
			break;
		}

		return false;
	}

	inline std::pair<AStarDirection, AStarDirection> ResolveDiagonalDirection(AStarDirection direction)
	{
		std::pair<AStarDirection, AStarDirection> directions;
		
		switch (direction)
		{
		case AStar::AStarDirection::RightUp:
			directions.first = AStarDirection::Right;
			directions.second = AStarDirection::Up;
			break;
		case AStar::AStarDirection::RightDown:
			directions.first = AStarDirection::Right;
			directions.second = AStarDirection::Down;
			break;
		case AStar::AStarDirection::LeftDown:
			directions.first = AStarDirection::Left;
			directions.second = AStarDirection::Down;
			break;
		case AStar::AStarDirection::LeftUp:
			directions.first = AStarDirection::Left;
			directions.second = AStarDirection::Up;
			break;
		default:
			directions.first = AStarDirection::None;
			directions.second = AStarDirection::None;
			break;
		}

		return directions;
	}
}
