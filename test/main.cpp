
#include "Systems/Collision.hpp"
#include "Systems/Movement.hpp"
#include "../src/GLoop.hpp"
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

int	main()
{
	 gloop::ISystem *movement = new Movement();
	 gloop::ISystem *collision = new Collision();


	 gloop::GLoop	gloop;

	 gloop.addSystem(movement);
	 gloop.addSystem(collision);

	 gloop.run();

/*	std::srand(std::time(nullptr)); // use current time as seed for random generator

	std::vector<testSystem> systemList;
	std::vector<testSystem> systemList2;
	systemList2.reserve(120000);

    auto start = std::chrono::system_clock::now();
	testSystem	test1;
	test1.classeSystem = "test1";

	for (int i = 0; i < 1000; ++i)
	{
		test1.weight = std::rand();
		systemList = insertSystem2(systemList, test1);
	}


    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "time passed with emplace => " << elapsed_seconds.count() << std::endl;

	start = std::chrono::system_clock::now();

	for (int i = 0; i < 1000; ++i)
	{
		test1.weight = std::rand();
		systemList = insertSystem(systemList, test1);
	}
	end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
	std::cout << "time passed with emplace => " << elapsed_seconds.count() << std::endl;
*/
	return 0;
}