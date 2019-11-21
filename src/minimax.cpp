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
        globalMark = note(grid);

    } else {    // Recursive case.

        std::vector<Vec2D> possibleMoves = fournir_coups(grid, isPlayer);

        for (Vec2D child: possibleMoves){   // Stores all marks for child grids.
                marks.push_back( minimax( child, depth-1, !isPlayer ));
        }


        if (isPlayer){  // Computes corresponding mark of grid, depending on the player.
            globalMark = *std::max_element(std::begin(marks), std::end(marks));
        }else{
            globalMark = *std::min_element(std::begin(marks), std::end(marks));
        }

    }
    return globalMark;
}


int note(Vec2D const& grid){
    /* Returns the mark corresponding to the given grid. */
    /// Sum of :
    //  - Sum of all tiles,
    //  - Bonus : if the highest tile is in the corner,
    //  - Bonus : if both highest tile and second to highest tile are next to each other,
    //  - Bonus : value/tile (favor |0|1024| against |512|512|)

    return EXIT_SUCCESS;
}
