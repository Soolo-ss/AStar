#pragma once

#include "Common.h"

namespace AStar
{
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

		AStarDirection GetFromDriection(Tile parent);

		void SetX(int x) { x_ = x; }

		void SetZ(int z) { z_ = z; }

		int GetKey () const
		{
			return x_ * 1000 + z_;
		}

	private:
		int x_;
		int z_;
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