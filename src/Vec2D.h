#pragma once

#include "./mm2048.h"
#include "./Grid.h"
#include "./Tile.h"

class Vec2D
{
public:
	Vec2D();
	Vec2D(std::array<std::array<Tile,4>,4> const& table);
	Vec2D(Grid const& grid);
	Vec2D(std::array<std::array<int,4>,4> const& table);
	~Vec2D();

	std::array<std::array<int,4>,4> & getVec2D() ;

	std::array<int, 4> & operator[] (unsigned int index) ;
	std::array<int, 4> operator[] (unsigned int index) const;

	Vec2D& operator += (Vec2D const& other);

	friend bool operator == (Vec2D const& vecA, Vec2D const& vecB);
	friend Vec2D operator+(Vec2D vA, Vec2D const& vB);
	

private:
	//4*4 grid containing the numbers :
	std::array<std::array<int,4>,4> m_table;
	unsigned int m_size;
};

