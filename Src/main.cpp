#include "AStar.h"
#include "AStarSearch.h"

#include <random>
#include <chrono>
#include <iostream>

using namespace AStar;

int getg(int x, int z, int d)
{
	return IsDiagonal(static_cast<AStarDirection>(d)) ? 14 : 10;
}

int geth(int x, int z, int x1, int z1)
{
	int re = labs(x1 - x) + labs(z1 - z);
	return re * 10;
}

bool canmove(int x, int z, int x1, int z1)
{
	return true;
}

int main(int argc, char** argv)
{
	Initialise(&getg, &geth, &canmove, &getg, &geth, &canmove);

	std::mt19937 rng;
	std::uniform_int<int> intdist(0, 600);

	uint64_t count = 0;
	uint64_t alltime = 0;

	auto begin = std::chrono::system_clock::now();

	//for(int i = 0; i != 10000; ++i)
	while(true)
	{
		int startX = intdist(rng);
		int startZ = intdist(rng);
		int endX = intdist(rng);
		int endZ = intdist(rng);

		char* buffer = nullptr;
		int bufferCount = 0;

		GenerateSearchPath(startX, startZ, endX, endZ, 400, 0, &buffer, &bufferCount);
		//GenerateSearchPath(0, 0, 10, 0, 400, 0, &buffer, &bufferCount);
	}

	auto end = std::chrono::system_clock::now();

	auto duration = end - begin;//

	std::cout << duration.count() << std::endl;

	return 0;
}