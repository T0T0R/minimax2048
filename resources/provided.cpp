#include <iostream>
#include <vector>
#include <string>
#include <array>

#include "../src/mm2048.h"
#include "../src/GameManager.h"
#include "../src/Grid.h"
#include "../src/Tile.h"
#include "../src/Vec2D.h"
#include "./provided.h"



Vec2D rot90(Vec2D const& M){
	/***	Clockwise rotation at 90 degrees	***/
	Vec2D rotatedArray{};

	for (unsigned int i{0}; i<4; i++){
		for (unsigned int j{0}; j<4; j++){
			rotatedArray[j][3-i] = M[i][j];
		}
	}

	return rotatedArray;
}


Vec2D glisse(Grid const& myGrid, std::string const& fleche){
    /*** fleche est une lettre indiquant dans quelle direction les tuiles
        doivent etre glissees ***/

	Vec2D M {myGrid.getGrid()};

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

    for (unsigned int j{0}; j<4; ++j){
        for (unsigned int i{2}; i>0; --i){//	Position initiale (dans les trois lignes du haut)

            if (M[i][j] != 0){	//Si il y a une tuile...
                
				scanner = i;
                while (scanner < imax){	//	... on regarde s il y a une tuile compatible en dessous
					++ scanner;

                    if ( M[scanner][j] == M[scanner-1][j] ){	//	Si on trouve une tuile identique, on les combine
						M[scanner][j] = M[scanner][j]*2;
						M[scanner-1][j] = 0;
                        imax = scanner - 1;

                    }else if ( M[scanner][j] == 0 ){	//	Si il n y a pas de tuile en dessous, on la deplace
						M[scanner][j] = M[scanner-1][j];
						M[scanner-1][j] = 0;

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


int fournir_note(Vec2D table){
	return 0;
}


bool isInside(std::vector<Vec2D> const& liste_coups, Vec2D const& coup){
	int tuiles_identiques {0};
	bool output {false};

	for (Vec2D coup_present : liste_coups){
	
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


int fournir_coups(Grid const& myGrid, bool const& trait, std::vector<Vec2D> &liste_coups){
    /*** Game est une matrice 4*4 contenant la valeur des tuiles, trait est vrai si le coup suivant
        consiste a glisser les tuiles, et faux si le coup suivant consiste a faire apparaitre
        un 2 ou un 4 sur la grille.
        La sortie est la liste de toutes les positions possibles apres ce coup ***/

	Vec2D grilleActuelle { myGrid.getGrid() };

	int note = fournir_note(grilleActuelle);

	Vec2D coup {};	//	Construit une grille vierge tampon

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
					if (grilleActuelle[i][j] == 0){
                        for (int n : valeursTuile){
							//	On construit une grille avec la tuile supplementaire et on la stocke

                            grilleActuelle[i][j] = n;
                            liste_coups.push_back(grilleActuelle);
                        }

						grilleActuelle[i][j] = 0;	//	On remet la grille dans son etat initial
                    }
                }
            }
        }
    }

    return EXIT_SUCCESS;
}
