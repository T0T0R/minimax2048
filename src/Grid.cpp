#include <iostream>
#include <array>
#include <vector>
#include <random>

#include "./mm2048.h"
#include "./Tile.h"
#include "./Grid.h"

Grid::Grid(std::default_random_engine const rd, int const& size):
	m_size(size), m_rd(rd)
{
	empty();
}

Grid::~Grid() {
}

// Build a grid of the specified size
std::array<std::array<Tile, 4>, 4> Grid::empty() {
	std::array<Tile, 4> emptyLine {Tile (0),Tile (0),Tile (0),Tile (0)};
	m_cells = {emptyLine,emptyLine,emptyLine,emptyLine};

	for (int i {0}; i<m_size; ++i){
		for (int j {0}; j<m_size; ++j){
			m_cells[i][j].updatePosition(Position {i,j});
		}
	}

	return m_cells;
}

// Find the first available random position
Position Grid::randomAvailableCell(){
	std::vector<Position> cells {availableCells()};

	if (!cells.empty()){
		return cells[m_rd() % cells.size()];
	}
	return Position {-1,-1};
}

std::vector<Position> Grid::availableCells() const {
	std::vector<Position> cells;

	for (int x = 0; x < m_size; x++) {
		for (int y = 0; y < m_size; y++) {

			if (m_cells[x][y].getValue()==0){
				cells.push_back(Position {x,y});
			}
		}
	}
	return cells;
}

// Check if there are any cells available
bool Grid::cellsAvailable() const{
	if (availableCells().size()==0){return false;}
	else {return true;}
}

// Check if the specified cell is taken
bool Grid::cellAvailable(Position const& pos) const{
	return !cellOccupied(pos);
}

bool Grid::cellOccupied(Position const& pos) const{
	return (!cellContent(pos).getValue()==0);
}

Tile Grid::cellContent(Position const& pos) const {
	if (withinBounds(pos)) {
		return m_cells[pos.x][pos.y];
	} else {
		return Tile(-1);
	}
}

bool Grid::withinBounds(Position const& position) const {
	return (position.x >= 0) && (position.x < m_size)
		&& (position.y >= 0) && (position.y < m_size);
}

// Save all tile positions and remove merger info
void Grid::prepareTiles() {
	for (auto& cellLine: m_cells) {
		for (auto& tile: cellLine) {
			tile.setMerged(false);
		}
	}
}

// Inserts a tile at its position
void Grid::insertTile(Tile& tile) {
	m_cells[tile.x()][tile.y()] = tile;
}

void Grid::removeTile(Tile& tile) {
	m_cells[tile.x()][tile.y()] = Tile (Position {tile.x(),tile.y()}, 0);
}

std::array<std::array<Tile, 4>, 4> Grid::getGrid() const {
	return m_cells;
}

void Grid::setGrid(int const& x, int const& y, Tile& tile) {
	m_cells[x][y] = tile;
	m_cells[x][y].updatePosition(Position {x,y});
}

void Grid::setGrid(std::array<std::array<Tile, 4>, 4> const& grid) {
	m_cells = grid;
}

void Grid::display() const {
	for (auto line: m_cells){
		for (auto cell: line){
			std::cout<< cell.getValue() << "\t";
		}
		std::cout<<std::endl;
	}
}
