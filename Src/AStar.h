#include "platform.h"

#include <functional>

using DebugLogFuncPtr = void(*)(const char*);
using PathGetGFuncPtr = int(*)(int, int, int);
using PathGetHFuncPtr = int(*)(int, int, int, int);
using PathCanMoveFuncPtr = bool(*)(int, int, int, int);
using GuildPathGetGFuncPtr = int(*)(int, int, int);
using GuildPathGetHFuncPtr = int(*)(int, int, int, int);
using GuildPathCanMoveFuncPtr = bool(*)(int, int, int, int);

EXPORT void Initialise(
	PathGetGFuncPtr pathGetGCB,
	PathGetHFuncPtr pathGetHCB,
	PathCanMoveFuncPtr pathCanMoveCB,
	GuildPathGetGFuncPtr guildPathGetGCB,
	GuildPathGetHFuncPtr guildPathGetHCB,
	GuildPathCanMoveFuncPtr guildCanMoveCB
);

EXPORT void GenerateSearchPath(int startX, int startZ, int endX, int endZ, int maxStep, int searchMethod, char** pathBuffer, int* pathCount);

EXPORT void SetDebugFunction(DebugLogFuncPtr func);

extern void DEBUG_MSG(const char* fmt, ...);

extern bool initialised;

extern std::function<int(int, int, int)> pathGetG;
extern std::function<int(int, int, int, int)> pathGetH;
extern std::function<bool(int, int, int, int)> pathCanMove;
extern std::function<int(int, int, int)> guildPathGetG;
extern std::function<int(int, int, int, int)> guildPathGetH;
extern std::function<bool(int, int, int, int)> guildPathCanMove;
