//Author: Maxime MU 2023
//Description: Ce programme permet de trouver toutes les solutions possibles pour le jeu "Tetris"
//             en utilisant la programmation dynamique. La méthode de résolution est une fonction
//             récursive qui place les pièces sur le plateau de jeu. Le programme affiche le nombre
//             de solutions trouvées ainsi que le temps d'exécution.
//Date: 29/03/2023
//Processeur : Intel(R) Core(TM) i7-8550U CPU @ 1.80GHz   1.99 GHz 8 Go de RAM  64 bits Windows 11 Famille


//importation des librairies
#include <stdio.h>//pour les entrées/sorties
#include <stdbool.h>//pour les booléens
#include <time.h>//pour le temps

//définition des constantes
#define ROWS 8 //nombre de lignes
#define COLUMNS 7 //nombre de colonnes
#define PIECES 10 //nombre de pièces
#define ROTATIONS 4 //nombre de rotations

//définition des variables globales
int board[ROWS][COLUMNS] = {0}; //le plateau de jeu
int total = 0; //le nombre de solutions
int size; //la taille de la pièce
int rotation = 4; //le nombre de rotations

//définition des pièces et de leurs rotations
int pieces[PIECES][ROTATIONS][5][2] = {
    //Le L inversé
    {{{0, 1}, {1, 1}, {2, 1}, {3, 0}, {3,1}}, {{0, 0}, {1, 0}, {1, 1}, {1, 2}, {1,3}}, {{0, 0}, {0, 1}, {1, 0}, {2, 0}, {3,0}}, {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {1,3}}},

    //Le T
    {{{0, 1}, {1, 1}, {2, 0}, {2, 1}, {2,2}}, {{0, 0}, {1, 0}, {1, 1}, {1, 2}, {2,0}}, {{0, 0}, {0, 1}, {0, 2}, {1, 1}, {2,1}}, {{0, 2}, {1, 0}, {1, 1}, {1, 2}, {2,2}}},

    //Le coin
    {{{0,0}, {0,1}, {0,2}, {1,0}, {2,0}}, {{0,0}, {0,1}, {0,2}, {1, 2}, {2,2}}, {{0, 2}, {1, 2}, {2, 0}, {2,1}, {2,2}}, {{0, 0}, {1, 0}, {2, 0}, {2,1}, {2,2}}},

    //Le Z (symétrie)
    {{{0,0}, {0,1}, {1,1}, {2, 1}, {2,2}}, {{0, 2}, {1, 0}, {1, 1}, {1, 2}, {2,0}}},

    //Le long Z
    {{{0,1}, {1,1}, {2,0}, {2, 1}, {3,0}}, {{0, 0}, {0, 1}, {1, 1}, {1, 2}, {1,3}}, {{0,1}, {1,0}, {1,1}, {2, 0}, {3,0}}, {{0,0}, {0,1}, {0, 2}, {1, 2}, {1,3}}},

    //LE U
    {{{0,0}, {0,2}, {1,0}, {1, 1}, {1,2}}, {{0, 0}, {0, 1}, {1, 0}, {2,0}, {2,1}}, {{0,0}, {0,1}, {0,2}, {1,0}, {1,2}}, {{0,0},{0,1},{1,1},{2,0},{2,1}}},

    //Le radio
    {{{0, 0}, {1, 0}, {1, 1}, {2,0}, {2,1}}, {{0, 0}, {0, 1}, {0,2}, {1,0}, {1,1}}, {{0,0}, {0,1}, {1,0}, {1,1}, {2,1}}, {{0,1},{0,2},{1,0},{1,1},{1,2}}},

    //Le petit L inversé
    {{{0,1}, {1,1}, {2,0}, {2,1}}, {{0,0}, {1,0}, {1,1}, {1,2}}, {{0,0}, {0,1}, {1,0}, {2,0}}, {{0,0}, {0,1}, {0,2}, {1,2}}},

    //Le Z inversé debout
    {{{0,0}, {1,0}, {1,1}, {2,1}}, {{0,1}, {0,2}, {1,0}, {1,1}}},

    //Le I renversé
    {{{0,0}, {0,1}, {0,2}, {0,3}}, {{0,0}, {1,0}, {2,0}, {3,0}}},
};

//définition des fonctions
bool placePiece(int piece_num, int rotation_num, int x, int y, int size, int rotation);
void removePiece(int piece_num, int rotation_num, int x, int y, int size, int rotation);
void solvePuzzle(int piece_num, int number, int size, int rotation);
bool isEncircled(int matrix[ROWS][COLUMNS]);
void chooseDate(int day, int month, int year);

//Méthode principale
int main(){
    double time_spent = 0.0; //variable qui va contenir le temps d'exécution du programme
 
    clock_t begin = clock(); //on récupère le temps au début de l'exécution du programme

    //On initialise le plateau
    board[0][6] = 11;
    board[1][6] = 11;
    board[7][0] = 11;
    board[7][1] = 11;
    board[7][2] = 11;
    board[7][3] = 11;

    //Samedi 1 janvier
    chooseDate(6, 1, 1);

    //on commence par la pièce numéro 0
    //on a en tout PIECES-1 pièces à placer
    //on initialise la size à 0 et la rotation à 0
    solvePuzzle(0, PIECES-1, 0, 0); //on appelle la méthode qui résout le puzzle
    printf("total = %i\n", total); //on affiche le nombre de solutions

    clock_t end = clock(); //on récupère le temps à la fin de l'exécution du programme
 
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC; //on calcule le temps d'exécution du programme
 
    printf("Le temps écoulé est %f secondes", time_spent); //on affiche le temps d'exécution du programme

    return 0;
}

//Méthode qui vérifie si la pièce peut être placée et la place si c'est possible
bool placePiece(int piece_num, int rotation_num, int x, int y, int size, int rotation) {
    for (int i = 0; i < size; i++)
    {
        int piece_x = pieces[piece_num][rotation_num][i][0];//on récupère la coordonnée x de la pièce
        int piece_y = pieces[piece_num][rotation_num][i][1];//on récupère la coordonnée y de la pièce

        //on vérifie si la pièce est dans le plateau
        if (x + piece_x < 0 || x + piece_x >= ROWS || y + piece_y < 0 || y + piece_y >= COLUMNS) 
        {
            return false; //si elle n'est pas dans le plateau, on retourne faux
        }

        //on vérifie si la pièce est sur une autre pièce
        if (board[x + piece_x][y + piece_y] != 0) 
        {
            return false; //si elle est sur une autre pièce, on retourne faux
        }
    }

    //on place la pièce
    for (int i = 0; i < size; i++) 
    {
        int piece_x = pieces[piece_num][rotation_num][i][0]; //on récupère la coordonnée x de la pièce
        int piece_y = pieces[piece_num][rotation_num][i][1]; //on récupère la coordonnée y de la pièce
        board[x + piece_x][y + piece_y] = piece_num + 1;} //on place la pièce
    return true; //on retourne vrai
}

//Méthode qui enlève la pièce du plateau
void removePiece(int piece_num, int rotation_num, int x, int y, int size, int rotation) {
    //on enlève la pièce
    for (int i = 0; i < size; i++) 
    {
        int piece_x = pieces[piece_num][rotation_num][i][0]; //on récupère la coordonnée x de la pièce
        int piece_y = pieces[piece_num][rotation_num][i][1]; //on récupère la coordonnée y de la pièce
        board[x + piece_x][y + piece_y] = 0; //on enlève la pièce
    }
}

//Méthode qui vérifie si il y a un 0 isolé dans le plateau (0 isolé = plateau non rempli)
bool isEncircled(int matrix[ROWS][COLUMNS]) {
    int i, j, isolated; //isolated = 0 si le 0 n'est pas isolé, 1 sinon

    // On parcourt le plateau
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLUMNS; j++) {
            isolated = 1; //on initialise à 1

            if (matrix[i][j] == 0) {
                // Vérifie s'il y a un voisin qui est également un 0 (en haut, en bas, à gauche ou à droite)
                if ((i > 0 && matrix[i-1][j] == 0) || (i < ROWS-1 && matrix[i+1][j] == 0) ||
                    (j > 0 && matrix[i][j-1] == 0) || (j < COLUMNS-1 && matrix[i][j+1] == 0)) {
                    isolated = 0; //on retourne faux
                }
                // Si le 0 est isolé, on peut retourner immédiatement
                if (isolated) {
                    return true; //on retourne vrai
                }
            }
        }
    }
    return false; //on retourne faux
}

//Méthode qui résout le puzzle en utilisant la méthode de backtracking (on place une pièce, on vérifie si le plateau est rempli, si ce n'est pas le cas, on place la pièce suivante, etc.)
void solvePuzzle(int piece_num, int number, int size, int rotation) {
    int r, i ,j; //r = rotation, i = ligne, j = colonne

    //on vérifie si la pièce est une pièce de taille 5 ou 4
    if(piece_num <=6)
    {
        size = 5; //on définit la taille de la pièce
        //On vérifie si la pièce est symétrique ou non
        if(piece_num == 3){
            rotation = 2; //on définit le nombre de rotations de la pièce
        }
        else{
            rotation = 4; //on définit le nombre de rotations de la pièce
        }
    }
    else{
        size = 4; //on définit la taille de la pièce
        //On vérifie si la pièce est symétrique ou non
        if(piece_num >= 8){
            rotation = 2; //on définit le nombre de rotations de la pièce
        }else{
        rotation = 4; //on définit le nombre de rotations de la pièce
        }
    }

    //On teste toutes les rotations de la pièce
    for(r = 0; r < rotation; r++){
        //On parcourt le plateau
        for(i = 0; i < ROWS; i++ ){
            for(j = 0; j < COLUMNS; j++){
                //On vérifie si la pièce peut être placée en (i,j) avec la rotation r et la place si c'est le cas
                if(placePiece(piece_num, r, i, j, size, rotation))
                {
                    //On affiche le plateau sur la console (pour vérifier que le programme fonctionne) 
                    /*for (int y = 0; y < ROWS; y++) {
                            for (int x = 0; x < COLUMNS; x++) {
                            printf("%d ", board[y][x]);
                            }
                            printf("\n");
                        }
                    printf("\n");*/

                    //On vérifie si le plateau est rempli (si le nombre de pièces placées est égal au nombre de pièces)
                    if (piece_num == number){
                        total += 1; //on incrémente le nombre de solutions
                    }
                    //On vérifie si le plateau est rempli et si le 0 n'est pas isolé
                    else if(!isEncircled(board)){
                        solvePuzzle(piece_num + 1, number, size, rotation); //on appelle la méthode récursivement pour placer la pièce suivante 
                    }
                    //On enlève la pièce du plateau (backtracking)
                    removePiece(piece_num, r, i, j, size, rotation);
                }
            }
        }
    }
}

void chooseDate(int s, int j, int m){
    switch (m)
    {
    case 1:
        board[0][0] = 11;
        break;
    case 2:
        board[0][1] = 11;
        break;
    case 3:
        board[0][2] = 11;
        break;
    case 4:
        board[0][3] = 11;
        break;
    case 5:
        board[0][4] = 11;
        break;
    case 6:
        board[0][5] = 11;
        break;
    case 7:
        board[1][0] = 11;
        break;
    case 8:
        board[1][1] = 11;
        break;
    case 9:
        board[1][2] = 11;
        break;
    case 10:
        board[1][3] = 11;
        break;
    case 11:
        board[1][4] = 11;
        break;
    case 12:
        board[1][5] = 11;
        break;
    }
    switch (j)
    {
    case 1:
        board[2][0] = 11;
        break;
    case 2:
        board[2][1] = 11;
        break;
    case 3:
        board[2][2] = 11;
        break;
    case 4:
        board[2][3] = 11;
        break;
    case 5:
        board[2][4] = 11;
        break;
    case 6:
        board[2][5] = 11;
        break;
    case 7:
        board[2][6] = 11;
        break;
    case 8:
        board[3][0] = 11;
        break;
    case 9:
        board[3][1] = 11;
        break;
    case 10:
        board[3][2] = 11;
        break;
    case 11:
        board[3][3] = 11;
        break;
    case 12:
        board[3][4] = 11;
        break;
    case 13:
        board[3][5] = 11;
        break;
    case 14:
        board[3][6] = 11;
        break;
    case 15:
        board[4][0] = 11;
        break;
    case 16:
        board[4][1] = 11;
        break;
    case 17:
        board[4][2] = 11;
        break;
    case 18:
        board[4][3] = 11;
        break;
    case 19:
        board[4][4] = 11;
        break;
    case 20:
        board[4][5] = 11;
        break;
    case 21:
        board[4][6] = 11;
        break;
    case 22:
        board[5][0] = 11;
        break;
    case 23:
        board[5][1] = 11;
        break;
    case 24:
        board[5][2] = 11;
        break;
    case 25:
        board[5][3] = 11;
        break;
    case 26:
        board[5][4] = 11;
        break;
    case 27:
        board[5][5] = 11;
        break;
    case 28:
        board[5][6] = 11;
        break;
    case 29:
        board[6][0] = 11;
        break;
    case 30:
        board[6][1] = 11;
        break;
    case 31:
        board[6][2] = 11;
        break;
    }
    switch (s)
    {
    case 7:
        board[6][3] = 11;
        break;
    case 1:
        board[6][4] = 11;
        break;
    case 2:
        board[6][5] = 11;
        break;
    case 3:
        board[6][6] = 11;
        break;
    case 4:
        board[7][4] = 11;
        break;
    case 5:
        board[7][5] = 11;
        break;
    case 6:
        board[7][6] = 11;
        break;
    }
}
