#include "AStar.h"
#include "AStarSearch.h"

#include <cstdarg>

using namespace AStar;

AStarSearch search;
SearchPathMethod pathMethod;
SearchGuildPathMethod guildPathMethod;

std::function<int(int, int, int)> pathGetG;
std::function<int(int, int, int, int)> pathGetH;
std::function<bool(int, int, int, int)> pathCanMove;
std::function<int(int, int, int)> guildPathGetG;
std::function<int(int, int, int, int)> guildPathGetH;
std::function<bool(int, int, int, int)> guildPathCanMove;

static std::function<void(const char*)> debug;

static bool initialised = false;

//can be optimied use objectpool or memorypool
static std::vector<Tile> path;

void Initialise(
	PathGetGFuncPtr pathGetGCB,
	PathGetHFuncPtr pathGetHCB,
	PathCanMoveFuncPtr pathCanMoveCB,
	GuildPathGetGFuncPtr guildPathGetGCB,
	GuildPathGetHFuncPtr guildPathGetHCB,
	GuildPathCanMoveFuncPtr guildPathCanMoveCB
)
{
	if (initialised)
	{
		DEBUG_MSG("AStarLib::already initialise");
		return;
	}

	pathGetG = std::function<int(int, int, int)>(pathGetGCB);
	pathGetH = std::function<int(int, int, int, int)>(pathGetHCB);
	pathCanMove = std::function<bool(int, int, int, int)>(pathCanMoveCB);
	guildPathGetG = std::function<int(int, int, int)>(guildPathGetGCB);
	guildPathGetH = std::function<int(int, int, int, int)>(guildPathGetHCB);
	guildPathCanMove = std::function<bool(int, int, int, int)>(guildPathCanMoveCB);

	initialised = true;

	DEBUG_MSG("AStarLib::initialise success");
}

void GenerateSearchPath(int startX, int startZ, int endX, int endZ, int maxStep, int searchMethod, char** pathBuffer, int* pathCount)
{
	if (!initialised)
	{
		DEBUG_MSG("AStarLib::please call Initialise first");
		return;
	}

	path.clear();

	AStarSearchMethod method = static_cast<AStarSearchMethod>(searchMethod);

	switch (method)
	{
	case AStar::AStarSearchMethod::PathSearchMethod:
		search.SetMethod(&pathMethod);
		break;
	case AStar::AStarSearchMethod::GuildPathSearchMethod:
		search.SetMethod(&guildPathMethod);
		break;
	default:
		DEBUG_MSG("AStarLib::use undefined search method");
		return;
	}

	Tile startTile(startX, startZ);
	Tile endTile(endX, endZ);

	search.Search(startTile, endTile, path, maxStep);

	*pathBuffer = reinterpret_cast<char*>(path.data());
	*pathCount = path.size();
}

void DEBUG_MSG(const char* fmt, ...)
{
	static char buff[4096];

	va_list ap;
	
	va_start(ap, fmt);
	vsnprintf(buff, sizeof(buff), fmt, ap);
	va_end(ap);

	if (debug)
		debug(buff);
}

void SetDebugFunction(DebugLogFuncPtr func)
{
	debug = std::function<void(const char*)>(func);
}
