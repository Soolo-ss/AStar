#pragma once

#include "Common.h"
#include "AStarMethod.h"
#include "AStarOpen.h"
#include "AStarOpenByHeap.h"
#include "AStarNodePool.h"
#include "JumpPointSearch.h"

#include <vector>
#include <unordered_map>

namespace AStar
{
	class AStarTask
	{
	public:
		AStarTask(AStarTileSharedPtr start, AStarTileSharedPtr end)
			: startTile(start), endTile(end), endNode(nullptr)
		{  }

	public:
		AStarTileSharedPtr startTile;
		AStarTileSharedPtr endTile;
		AStarNodeSharedPtr endNode;
	};

	class AStarSearch
	{
	public:
		AStarSearch()
		{ }

		void SetMethod(AStarMethod* method);

		bool Search(AStarTileSharedPtr start, AStarTileSharedPtr end, std::vector<Tile>& paths, int maxStep = 0);
	
	private:
		void AStarTestNode(AStarTileSharedPtr tile, int g, AStarNodeSharedPtr parent, AStarTask& task);

		std::vector<AStarNodeSharedPtr> GetInternalNodes(AStarNodeSharedPtr start, AStarNodeSharedPtr end);
		
	private:
		AStarMethod* method_;
		AStarOpenByHeap openList_;
		AStarNodePool pools_;
		JumpPointSearch jumpSearcher_;

		int maxStep_;
	};
}
