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

		AStarNodeSharedPtr GetNodeByTile(AStarTileSharedPtr tile)
		{
			auto find = dense_maps_.find(tile->GetKey());

			if (find == dense_maps_.end())
			{
				AStarNodeSharedPtr node = pools_.acquire();
				node->Clear();
				node->SetTile(tile);

				dense_maps_.insert(std::make_pair(tile->GetKey(), node));

				return node;
			}
			else
			{
				return find->second;
			}
		}

		void Clear()
		{
			dense_maps_.clear();
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
