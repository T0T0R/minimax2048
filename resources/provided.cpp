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
	/***	Anti-clockwise rotation at 90 degrees.	***/
	Vec2D rotatedArray{};

	for (unsigned int i{0}; i<4; i++){
		for (unsigned int j{0}; j<4; j++){
			rotatedArray[3-j][i] = M[i][j];
		}
	}

	return rotatedArray;
}


Vec2D glisse(Vec2D const& position, std::string const& fleche){
    /*** fleche est une lettre indiquant dans quelle direction les tuiles
        doivent etre glissees. ***/

	Vec2D M = position;

	//	Fait pivoter la grille pour traiter les quatre cas de figure de facon identique.
	//	La grille traitee sera pivotee dans le sens inverse apres le glissement des tuiles.
    if (fleche == "g"){
        M = rot90(M);
    }else if (fleche == "h"){
        M = rot90(rot90(M));
    }else if (fleche == "d"){
        M = rot90(rot90(rot90(M)));
    }

	int imax;
    int scanner;

    for (unsigned int j{0}; j<4; ++j){
        imax = 3;
        for (int i{2}; i>=0; --i){//	Position initiale (dans les trois lignes du haut).
            if (M[i][j] != 0){	//	Si il y a une tuile ?
                
				scanner = i;
                while (scanner < imax){	//	on regarde s il y a une tuile compatible en dessous.
					++ scanner;

                    if ( M[scanner][j] == M[scanner-1][j] ){	//	Si on trouve une tuile identique, on les combine.
						M[scanner][j] = M[scanner][j]*2;
						M[scanner-1][j] = 0;
                        imax = scanner - 1;

                    }else if ( M[scanner][j] == 0 ){	//	Si il n y a pas de tuile en dessous, on la deplace.
						M[scanner][j] = M[scanner-1][j];
						M[scanner-1][j] = 0;

                    }else {	
                        imax = scanner-1;
                    }
                }
            }
        }
    }


	//	La grille est remise en position initiale.
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
	return table[0][0];
    /* Returns the mark corresponding to the given grid. */
   /// Sum of :
   //  - Sum of all tiles,
   //  - Bonus : if the highest tile is in the corner,
   //  - Bonus : if both highest tile and second to highest tile are next to each other,
   //  - Bonus : value/tile (favor |0|1024| against |512|512|)

   //return EXIT_SUCCESS;
}


bool isInside(std::vector<std::pair<Vec2D, std::string>> const& liste_coups, Vec2D const& coup){
	bool output {false};

	for (std::pair<Vec2D, std::string> coup_present : liste_coups){

		if (coup_present.first==coup){
			output = true;
			break;
		}

	}	
	return output;
}


std::vector<std::pair<Vec2D, std::string>> fournir_coups(Vec2D const& position, bool const& trait){
    /*** position est une matrice 4*4 contenant la valeur des tuiles, trait est vrai si le coup suivant
        consiste a glisser les tuiles, et faux si le coup suivant consiste a faire apparaitre
        un 2 ou un 4 sur la grille.
        La sortie est la liste de toutes les positions possibles apres ce coup, associees a la direction
        qui a engendre ce coup. ***/

	Vec2D grilleActuelle = position;

	std::vector<std::pair<Vec2D,std::string>> liste_coups;
	Vec2D coup {};	//	Construit une grille vierge tampon.

	std::array<std::string, 4> directions = {"g", "d", "h", "b"};
	std::array<int, 2> valeursTuile = {2, 4};


    if (fournir_note(grilleActuelle) != -1){
        if (trait){ //	Si on glisse les tuiles,


			for (std::string fleche : directions){
				//	On glisse les tuiles dans les quatre sens, et on stocke les quatre 
				//	grilles obtenues.

                coup = glisse(position,fleche);

				if ( !isInside(liste_coups, coup) && coup!=grilleActuelle){
					liste_coups.push_back(std::pair<Vec2D, std::string>(coup, fleche));
				}
            }

        } else {	//	Si la tuile 2 ou 4 apparait,
            for (int i {0}; i<4; ++i){
                for (int j {1}; j<4; ++j){
					if (grilleActuelle[i][j] == 0){
                        for (int n : valeursTuile){
							//	On construit une grille avec la tuile supplementaire et on la stocke.

                            grilleActuelle[i][j] = n;
                            liste_coups.push_back(std::pair<Vec2D, std::string>(grilleActuelle, "o"));
                        }

						grilleActuelle[i][j] = 0;	//	On remet la grille dans son etat initial.
                    }
                }
            }
        }
    }

    return liste_coups;
}
