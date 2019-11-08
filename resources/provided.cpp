#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <iterator>

#include "../src/mm2048.h"
#include "../src/GameManager.h"
#include "../src/Grid.h"
#include "../src/Tile.h"


std::array<std::array<Tile, 4>, 4> rot90(std::array<std::array<Tile, 4>, 4> const& M){
	std::array<std::array<Tile, 4>, 4> rotatedArray{};

	for (unsigned int i{0}; i<4; i++){
		for (unsigned int j{0}; j<4; j++){
			rotatedArray[j][3-i] = M[i][j];
		}
	}

	return rotatedArray;
}


std::array<std::array<Tile, 4>, 4> glisse(Grid const& myGrid, std::string const& fleche){
    /*** fleche est une lettre indiquant dans quelle direction les tuiles
        doivent etre glissees ***/

	std::array<std::array<Tile, 4>, 4> M = myGrid.getGrid();

	//	Fait pivoter la grille pour traiter les quatre cas de figure de façon identique.
	//	La grille traitée sera pivotée dans le sens inverse après le glissement des tuiles.
    if (fleche == "g"){
        M = rot90(M);
    }else if (fleche == "h"){
        M = rot90(rot90(M));
    }else if (fleche == "d"){
        M = rot90(rot90(rot90(M)));
    }

	int imax{4};
    int scanner;

    for (int j{0}; j<4; ++j){
        for (int i{2}; i>0; --i){//	Position initiale (dans les trois lignes du haut)

            if (M[i][j].getValue() != 0){	//Si il y a une tuile...
                
				scanner = i;
                while (scanner < imax){	//	... on regarde s il y a une tuile compatible en dessous
					++ scanner;

                    if ( M[scanner][j] == M[scanner-1][j] ){	//	Si on trouve une tuile identique, on les combine
						M[scanner][j].setValue( M[scanner][j].getValue()*2 );
						M[scanner-1][j].setValue(0);
                        imax = scanner - 1;

                    }else if ( M[scanner][j] == 0 ){	//	Si il n y a pas de tuile en dessous, on la deplace
						M[scanner][j].setValue( M[scanner-1][j].getValue() );
						M[scanner-1][j].setValue(0);

                    }else {	
                        imax = scanner-1;
                    }
                }
            }
        }
    }


	//	La grille est remise en position initiale
    if(fleche == "g"){
        M = rot90(rot90(rot90(M)));
    }else if (fleche == "h"){
        M = rot90(rot90(M));
    }else if (fleche == "d"){
        M = rot90(M);
    }

	return M;
}


int fournir_note(std::array<std::array<Tile, 4>, 4> grid){
	return 0;
}


bool isInside(std::vector<std::array<std::array<Tile, 4>, 4>> const& liste_coups, std::array<std::array<Tile, 4>, 4> const& coup){
	int tuiles_identiques {0};
	bool output {false};

	for (std::array<std::array<Tile, 4>, 4> coup_present : liste_coups){
	
		tuiles_identiques = 0;

		for (int i = 0; i < 4; i++) {
			for  (int j = 0; j < 4; j++) {

				if(coup_present[i][j]==coup[i][j]){
					tuiles_identiques++;
				}

			}
		}

		if (tuiles_identiques==16){
			output = true;
			break;
		}
	
	}	

	return output;
}


int fournir_coups(Grid const& myGrid, bool const& trait, std::vector<std::array<std::array<Tile, 4>, 4>> &liste_coups){
    /*** Game est une matrice 4*4 contenant la valeur des tuiles, trait est vrai si le coup suivant
        consiste a glisser les tuiles, et faux si le coup suivant consiste a faire apparaitre
        un 2 ou un 4 sur la grille.
        La sortie est la liste de toutes les positions possibles apres ce coup ***/

	int note = fournir_note(myGrid.getGrid());


	std::array<std::array<Tile, 4>, 4> grille = myGrid.getGrid();
	std::array<std::array<Tile, 4>, 4> coup = myGrid.getGrid();	//	Construit une grille vierge tampon

	std::array<std::string, 4> directions = {"g", "d", "h", "b"};
	std::array<int, 2> valeursTuile = {2, 4};


    if (note != -1){
        if (trait){ //	Si on glisse les tuiles


			for (std::string fleche : directions){
				//	On glisse les tuiles dans les quatre sens, et on stocke les quatre 
				//	grilles obtenues

                coup = glisse(myGrid,fleche);

				if ( !isInside(liste_coups, coup)){
					liste_coups.push_back(coup);
				}
            }

        } else {	//	Si la tuile 2 ou 4 apparait
            for (int i {0}; i<4; ++i){
                for (int j {1}; j<4; ++j){
					if (myGrid.cellContent(Position{i,j}) == 0){
                        for (int n : valeursTuile){
							//	On construit une grille avec la tuile supplementaire et on la stocke

                            grille[i][j] = n;
                            liste_coups.push_back(grille);
                        }

						grille[i][j] = 0;	//	On remet la grille dans son etat initial
                    }
                }
            }
        }
    }

    return EXIT_SUCCESS;
}
