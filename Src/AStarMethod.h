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
		
		virtual int GetG(AStarTileSharedPtr point, AStarDirection direction) = 0;
		virtual int GetH(AStarTileSharedPtr point, AStarTileSharedPtr target) = 0;
		virtual int GetGOnTurn() = 0;
		virtual bool CanMove(AStarTileSharedPtr point) = 0;
		virtual bool CanMove(AStarTileSharedPtr point, AStarDirection direction) = 0;
		virtual bool isExist(AStarTileSharedPtr point) = 0;
		virtual bool isExist(AStarTileSharedPtr point, AStarDirection direction) = 0;
	};

	class SearchPathMethod : public AStarMethod
	{
	public:
		int GetG(AStarTileSharedPtr point, AStarDirection direction) final;

		int GetH(AStarTileSharedPtr point, AStarTileSharedPtr target) final;

		int GetGOnTurn() final;

		bool CanMove(AStarTileSharedPtr point) final;

		bool CanMove(AStarTileSharedPtr point, AStarDirection direction) final;

		bool isExist(AStarTileSharedPtr point) final;

		bool isExist(AStarTileSharedPtr point, AStarDirection direction) final;
	};

	class SearchGuildPathMethod : public AStarMethod
	{
	public:
		int GetG(AStarTileSharedPtr point, AStarDirection direction) final;

		int GetH(AStarTileSharedPtr point, AStarTileSharedPtr target) final;

		int GetGOnTurn() final;

		bool CanMove(AStarTileSharedPtr point) final;

		bool CanMove(AStarTileSharedPtr point, AStarDirection direction) final;

		bool isExist(AStarTileSharedPtr point) final;

		bool isExist(AStarTileSharedPtr point, AStarDirection direction) final;
	};
}
