#include <iostream>
#include <array>
#include <map>
#include <random>
#include <ctime>

#include "./mm2048.h"
#include "./Tile.h"
#include "./Grid.h"
#include "./Vec2D.h"
#include "./GameManager.h"


void testMemory(){
	std::array<unsigned short int, 4> answer {1,0,0,0};

	std::map<std::array<std::array<unsigned char, 4>, 4>, std::array<unsigned short int, 4>> table;

	for (unsigned char a {0}; a<11; ++a){
		for (unsigned char b {0}; b<11; ++b) {
			for (unsigned char c {0}; c<11; ++c) {
				for (unsigned char d {0}; d<11; ++d) {
					for (unsigned char e {0}; e<11; ++e) {
						std::cout<<"hello";
						for (unsigned char f {0}; f<11; ++f) {
							for (unsigned char g {0}; g<11; ++g) {
								for (unsigned char h {0}; h<11; ++h) {
									for (unsigned char i {0}; i<11; ++i) {
										for (unsigned char j {0}; j<11; ++j) {
											for (unsigned char k {0}; k<11; ++k) {
												for (unsigned char l {0}; l<11; ++l) {
													for (unsigned char m {0}; m<11; ++m) {
														for (unsigned char n {0}; n<11; ++n) {
															for (unsigned char o {0}; o<11; ++o) {
																for (unsigned char p {0}; p<11; ++p) {



		std::array<unsigned char, 4> line0 {a,b,c,d};
		std::array<unsigned char, 4> line1 {e,f,g,h};
		std::array<unsigned char, 4> line2 {i,j,k,l};
		std::array<unsigned char, 4> line3 {m,n,o,p};

		std::array<std::array<unsigned char, 4>, 4> m_cells = {line0,line1,line2, line3};
		table.insert({m_cells, answer});

																}}}}}}}}}}}}}}}
		
	}
}


int main()
{	
	unsigned int const seed = static_cast<unsigned int>(std::time(nullptr));
	std::default_random_engine rd {seed};	//Pseudo-random number generator

	int size {4};

	int input;

	auto cases {3^9};




	GameManager Game {rd, size};
	while (!Game.isOver()){
		Game.display();
		std::cin>>input;
		Game.move(input);
	}

	return EXIT_SUCCESS;
}
