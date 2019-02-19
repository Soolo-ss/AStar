#pragma once

#include "AStarNode.h"
#include "AStarNodePool.h"
#include "AStarMethod.h"
#include "ObjectPool.h"

#include <vector>

namespace AStar
{
	class JumpPointSearch
	{
	public:
		std::vector<std::pair<int, AStarTileSharedPtr>> GetJumpPoints(AStarTileSharedPtr current, AStarTileSharedPtr start, AStarTileSharedPtr end, AStarDirection parentDirection);

		void SetMethod(AStarMethod* method)
		{
			method_ = method;
		}

	private:

		AStarTileSharedPtr Jump(AStarTileSharedPtr current, AStarDirection direction, AStarTileSharedPtr start, AStarTileSharedPtr end);
		
		AStarTileSharedPtr JumpDiagonal(AStarTileSharedPtr current, AStarDirection direction);

		AStarTileSharedPtr JumpOther(AStarTileSharedPtr current, AStarDirection direction);

		bool isForcedTile(AStarTileSharedPtr current, AStarDirection direction);

		void MoveTile(AStarTileSharedPtr current, AStarDirection direction);

		int GetJumpCost(AStarTileSharedPtr current, AStarTileSharedPtr target, AStarDirection direciton);

		std::vector<std::pair<AStarDirection, AStarTileSharedPtr>> GetNeighbours(AStarTileSharedPtr current, AStarDirection);

	private:
		AStarMethod* method_;
		AStarTileSharedPtr start_;
		AStarTileSharedPtr end_;
	};
}