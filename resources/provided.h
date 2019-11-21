#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <random>

#include "../src/mm2048.h"
#include "../src/GameManager.h"
#include "../src/Grid.h"
#include "../src/Tile.h"
#include "../src/Vec2D.h"


Vec2D rot90(Vec2D const& M);

Vec2D glisse(Vec2D const& position, std::string const& fleche);

int fournir_note(Vec2D table);

bool isInside(std::vector<Vec2D> const& liste_coups, Vec2D const& coup);

std::vector<Vec2D> fournir_coups(Vec2D const& position, bool const& trait);
