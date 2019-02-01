#pragma once

#include <memory>

#include "Common.h"
#include "Tail.h"

namespace AStar
{
	class AStarNode;

	using AStarNodeUniquePtr = SmartObjectPool<AStarNode>::ReturnObjectPtrType;
	using AStarNodeSharedPtr = std::shared_ptr<AStarNode>;
	using AStarNodeWeakPtr = std::weak_ptr<AStarNode>;

	class AStarNode
	{
	public:
		//default constructor used for object pool
		AStarNode()
			: g_(0),
			  h_(0),
			  tile_(),
			  parent_(),
			  state_(AStarNodeState::Init)
		{  }

		AStarNode(Tile tile)
			: g_(0), 
			  h_(0),
			  tile_(tile),
			  parent_(),
			  state_(AStarNodeState::Init)
		{  }

		int GetF() const
		{
			return g_ + h_;
		}

		void Clear()
		{
			parent_.reset();
			state_ = AStarNodeState::Init;
			GetTile().SetX(0);
			GetTile().SetZ(0);
			g_ = 0;
			h_ = 0;
		}

		void SetG(int g) { g_ = g; }

		void SetH(int h) { h_ = h; }

		void SetState(AStarNodeState stat) { state_ = stat; }

		void SetParent(AStarNodeSharedPtr parent)
		{ 
			parent_ = parent;
		}

		int GetG() const { return g_; }

		int GetH() const { return h_; }

		AStarNodeState GetState() const { return state_; }

		AStarNodeSharedPtr GetParent() const
		{
			if (!parent_.expired())
			{
				return parent_.lock();
			}
			else
			{
				return nullptr;
			}
		}

		Tile& GetTile() { return tile_; }

		int GetKey() const { return tile_.GetX() * 1000 + tile_.GetZ(); }

	private:
		int g_;
		int h_;
		Tile tile_;
		AStarNodeWeakPtr parent_;
		AStarNodeState state_;
	};

	struct AStarNodeComparer
	{
		bool operator()(const AStarNode& lhs, const AStarNode& rhs)
		{
			return lhs.GetF() > rhs.GetF();
		}
	};
}

;