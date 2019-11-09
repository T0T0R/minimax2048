#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <random>

#include "./mm2048.h"
#include "./Tile.h"
#include "./Grid.h"



class Grid
{
public:
	Grid(std::default_random_engine const rd, int size);
	~Grid();

	Position randomAvailableCell();
	bool cellsAvailable() const;
	bool cellAvailable(Position const& pos) const;
	Tile cellContent(Position const& pos) const;

	bool withinBounds(Position const& pos) const;

	void prepareTiles();
	void insertTile (Tile& tile);
	void removeTile (Tile& tile);

	std::array<std::array<Tile, 4>, 4> getGrid() const;
	void setGrid(int x, int y, Tile& tile);
	void setGrid(std::array<std::array<Tile, 4>, 4> const& grid);

	void display() const;


protected:
	std::array<std::array<Tile, 4>, 4> empty();
	std::vector<Position> availableCells() const;
	bool cellOccupied(Position const& pos) const;


private:
	std::default_random_engine m_rd;
	int m_size;
	std::array<std::array<Tile,4>,4> m_cells;
};

