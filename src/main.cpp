#include <iostream>
#include <array>
#include <map>
#include <random>
#include <ctime>

#include "./mm2048.h"
#include "../resources/provided.h"
#include "./Tile.h"
#include "./Grid.h"
#include "./Vec2D.h"
#include "./GameManager.h"


int main()
{	
	unsigned int const seed = static_cast<unsigned int>(std::time(nullptr));
	std::default_random_engine rd {seed};	//Pseudo-random number generator.

	int size {4};

	int input;

	std::array<int,4> line {1,2,3,4};
	std::array<std::array<int, 4>, 4> table;
	table.fill(line);

	Vec2D myVec (table);
	Vec2D id = Vec2D::eye();

	myVec.display();
	(id/myVec).display();
	myVec.display();


	GameManager Game {rd, size};
	while (!Game.isOver()){
		Game.display();
		std::cin>>input;
		Game.move(input);
	}

	return EXIT_SUCCESS;
}
