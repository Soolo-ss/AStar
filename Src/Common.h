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
}
