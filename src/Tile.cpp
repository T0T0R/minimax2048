#include <iostream>
#include <array>

#include "./mm2048.h"
#include "./Tile.h"

Tile::Tile():
	m_x(-1), m_y(-1), m_value(-1), m_justMerged(false)
{}

Tile::Tile(int value) :
	m_x(-1), m_y(-1), m_value(value), m_justMerged(false) 
{}

Tile::Tile(Position const& position, int value):
	m_x(position.x), m_y(position.y), m_value(value), m_justMerged(false)
{}

Tile::~Tile() {
}

int Tile::x() const {
	return m_x;
}

int Tile::y() const {
	return m_y;
}

int Tile::getValue() const {
	return m_value;
}


void Tile::updatePosition(Position const& position) {
	m_x = position.x;
	m_y = position.y;
}

void Tile::setMerged(bool merged) {
	m_justMerged = merged;
}

void Tile::setValue(int value) {
	m_value = value;
}

bool Tile::didMerged() const {
	return m_justMerged;
}

bool operator == (Tile const& tA, Tile const& tB){
	return tA.m_value==tB.m_value;
}

bool operator == (Tile const& tA, int const tB) {
	return tA.m_value==tB;
}

bool operator == (int const tA, Tile const& tB) {
	return tA==tB.m_value;
}