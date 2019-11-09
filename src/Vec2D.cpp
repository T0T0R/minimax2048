#include <iostream>
#include <array>
#include <random>

#include "./mm2048.h"
#include "./Tile.h"
#include "./Vec2D.h"

Vec2D::Vec2D()
{
	std::array<int, 4> emptyLine {};
	m_table.fill(emptyLine);
}

Vec2D::Vec2D(std::array<std::array<Tile,4>,4> const& table)
{
	std::array<int, 4> emptyLine {};
	m_table.fill(emptyLine);

	for (unsigned int i {0}; i<table.size(); ++i) {
		for (unsigned int j {0}; j<table.size(); ++j) {
			m_table[i][j] = table[i][j].getValue();
		}
	}

}

Vec2D::Vec2D(Grid const& grid)
{
	m_table = Vec2D(grid.getGrid()).getVec2D();
}

Vec2D::Vec2D(std::array<std::array<int,4>,4> const& table):
	m_table(table)
{}

Vec2D::~Vec2D() {
}

std::array<std::array<int,4>,4> & Vec2D::getVec2D() {
	return m_table;
}

std::array<int, 4> & Vec2D::operator[](unsigned int index) {
	return m_table.at(index);
}

std::array<int, 4> Vec2D::operator[](unsigned int index) const {
	return m_table.at(index);
}

bool operator==(Vec2D const & vecA, Vec2D const & vecB) {
	return vecA.m_table == vecB.m_table;
}
