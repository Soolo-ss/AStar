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

	//小心使用
	//每加1代表右转45度
	inline AStarDirection RotateDirection(AStarDirection direction, uint32_t degree)
	{
		degree = degree % 8;

		int directionIndex = static_cast<int>(direction) + degree;

		if (directionIndex >= 8)
			directionIndex -= 8;

		return static_cast<AStarDirection>(directionIndex);
	}

	inline AStarDirection ReverseDirection(AStarDirection direction)
	{
		switch (direction)
		{
		case AStar::AStarDirection::Up:
			return AStarDirection::Down;
		case AStar::AStarDirection::RightUp:
			return  AStarDirection::LeftDown;
		case AStar::AStarDirection::Right:
			return AStarDirection::Left;
		case AStar::AStarDirection::RightDown:
			return AStarDirection::LeftUp;
		case AStar::AStarDirection::Down:
			return AStarDirection::Up;
		case AStar::AStarDirection::LeftDown:
			return AStarDirection::RightUp;
		case AStar::AStarDirection::Left:
			return AStarDirection::Right;
		case AStar::AStarDirection::LeftUp:
			return AStarDirection::RightDown;
		default:
			break;
		}

		return AStarDirection::None;
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
