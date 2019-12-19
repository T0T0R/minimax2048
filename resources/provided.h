#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <random>
#include <string>

#include "../src/mm2048.h"
#include "../src/GameManager.h"
#include "../src/Grid.h"
#include "../src/Tile.h"
#include "../src/Vec2D.h"


Vec2D rot90(Vec2D const& M);

Vec2D glisse(Vec2D const& position, std::string const& fleche);

int fournir_note(Vec2D table);

int evalNeighbors(Vec2D const& table, int const i, int const j, int const parentValue);

bool isInside(std::vector<std::pair<Vec2D, std::string>> const& liste_coups, Vec2D const& coup);

std::vector<std::pair<Vec2D,std::string>> fournir_coups(Vec2D const& position, bool const& trait);
