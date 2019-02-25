
// #include "Systems/Collision.hpp"
// #include "Systems/Movement.hpp"
// #include "../src/GLoop.hpp"
/*
#include <string>
#include <iostream>
#include <list>
#include <algorithm>
#include <functional>
#include <queue>
#include <vector>
#include <ctime>
#include <chrono>


struct testSystem
{
	int weight;
	std::string classeSystem;
};
std::vector<testSystem>	insertSystem2(std::vector<testSystem> systemList, testSystem toAdd)
{
	systemList.push_back(toAdd);
	auto start = systemList.begin();
	auto end = systemList.end();

	std::sort(start, end, [](const testSystem &left, const testSystem &right) {return left.weight < right.weight; } );
	return systemList;
}

std::vector<testSystem>	insertSystem(std::vector<testSystem> systemList, testSystem toAdd)
{
	auto it = systemList.begin();

	while (it != systemList.end()) {
		if (it->weight >= toAdd.weight) {
			systemList.emplace(it, toAdd);
			break;
		}
		it += 1;
	}
	if (it == systemList.end()) {
		systemList.emplace_back(toAdd);
	}
	return systemList;
}

void	displaySystem(std::vector<testSystem> v) {
	for (unsigned int i = 0; i < v.size(); ++i)
	{
		std::cout << v[i].weight << std::endl;
	}
}
*/
#include "GLoop.hpp"
int	main()
{
	gloop::GLoop	l;
	return 0;
}