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
#include "./minimax.h"




std::string bestMove(std::vector<std::pair<Vec2D, std::string>> const& futureGrids, std::vector<int> const& marks) {
	std::string answer = "o";
	int bestMark {0};
	for (unsigned int i {0}; i<futureGrids.size(); i++) {
		if (marks[i]>bestMark) {	//If there is a better mark, add the corresponding movement.
			bestMark = marks[i];
			answer = futureGrids[i].second;
		}
	}

	return answer;
}


int movementConv(std::string direction) {
	// Converts a movement expressed with a string in a movement expressed by an integer number.
	const std::map<std::string, int> conv {
		{"h", 0 }, // Up
		{"d", 1 },  // Right
		{"b", 2},  // Down
		{"g",3},   // Left
		{"o", 4}
	};
	int inter = conv.at(direction);
	return inter;
}









int main()
{	
	unsigned int const seed = static_cast<unsigned int>(std::time(nullptr));
	std::default_random_engine rd {seed};	//Pseudo-random number generator.
	
	std::vector<std::pair<Vec2D, std::string>> futureGrids;
	std::vector<int> marks;	//Contains marks corresponding to grids in futureGrids
	Vec2D actualGrid;

	int size {4};
	int const DEPTH {5};

	int input;

	std::array<int,4> line {1,0,0,4};
	std::array<std::array<int, 4>, 4> table;
	table.fill(line);

	Vec2D myVec (table);
	Vec2D id = Vec2D::eye();

	myVec.display();
	//(id/myVec).display();
	glisse(myVec,"g").display();


	GameManager Game {rd, size};
	/*while (!Game.isOver()){
		Game.display();
		std::cin>>input;
		Game.move(input);
	}*/

	while (!Game.isOver()) {
		std::cout<<"==============="<<std::endl;
		Game.display();
		std::cout<<std::endl;
		actualGrid = Game.getGrid();

		futureGrids = fournir_coups(actualGrid, true);

		for (std::pair<Vec2D, std::string> grid: futureGrids){
			marks.push_back(minimax(grid.first, DEPTH, true));
			grid.first.display();
			std::cout<<grid.second<<std::endl;
		}

		Game.move(movementConv(bestMove(futureGrids, marks)));

	}


	return EXIT_SUCCESS;
}

