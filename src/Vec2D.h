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

	static Vec2D eye();

	std::array<std::array<int,4>,4> & getVec2D() ;
	void display() const;

	std::array<int, 4> & operator[] (unsigned int index) ;
	std::array<int, 4> operator[] (unsigned int index) const;

	Vec2D& operator += (Vec2D const& other);
		template <typename Tcoeff>
	Vec2D& operator *= (Tcoeff const& lambda){
			for (unsigned int i {0}; i<m_size; ++i) {
				for (unsigned int j {0}; j<m_size; ++j) {
					m_table[i][j] = lambda * m_table[i][j];
				}
			}
			return *this;
		}
		

	friend bool operator == (Vec2D const& vecA, Vec2D const& vecB);
	friend Vec2D operator +(Vec2D vA, Vec2D const& vB);
		template <typename Tcoeff>
	friend Vec2D operator * (Vec2D vA, Tcoeff const& lambda) {
		return vA *= lambda;
		}
		template <typename Tcoeff>
	friend Vec2D operator * (Tcoeff const& lambda, Vec2D vA) {
		return vA *= lambda;
		}
		template <typename Tmatrix>
	friend Vec2D operator / (Tmatrix const& mA, Tmatrix const& mB) {
		//	matrix product.
		Vec2D output;
		auto sum {0};
		int a {0};
		int b {0};
		for (unsigned int i {0}; i<4; ++i) {
			for (unsigned int j {0}; j<4; ++j) {

				for (unsigned int p {0}; p<4; ++p) {
					a = mA[i][p];
					b = mB[p][j];
					sum += (a*b);
				}

				output[i][j] = sum;
				sum = 0;
			}
		}
		return output;
	}

private:
	// 4*4 grid containing the numbers :
	std::array<std::array<int,4>,4> m_table;
	unsigned int m_size;
};

