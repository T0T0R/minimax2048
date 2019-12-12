#include <iostream>
#include <vector>

#include "./mm2048.h"
#include "./Vec2D.h"
#include "../resources/provided.h"
#include "./minimax.h"

int minimax(Vec2D const& grid, int depth, bool isPlayer){
    /* Returns the mark corresponding to the given grid, with depth of
        several other grids. */

    int globalMark {-1};
	std::vector<int> marks {};

    if (depth == 0){    // Base case.
        globalMark = fournir_note(grid);

    } else {    // Recursive case.

        std::vector<std::pair<Vec2D,std::string>> possibleMoves = fournir_coups(grid, isPlayer);

        for (std::pair<Vec2D,std::string> child: possibleMoves){   // Stores all marks for child grids.
                marks.push_back( minimax( child.first, depth-1, !isPlayer ));
        }


        if (isPlayer){  // Computes corresponding mark of grid, depending on the player.
            globalMark = *std::max_element(std::begin(marks), std::end(marks));
        }else{
            globalMark = *std::min_element(std::begin(marks), std::end(marks));
        }

    }
    return globalMark;
}
