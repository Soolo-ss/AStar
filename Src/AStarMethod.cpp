#include "AStarMethod.h"
#include "AStar.h"

#include <cmath>

namespace AStar
{
	int SearchPathMethod::GetG(AStarTileSharedPtr point, AStarDirection direction)
	{
		return pathGetG(point->GetX(), point->GetZ(), static_cast<int>(direction));
	}

	int SearchPathMethod::GetH(AStarTileSharedPtr point, AStarTileSharedPtr target)
	{
		return pathGetH(point->GetX(), point->GetZ(), target->GetX(), target->GetZ());
	}

	int SearchPathMethod::GetGOnTurn()
	{
		return 50;
	}

	bool SearchPathMethod::CanMove(AStarTileSharedPtr point)
	{
		return pathCanMove(0, 0, point->GetX(), point->GetZ());
	}

	bool SearchPathMethod::CanMove(AStarTileSharedPtr point, AStarDirection direction)
	{
		Tile tile(*point);
		tile.AddDirectionOffset(direction);

		return pathCanMove(0, 0, tile.GetX(), tile.GetZ());
	}

	bool SearchPathMethod::isExist(AStarTileSharedPtr point)
	{
		return pathIsExits(point->GetX(), point->GetZ());
	}

	bool SearchPathMethod::isExist(AStarTileSharedPtr point, AStarDirection direction)
	{
		Tile tile(*point);
		tile.AddDirectionOffset(direction);

		return pathIsExits(tile.GetX(), tile.GetZ());
	}

	int SearchGuildPathMethod::GetG(AStarTileSharedPtr point, AStarDirection direction)
	{
		return guildPathGetG(point->GetX(), point->GetZ(), static_cast<int>(direction));
	}

	int SearchGuildPathMethod::GetH(AStarTileSharedPtr point, AStarTileSharedPtr target)
	{
		return guildPathGetH(point->GetX(), point->GetZ(), target->GetX(), target->GetZ());
	}

	int SearchGuildPathMethod::GetGOnTurn()
	{
		return 0;
	}
	
	bool SearchGuildPathMethod::CanMove(AStarTileSharedPtr point)
	{
		return guildPathCanMove(0, 0, point->GetX(), point->GetZ());
	}

	bool SearchGuildPathMethod::CanMove(AStarTileSharedPtr point, AStarDirection direction)
	{
		Tile tile(*point);
		tile.AddDirectionOffset(direction);

		return guildPathCanMove(0, 0, tile.GetX(), tile.GetZ());
	}

	bool SearchGuildPathMethod::isExist(AStarTileSharedPtr point)
	{
		return guildPathIsExits(point->GetX(), point->GetZ());
	}

	bool SearchGuildPathMethod::isExist(AStarTileSharedPtr point, AStarDirection direction)
	{
		Tile tile(*point);
		tile.AddDirectionOffset(direction);

		return guildPathIsExits(tile.GetX(), tile.GetZ());
	}
}