#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <random>
#include <algorithm>

#include "./mm2048.h"
#include "./Tile.h"
#include "./Grid.h"




struct Traversal {
	std::vector<int> x;
	std::vector<int> y;
};


class GameManager
{
public:
	GameManager(std::default_random_engine rd, int size);
	~GameManager();

	void setup(std::default_random_engine rd);

	void move(int direction);

	bool isStuck() const;
	bool isOver() const;
	bool getWon() const;

	void display() const;


protected:
	void addStartTiles();
	void addRandomTile();

	bool isGameTerminated() const;

	bool movesAvailable() const;
	bool tileMatchesAvailable() const;

	void moveTile(Tile& tile, Position const& pos);

	Position getVector(int direction) const;
	Traversal buildTraversals(Position const& vector) const;
	std::array<Position, 2> findFarthestPosition(Position cell, Position const& vector) const;
	bool positionsEqual(Position const& first, Tile const& second) const;


private:
	int m_size;
	int m_startTiles;
	Grid m_grid;
	int m_score;
	bool m_over, m_won, m_isStuck;
	bool m_keepPlaying;
	std::default_random_engine m_rd;
};

