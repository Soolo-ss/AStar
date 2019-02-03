#include "AStarOpen.h"

namespace AStar
{
	void AStarOpen::Push(AStarNodeSharedPtr node)
	{
		if (node == nullptr)
			return;

		maps_.insert(std::make_pair(node->GetF(), node));
		pools_.insert(std::make_pair(node->GetKey(), node));
	}

	void AStarOpen::Pop()
	{
		if (maps_.size() <= 0)
			return;

		pools_.erase(maps_.begin()->second->GetKey());
		maps_.erase(maps_.begin());
	}

	AStarNodeSharedPtr AStarOpen::Top()
	{
		auto first = maps_.begin();

		return first->second;
	}

	void AStarOpen::Update(AStarNodeSharedPtr node)
	{
		auto range = maps_.equal_range(node->GetF());

		if (range.first == maps_.end())
			return;

		for (auto i = range.first; i != range.second; ++i)
		{
			if (i->second->GetKey() == node->GetKey())
			{
				i->second = node;
			}
		}

		pools_[node->GetKey()] = node;
	}

	AStarNodeSharedPtr AStarOpen::GetNodeByTile(Tile& tile)
	{
		int key = tile.GetKey();

		auto find = pools_.find(key);

		if (find == pools_.end())
			return nullptr;

		return find->second;
	}
}