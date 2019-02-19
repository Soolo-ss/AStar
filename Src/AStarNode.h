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
			  tile_(Tile::GetPool().acquire()),		//defualt acquire from pools
			  parent_(),
			  state_(AStarNodeState::Init)
		{	}

		AStarNode(AStarTileSharedPtr tile)
			: g_(0), 
			  h_(0),
			  tile_(tile),					//copy other tile to self
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

			/*
			if (tile_ != nullptr)
			{
				tile_->SetX(0);
				tile_->SetZ(0);
			}
			*/

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

		AStarDirection GetParentDirection() 
		{
			if (!parent_.expired())
			{
				int subx = this->GetTile()->GetX() - parent_.lock()->GetTile()->GetX();
				int subz = this->GetTile()->GetZ() - parent_.lock()->GetTile()->GetZ();

				if (subz < 0)
				{
					if (subx == 0)
						return AStarDirection::Down;
					else if (subx < 0)
						return AStarDirection::LeftDown;
					else
						return AStarDirection::RightDown;
				}
				else if (subz > 0)
				{
					if (subx == 0)
						return AStarDirection::Up;
					else if (subx < 0)
						return AStarDirection::LeftUp;
					else
						return AStarDirection::RightUp;
				}
				else
				{
					if (subx == 0)
						return AStarDirection::None;
					else if (subx < 0)
						return AStarDirection::Left;
					else
						return AStarDirection::Right;
				}
			}

			return AStarDirection::None;
		}

		AStarTileSharedPtr GetTile() { return tile_; }

		void SetTile(AStarTileSharedPtr tile)
		{
			tile_ = tile;
		}

		int GetKey() const { return tile_->GetKey(); }

	private:
		int g_;
		int h_;
		AStarTileSharedPtr tile_;
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