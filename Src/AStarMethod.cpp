#include "AStarMethod.h"
#include "AStar.h"

#include <cmath>

namespace AStar
{
	int SearchPathMethod::GetG(Tile& point, AStarDirection direction)
	{
		return pathGetG(point.GetX(), point.GetZ(), static_cast<int>(direction));
	}

	int SearchPathMethod::GetH(Tile& point, Tile& target)
	{
		return pathGetH(point.GetX(), point.GetZ(), target.GetX(), target.GetZ());
	}

	int SearchPathMethod::GetGOnTurn()
	{
		return 50;
	}

	bool SearchPathMethod::CanMove(Tile& point, Tile& next)
	{
		return pathCanMove(point.GetX(), point.GetZ(), next.GetX(), next.GetZ());
	}

	int SearchGuildPathMethod::GetG(Tile& point, AStarDirection direction)
	{
		return guildPathGetG(point.GetX(), point.GetZ(), static_cast<int>(direction));
	}

	int SearchGuildPathMethod::GetH(Tile& point, Tile& target)
	{
		return guildPathGetH(point.GetX(), point.GetZ(), target.GetX(), target.GetZ());
	}

	int SearchGuildPathMethod::GetGOnTurn()
	{
		return 0;
	}
	
	bool SearchGuildPathMethod::CanMove(Tile& point, Tile& next)
	{
		return guildPathCanMove(point.GetX(), point.GetZ(), next.GetX(), next.GetZ());
	}
}