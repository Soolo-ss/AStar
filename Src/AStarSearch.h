#pragma once

#include "Common.h"
#include "AStarMethod.h"
#include "AStarOpen.h"
#include "AStarOpenByHeap.h"
#include "AStarNodePool.h"

#include <vector>
#include <unordered_map>

namespace AStar
{
	class AStarTask
	{
	public:
		AStarTask(Tile start, Tile end)
			: startTile(start), endTile(end), endNode(nullptr)
		{  }

	public:
		Tile startTile;
		Tile endTile;
		AStarNodeSharedPtr endNode;
	};

	class AStarSearch
	{
	public:
		AStarSearch()
		{ }

		void SetMethod(AStarMethod* method);

		bool Search(Tile& start, Tile& end, std::vector<Tile>& paths, int maxStep = 0);
		
		void AStarTestNode(Tile& tile, int g, AStarNodeSharedPtr parent, AStarTask& task);

	private:
		AStarMethod* method_;
		AStarOpenByHeap openList_;
		AStarNodePool pools_;

		int maxStep_;
	};
}
