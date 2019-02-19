#include "AStar.h"
#include "AStarSearch.h"

#include <random>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace AStar;

const int map_max_x = 500;
const int map_max_z = 500;

int getg(int x, int z, int d)
{
	return IsDiagonal(static_cast<AStarDirection>(d)) ? 14 : 10;
}

int geth(int x, int z, int x1, int z1)
{
	int re = labs(x1 - x) + labs(z1 - z);
	return re * 10;
}

bool isExist(int x, int z)
{
	if (x >= 0 && x <= map_max_x && z >= 0 && z <= map_max_z)
		return true;

	return false;
}

bool canmove(int x, int z, int x1, int z1)
{
	/*
	if (x1 == 2 && z1 == 2)
		return false;

	if (x1 == 2 && z1 == 3)
		return false;

	if (x1 == 2 && z1 == 4)
		return false;

	if (x1 == 3 && z1 == 2)
		return false;

	if (x1 == 3 && z1 == 3)
		return false;

	if (x1 == 3 && z1 == 4)
		return false;
	*/

	return isExist(x1, z1);
}

int main(int argc, char** argv)
{
	std::mt19937 rng;
	std::uniform_int<int> intdist(0, map_max_x - 1);

	Initialise(&getg, &geth, &canmove, &isExist, &getg, &geth, &canmove, &isExist);
	
	int count = 0;
	long long alltime = 0;

	auto begin = std::chrono::system_clock::now();

	for(int i = 0; i != 10000; ++i)
	//while(true)
	{
		int startX = intdist(rng);
		int startZ = intdist(rng);
		int endX = intdist(rng);
		int endZ = intdist(rng);

		char* buffer = nullptr;
		int bufferCount = 0;

		GenerateSearchPath(startX, startZ, endX, endZ, 400, 0, &buffer, &bufferCount);
		//GenerateSearchPath(166, 46, 172, 51, 400, 0, &buffer, &bufferCount);

		auto end = std::chrono::system_clock::now();

		auto duration = end - begin;//
		begin = end;

		alltime += duration.count();
		count++;
	}

	std::cout << alltime / count<< std::endl;

	return 0;
}