#pragma once


class Table
{
public:
	Table(std::default_random_engine& rd, unsigned int const& startTiles);
	~Table();

	std::array< std::array<unsigned int, 4>, 4> init(std::default_random_engine& rd, unsigned int const& startTiles);
	std::array< std::array<unsigned int, 4>, 4> getTable() const;
	unsigned long long int getNb() const;
	bool move(int const& dir);
	void display() const;

	bool cellsAvailable() const;
	void randomAvailableCell();

protected:
	unsigned int randNb(std::default_random_engine& rd, unsigned int max);

private:
	//4*4 grid containing the numbers :
	std::array< std::array<unsigned int,4> ,4> m_table;

	unsigned long long int m_nbInit;	//Contains the number of initialisations.


};

