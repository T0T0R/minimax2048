#include <iostream>
#include <array>
#include <random>

#include "./mm2048.h"
#include "./Tile.h"
#include "./Vec2D.h"

Vec2D::Vec2D():
	m_size {4}
{
	std::array<int, 4> emptyLine {};
	m_table.fill(emptyLine);
}

Vec2D::Vec2D(std::array<std::array<Tile,4>,4> const& table):
	m_size {4}
{
	std::array<int, 4> emptyLine {};
	m_table.fill(emptyLine);

	for (unsigned int i {0}; i<table.size(); ++i) {
		for (unsigned int j {0}; j<table.size(); ++j) {
			m_table[i][j] = table[i][j].getValue();
		}
	}

}

Vec2D::Vec2D(Grid const& grid):
	m_size {4}
{
	m_table = Vec2D(grid.getGrid()).getVec2D();
}

Vec2D::Vec2D(std::array<std::array<int,4>,4> const& table):
	m_table(table), m_size {4}
{}

Vec2D::~Vec2D() {
}

Vec2D Vec2D::eye() {
	std::array<int,4> line1 {1,0,0,0};
	std::array<int, 4> line2 {0,1,0,0};
	std::array<int, 4> line3 {0,0,1,0};
	std::array<int, 4> line4 {0,0,0,1};
	return Vec2D(std::array<std::array<int,4>,4> {line1, line2, line3, line4});
}

std::array<std::array<int,4>,4> & Vec2D::getVec2D() {
	return m_table;
}

void Vec2D::display() const {
	for (auto line: m_table) {
		for (auto cell: line) {
			std::cout<< cell << "\t";
		}
		std::cout<<std::endl;
	}
}

std::array<int, 4> & Vec2D::operator[](unsigned int index) {
	return m_table.at(index);
}

std::array<int, 4> Vec2D::operator[](unsigned int index) const {
	return m_table.at(index);
}

Vec2D& Vec2D::operator+=(Vec2D const& other) {
	for (unsigned int i {0}; i<m_size; ++i) {
		for (unsigned int j {0}; j<m_size; ++j) {
			m_table[i][j] += other[i][j];
		}
	}

	return *this;
}

bool operator==(Vec2D const & vecA, Vec2D const & vecB) {
	return vecA.m_table == vecB.m_table;
}
bool operator!=(Vec2D const& vecA, Vec2D const& vecB) {
	return !(vecA == vecB);
}

Vec2D operator+(Vec2D vA, Vec2D const& vB){
	vA += vB; // reuse compound assignment.
	return vA; // return the result by value (uses move constructor).
}