#pragma once

#include <functional>
#include <memory>

#include "Common.h"
#include "Tail.h"

namespace AStar
{
	class AStarMethod
	{
	public:
		virtual ~AStarMethod() { }
		
		virtual int GetG(Tile& point, AStarDirection direction) = 0;
		virtual int GetH(Tile& point, Tile& target) = 0;
		virtual int GetGOnTurn() = 0;
		virtual bool CanMove(Tile& point, Tile& next) = 0;
	};

	class SearchPathMethod : public AStarMethod
	{
	public:
		int GetG(Tile& point, AStarDirection direction) final;

		int GetH(Tile& point, Tile& target) final;

		int GetGOnTurn() final;

		bool CanMove(Tile& point, Tile& next) final;
	};

	class SearchGuildPathMethod : public AStarMethod
	{
	public:
		int GetG(Tile& point, AStarDirection direction) final;

		int GetH(Tile& point, Tile& target) final;

		int GetGOnTurn() final;

		bool CanMove(Tile& point, Tile& next) final;
	};
}
