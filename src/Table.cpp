#include <iostream>
#include <array>
#include <random>

#include "./mm2048.h"
#include "./Table.h"

Table::Table(std::default_random_engine& rd, unsigned int const& startTiles): m_nbInit{0} {
	init(rd, startTiles);
	std::cout<< "2048 Table initialized !" << std::endl;
	Position position;
}

Table::~Table() {
}


std::array<std::array<unsigned int, 4>, 4> Table::init(std::default_random_engine& rd, unsigned int const& startTiles) {
	/* Initializes the table by filling it with zeros, and then
		adding two numbers at random places.
	*/

	std::array<unsigned int, 4> emptyLine {{0,0,0,0}};
	m_table = {emptyLine,emptyLine,emptyLine,emptyLine};

	for (unsigned int i{0}; i<startTiles; ++i){
		m_table[randNb(rd,4)][randNb(rd, 4)] = (1+randNb(rd, 2))*2;
	}


	++ m_nbInit;	//One more initialisation
	return m_table;
}


std::array<std::array<unsigned int, 4>, 4> Table::getTable() const {
	/* Returns the table with values in it.
	*/
	return m_table;
}


unsigned long long int Table::getNb() const {
	/* Returns the number of initialisations since the creation
		of that table.
	*/
	return m_nbInit;
}


bool Table::move(int const& dir) {
	return false;
}


void Table::display() const {
	/* Displays the table in the console.
	*/

	std::cout<< std::endl;

	for (auto& line: m_table){
		for (auto& cell: line){
			std::cout<< cell <<"\t";
		}
		std::cout<< std::endl;
	}
}


unsigned int Table::randNb(std::default_random_engine& rd, unsigned int max) {
	/* Gives a random number between 0 and max (excluded)
	*/
	return rd()% max;
}
