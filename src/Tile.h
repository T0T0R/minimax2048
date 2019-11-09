#pragma once
#include <iostream>
#include <array>

#include "./mm2048.h"


class Tile
{
public:
	Tile();
	Tile(int value);
	Tile(Position const& position, int value);
	~Tile();

	int x() const;
	int y() const;
	int getValue() const;
	bool didMerged() const;

	void updatePosition(Position const& position);

	void setMerged(bool merged);
	void setValue(int value);

	friend bool operator == (Tile const& tA, Tile const& tB);
	friend bool operator == (Tile const& tA, int const tB);
	friend bool operator == (int const tA, Tile const& tB);

private:
	int m_x;
	int m_y;
	int m_value;

	bool m_justMerged; // Tracks tiles that merged together
};

