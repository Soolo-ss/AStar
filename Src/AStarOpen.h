#pragma once

#include "Common.h"
#include "AStarNode.h"

#include <map>
#include <unordered_map>
#include <memory>

namespace AStar
{
	class AStarOpen
	{
	public:
		AStarOpen()
		{  }

		void Push(AStarNodeSharedPtr node);

		//will extend AStarNode lifetime
		AStarNodeSharedPtr Top();

		void Pop();

		int Count()
		{
			return maps_.size();
		}

		void Clear()
		{
			maps_.clear();
			pools_.clear();
		}

		void Update(AStarNodeSharedPtr node);

		//
		AStarNodeSharedPtr GetNodeByTile(Tile& tile);

	private:
		std::multimap<int, AStarNodeSharedPtr> maps_;
		std::unordered_map<int, AStarNodeSharedPtr> pools_;
	};
}