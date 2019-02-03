#pragma once

#include "Common.h"
#include "AStarNode.h"

#include <unordered_map>
#include <iostream>

#include <sparsehash/dense_hash_map.h>

#define DENSE_HASH_MAP_EMPTY_KEY 100000000

namespace AStar
{
	class AStarNodePool
	{
	public:
		using AStarNodeKey = int;

		AStarNodePool()
		{
			dense_maps_.set_empty_key(DENSE_HASH_MAP_EMPTY_KEY);
		}

		AStarNodeSharedPtr GetNodeByKey(AStarNodeKey key)
		{
			/*
			auto find = mapping_.find(key);

			if (find == mapping_.end())
			{
				AStarNodeSharedPtr node = pools_.acquire();
				node->Clear();
				int x = key / 10000;
				int z = key - x * 10000;
				node->GetTile().SetX(x);
				node->GetTile().SetZ(z);

				mapping_.insert(std::make_pair(key, node));

				return node;
			}
			else
			{
				return find->second;
			}
			*/
				
			auto find = dense_maps_.find(key);

			if (find == dense_maps_.end())
			{
				AStarNodeSharedPtr node = pools_.acquire();
				node->Clear();
				int x = key / 1000;
				int z = key - x * 1000;
				node->GetTile().SetX(x);
				node->GetTile().SetZ(z);

				dense_maps_.insert(std::make_pair(key, node));

				return node;
			}
			else
			{
				return find->second;
			}
		}

		void Clear()
		{
			for (auto node : dense_maps_)
			{
				node.second->Clear();
			}
			//dense_maps_.clear();
			//mapping_.clear();
		}

	private:
		struct AStarNodeKeyComparer
		{
			bool operator()(const AStarNodeKey& lhs, const AStarNodeKey& rhs)
			{
				return lhs == rhs;
			}
		};

	private:
		std::unordered_map<AStarNodeKey, AStarNodeSharedPtr> mapping_;

		google::dense_hash_map<AStarNodeKey, AStarNodeSharedPtr> dense_maps_;

		SmartObjectPool<AStarNode> pools_;
	};
}
