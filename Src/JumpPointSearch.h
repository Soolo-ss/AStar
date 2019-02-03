#pragma once

#include "AStarNode.h"
#include "AStarNodePool.h"
#include "AStarMethod.h"

#include <vector>

namespace AStar
{
	class JumpPointSearch
	{
	public:
		std::vector<Tile> GetJumpPoints(Tile current, Tile star, Tile end);

	private:
		Tile Jump(Tile current, AStarDirection direction, Tile start, Tile end);

		bool IsNaturalNode(AStarNodeSharedPtr current, AStarNodeSharedPtr checkNode, AStarDirection direction);

		bool isForcedNode(AStarNodeSharedPtr current, AStarDirection direction);

	private:
		AStarMethod* method_;
	};
}