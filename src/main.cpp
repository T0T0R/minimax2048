#include <iostream>
#include <cstdlib>
#include <array>
#include <map>
#include <random>
#include <ctime>
#include <fstream>
#include <string>

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
		{"o", -1}
	};
	int inter = conv.at(direction);
	return inter;
}



int giveNbZeros(Vec2D const& table){
	int nbZeros {0};
	for (int i {0}; i<4; i++) {
		for (int j {0}; j<4; j++) {

			if (table[i][j]==0) {
				nbZeros++;
			}

		}
	}
	return nbZeros;
}


int giveMax(Vec2D const& table) {
	int max {0};
	for (int i {0}; i<4; i++) {
		for (int j {0}; j<4; j++) {

			if (table[i][j] > max) {
				max = table[i][j];
			}

		}
	}
	return max;
}


bool isMaxInCorner(Vec2D const& table){
	int max = giveMax(table);

	if (table[0][0]==max || table[3][0]==max || table[0][3]==max || table[3][3]==max) {  //  - Bonus : if the highest tile is in the corner,
		return true;
	}else{
		return false;
	}
}


int giveSum(Vec2D const& table){
	int sum {0};
	for (int i {0}; i<4; i++) {
		for (int j {0}; j<4; j++) {
			sum += table[i][j];
		}
	}
	return sum;
}



int main()
{	
	unsigned int const seed = static_cast<unsigned int>(std::time(nullptr));
	std::default_random_engine rd {seed};	//Pseudo-random number generator.
	
	std::vector<std::pair<Vec2D, std::string>> futureGrids;
	std::vector<int> marks;	//Contains marks corresponding to grids in futureGrids
	Vec2D actualGrid;

	int size {4};
	int const DEPTH {0};

	std::array<int, 4> lineA {2,0,0,0};
	std::array<int, 4> lineB {0,0,0,0};
	std::array<int, 4> lineC {0,0,0,0};
	std::array<int, 4> lineD {2,0,0,0};
	std::array<std::array<int, 4>, 4> table {lineA, lineB, lineC, lineD};


	Vec2D myVec (table);
	Vec2D id = Vec2D::eye();

	//std::cout<<(float)giveSum(table)/(float)(16-giveNbZeros(table))<<std::endl;


	GameManager Game {rd, size};
	

	std::ofstream fileNbZeros("nbZeros.csv");
	std::ofstream fileMaxValue("maxValue.csv");
	std::ofstream fileMean("mean.csv");
	std::ofstream fileCMean("correctedMean.csv");
	std::ofstream filePercCorner("percCorner.csv");



	for (int LAPS{0}; LAPS<1000; LAPS++){
		Game.setup(rd);

		std::cout<<"Lap: "<<LAPS<<std::endl;
		int lapNo {0};
		int nbMaxInCorner {0};


		while (!Game.isOver()) {
			//std::cout<<"==============="<<std::endl;
			marks.clear();
			//Game.display();
			
			actualGrid = Game.getGrid();

			fileNbZeros<<giveNbZeros(actualGrid)<<",";
			fileMaxValue<<giveMax(actualGrid)<<",";
			fileMean<<(float)giveSum(actualGrid)/(float)16<<",";
			fileCMean<<(float)giveSum(actualGrid)/(float)(16-giveNbZeros(actualGrid))<<",";
			if(isMaxInCorner(actualGrid)) nbMaxInCorner ++;

			futureGrids = fournir_coups(actualGrid, true);
						 
			for (std::pair<Vec2D, std::string> grid: futureGrids){
				marks.push_back(minimax(grid.first, DEPTH, true));
				/*grid.first.display();
				std::cout<<grid.second<<"\t"<<fournir_note(grid.first)<<std::endl;
				std::cout<<std::endl;*/
			}
			//std::cout<<std::endl;
			//std::cout<<bestMove(futureGrids, marks)<<std::endl;
			Game.move(movementConv(bestMove(futureGrids, marks)));

			lapNo++;

		}
		fileNbZeros<<std::endl;
		fileMaxValue<<std::endl;
		fileMean<<std::endl;
		fileCMean<<std::endl;

		filePercCorner<<(float)nbMaxInCorner/(float)lapNo<<",";
		
	}

	Game.display();

	return EXIT_SUCCESS;
}

