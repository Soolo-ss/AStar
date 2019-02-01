#pragma once

#include "Common.h"
#include "AStarNode.h"

#include <queue>
#include <vector>
#include <unordered_map>

namespace AStar
{
	class AStarOpenByHeap
	{
	public:
		AStarOpenByHeap()
		{  }

		void Push(AStarNodeSharedPtr node)
		{
			heap_.push_back(node);
			std::push_heap(heap_.begin(), heap_.end(), [](const AStarNodeSharedPtr& lhs, const AStarNodeSharedPtr& rhs) {
				return lhs->GetF() > rhs->GetF() ? true : false;
			});
		}

		void Pop()
		{
			if (heap_.size() == 0)
				return;

			std::pop_heap(heap_.begin(), heap_.end(), [](const AStarNodeSharedPtr& lhs, const AStarNodeSharedPtr& rhs) {
				return lhs->GetF() > rhs->GetF() ? true : false;
			});
			heap_.pop_back();
		}

		AStarNodeSharedPtr Top()
		{
			if (heap_.size() != 0)
				return heap_[0];
			else
				return nullptr;
		}

		int Count()
		{
			return heap_.size();
		}

		void Clear()
		{
			heap_.clear();
		}

	private:
		std::vector<AStarNodeSharedPtr> heap_;
	};
}
