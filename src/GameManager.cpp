#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <random>
#include <algorithm>

#include "./mm2048.h"
#include "./Tile.h"
#include "./Grid.h"
#include "./GameManager.h"

GameManager::GameManager(std::default_random_engine rd, int const& size):
	m_size(size), m_startTiles(2), m_grid (rd, m_size), m_score(0),
	m_over(false), m_won(false), m_isStuck(false), m_keepPlaying(false),
	m_rd(rd)
{
	setup(rd);
}

GameManager::~GameManager() {
}

void GameManager::setup(std::default_random_engine rd) {
	m_grid = Grid (rd, m_size);
	m_score = 0;
	m_over = false;
	m_won = false;
	m_isStuck = false;
	m_keepPlaying = false;

	// Add the initial tiles
	addStartTiles();
}

// Set up the initial tiles to start the game with
void GameManager::addStartTiles() {
	for (int i = 0; i < m_startTiles; i++) {
		addRandomTile();
	}
}

void GameManager::addRandomTile() {
	if (m_grid.cellsAvailable()) {
		int value {-1};
		if (m_rd()%10 < 8) { value = 2;} else {value = 4;}

		Tile tile (m_grid.randomAvailableCell(), value);

		m_grid.insertTile(tile);
	}
}

// Move a tile and its representation
void GameManager::moveTile(Tile& tile, Position const& pos) {
	Tile empty (0);

	m_grid.setGrid(tile.x(), tile.y(), empty);
	m_grid.setGrid(pos.x, pos.y, tile);
}

// Move tiles on the grid in the specified direction
void GameManager::move(int const& direction) {

	if (isGameTerminated()) return; // Don't do anything if the game's over

	Position cell;
	Tile tile;
	std::array<Position, 2> positions;

	Position vector = getVector(direction);
	Traversal traversals = buildTraversals(vector);
	bool moved = false;

	// Save the current tile positions and remove merger information
	m_grid.prepareTiles();

	// Traverse the grid in the right direction and move tiles	
	for (int x: traversals.x){
		for (int y : traversals.y) {
			cell = Position {x,y};
			tile = m_grid.cellContent(cell);

			if (tile.getValue()>0) {	// If there is a tile here at (x,y)
				positions = findFarthestPosition(cell, vector);
				Tile next = m_grid.cellContent(positions[1]);

				// Only one merger per row traversal?
				if (next.getValue()>0 &&
						next.getValue() == tile.getValue() &&
						!next.didMerged() ) {
					Tile merged {positions[1], tile.getValue() * 2};

					merged.setMerged(true);


					m_grid.insertTile(merged);
					m_grid.removeTile(tile);

					// Converge the two tiles' positions
					tile.updatePosition(positions[1]);

					// Update the score
					m_score += merged.getValue();

					// The mighty 2048 tile
					if (merged.getValue() == 2048) {m_won = true;}

					moved = true; // The tile moved from its original cell !

				} else {
					if (!positionsEqual(positions[0], tile)){ moved = true; }
					moveTile(tile, positions[0]);
				}
			}
		}
	}

	if (moved) {
		addRandomTile();

		if (!movesAvailable()) {
			m_over = true; // Game over!
		}

	}else{
		std::cout<<"*stuck*"<<std::endl;
	}



}

bool GameManager::isGameTerminated() const {
	return m_over || (m_won && !m_keepPlaying);
}

Position GameManager::getVector(int const& direction) const {
	const std::map<int, Position> map {
		{0 , Position {-1, 0}}, // Up
		{1 , Position {0, 1}},  // Right
		{2, Position {1, 0}},  // Down
		{3 , Position {0, -1}}   // Left
	};

	switch (direction){
		case 0:
			std::cout<< "Up"<<std::endl;
			break;
		case 1:
			std::cout<< "Right"<<std::endl;
			break;
		case 2:
			std::cout<< "Down"<<std::endl;
			break;
		case 3:
			std::cout<< "Left"<<std::endl;
			break;
		default:
			break;
	}

	return map.at(direction);
}

// Build a list of positions to traverse in the right order
Traversal GameManager::buildTraversals(Position const& vector) const {
	Traversal traversals;

	for (int pos = 0; pos < m_size; pos++) {
		traversals.x.push_back(pos);
		traversals.y.push_back(pos);
	}

	// Always traverse from the farthest cell in the chosen direction
	if (vector.x == 1){ std::reverse(traversals.x.begin(), traversals.x.end()); }
	if (vector.y == 1){ std::reverse(traversals.y.begin(), traversals.y.end()); }

	return traversals;
}

std::array<Position,2> GameManager::findFarthestPosition(Position cell, Position const& vector) const {
	Position previous;

	// Progress towards the vector direction until an obstacle is found
	do {
		previous = cell;
		cell = Position {previous.x + vector.x, previous.y + vector.y};
	} while (m_grid.withinBounds(cell) &&
			 m_grid.cellAvailable(cell));

	return std::array<Position, 2> {
	  previous,
	  cell // Used to check if a merge is required
	};
}

bool GameManager::positionsEqual(Position const& first, Tile const& second) const {
	return first.x == second.x() && first.y == second.y();
}

bool GameManager::movesAvailable() const {
	return m_grid.cellsAvailable() || tileMatchesAvailable();
}

// Check for available matches between tiles (more expensive check)
bool GameManager::tileMatchesAvailable() const {
	Tile tile;

	for (int x = 0; x < m_size; x++) {
		for (int y = 0; y < m_size; y++) {
			tile = m_grid.cellContent(Position{x,y});

			if (tile.getValue()!=0) {
				for (int direction = 0; direction < 4; direction++) {
					Position vector = getVector(direction);
					Position cell = {x + vector.x, y + vector.y};

					Tile other = m_grid.cellContent(cell);

					if (other.getValue()!=0 && other.getValue() == tile.getValue()) {
						return true; // These two tiles can be merged
					}
				}
			}
		}
	}

	return false;
}

bool GameManager::isStuck() const {
	return m_isStuck;
}

bool GameManager::isOver() const {
	return m_over;
}

bool GameManager::getWon() const {
	return m_won;
}

void GameManager::display() const {
	m_grid.display();
}
