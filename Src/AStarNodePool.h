#pragma once

#include "Common.h"
#include "AStarNode.h"

#include <unordered_map>
#include <iostream>

namespace AStar
{
	class AStarNodePool
	{
	public:
		using AStarNodeKey = int;

		AStarNodePool()
		{  }

		AStarNodeSharedPtr GetNodeByKey(AStarNodeKey key)
		{
			auto find = mapping_.find(key);

			if (find == mapping_.end())
			{
				AStarNodeSharedPtr node = pools_.acquire();
				node->Clear();
				int x = key / 1000;
				int z = key - x * 1000;
				node->GetTile().SetX(x);
				node->GetTile().SetZ(z);

				mapping_.insert(std::make_pair(key, node));

				return node;
			}
			else
			{
				return find->second;
			}
		}

		void Clear()
		{
			/*
			for (auto node : mapping_)
			{
				node.second->Clear();
			}
			*/
			mapping_.clear();
		}

	private:
		std::unordered_map<AStarNodeKey, AStarNodeSharedPtr> mapping_;

		SmartObjectPool<AStarNode> pools_;
	};
}
