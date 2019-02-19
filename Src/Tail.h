#pragma once

#include "Common.h"

namespace AStar
{
	class Tile;

	using AStarTileSharedPtr = std::shared_ptr<Tile>;

	class Tile
	{
	public:
		Tile(int x, int z)
			: x_(x), z_(z)
		{  }

		Tile()
			: x_(0), z_(0)
		{  }

		int GetX() const { return x_; }

		int GetZ() const { return z_; }

		void AddDirectionOffset(AStarDirection direction);

		void SetX(int x) { x_ = x; }

		void SetZ(int z) { z_ = z; }

		int GetKey () const
		{
			return x_ * 1000 + z_;
		}

		void Copy(AStarTileSharedPtr tile)
		{
			x_ = tile->GetX();
			z_ = tile->GetZ();
		}

		void Clear()
		{
			x_ = 0;
			z_ = 0;
		}

		static SmartObjectPool<Tile>& GetPool()
		{
			return tilePools_;
		}

		static AStarTileSharedPtr CreateTileFromDirection(AStarTileSharedPtr current, AStarDirection direction)
		{
			AStarTileSharedPtr tile = GetPool().acquire();
			tile->Copy(current);
			tile->AddDirectionOffset(direction);

			return tile;
		}

	private:
		int x_;
		int z_;

		static SmartObjectPool<Tile> tilePools_;
	};

	inline bool operator==(const Tile& lhs, const Tile& rhs)
	{
		return lhs.GetX() == rhs.GetX() && lhs.GetZ() == rhs.GetZ();
	}

	inline Tile operator-(Tile lhs, const Tile& rhs)
	{
		lhs.SetX(lhs.GetX() - rhs.GetX());
		lhs.SetZ(lhs.GetZ() - rhs.GetZ());

		return lhs;
	}

	inline bool operator!=(const Tile& lhs, const Tile& rhs)
	{
		return !(operator==(lhs, rhs));
	}

}