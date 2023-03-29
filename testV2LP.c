#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define NbRows 8
#define NbColumns 7
#define NbPieces 10
#define MaxRotations 4


int board[NbRows][NbColumns] = {0};
int solutions[100][NbRows][NbColumns] = {0};
int total = 0;
int size;
int rotation = 4;
/*
bool matrixHasNoZero(int matrix[NbRows][NbColumns]) {
    for (int i = 0; i < NbRows; i++) {
        for (int j = 0; j < NbColumns; j++) {
            if (matrix[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}*/

int index = 0;

void printBoard(int tboard[][7]){
    index++;

    printf("\n\n");
    printf("%i", index);
    printf("\n\n");
    for (int i = 0; i< NbRows; i++){
        for (int j = 0; j < NbColumns; j++){
            printf("| %i |", tboard[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

int pieces[NbPieces][MaxRotations][5][2] = {

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

    //Le L
    //{{{0,0}, {1,0}, {2,0}, {2,1}}, {{0,0}, {0,1}, {0,2}, {1,0}}, {{0,0}, {0,1}, {1,1}, {1,2}}, {{0,2}, {1,0}, {1,1}, {1,2}}},
    //I
    //{{{0,0}, {1,0}}, {{0,0}, {1,0}}},
    //Le coin
    //{{{0,0}, {1,0}, {1,1}}, {{0,0}, {0,1}, {1,0}}, {{0,0}, {0,1}, {1,1}}, {{0,1}, {1,0}, {1,1}}}

};

int rotationsPieces[10][2] ={{5,4}, {5, 4}, {5, 4}, {5, 2}, {5, 4}, {5, 4}, {5, 4}, {4, 4}, {4, 2}, {4, 2}};
int idPieces[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};


bool placePiece(int piece_num, int rotation_num, int x, int y,int tboard[][7]){


    size = rotationsPieces[piece_num][0];
    rotation = rotationsPieces[piece_num][1];


    for (int i = 0; i < size; i++) {
        int piece_x = pieces[piece_num][rotation_num][i][0];
        int piece_y = pieces[piece_num][rotation_num][i][1];
        if (x + piece_x < 0 || x + piece_x >= NbRows || y + piece_y < 0 || y + piece_y >= NbColumns) {
            return false;
        }
        if (tboard[x + piece_x][y + piece_y] != 0) {
            return false;
        }
    }


    for (int i = 0; i < size; i++) {
        //printf("%i\n", size);
        int piece_x = pieces[piece_num][rotation_num][i][0];
        int piece_y = pieces[piece_num][rotation_num][i][1];
        tboard[x + piece_x][y + piece_y] = piece_num + 1;
    }
    return true;
}

void remove_piece(int piece_num, int rotation_num, int x, int y, int tboard[][7]) {

    size = rotationsPieces[piece_num][0];
    rotation = rotationsPieces[piece_num][1];

    //printf("piece_num = %d, size = %d, rotation_num = %d, x = %d, y= %d\n", piece_num, size, rotation_num, x, y);

    for (int i = 0; i < size; i++) {
        int piece_x = pieces[piece_num][rotation_num][i][0];
        int piece_y = pieces[piece_num][rotation_num][i][1];
        tboard[x + piece_x][y + piece_y] = 0;
    }
}

bool isNew(int tboard[][7]){
    bool exists;
    for (int sol = 0; sol < total; sol++){
        exists = true;
        for (int i = 0; i < 8; i++){
            for (int j = 0; j <7; j++){
                solutions[total+1][i][j] = tboard[i][j];
                if (tboard[i][j] != solutions[sol][i][j]){
                    exists = false;
                }
            }
        }
        if(exists){return false;}
    }
    return true;
}

//recursive function which return the number of solutions for the problem given a board and a list of Pieces
int lpSolve(int tboard[][7], int piecesLeft[], int nbPieces){

    int totalSolutions = 0;
    bool notCoverable = true;
    //If there are no more pieces to use, then the board is full
    if (nbPieces == 0){
        if(isNew(tboard)){
            totalSolutions++;
            total++;
            printBoard(tboard);
            return totalSolutions;
        }
        return 0;
    }
    else{
        //from the top left corner, line by line
        for(int i =0; i<NbRows; i++){
            for(int j = 0; j<NbColumns; j++){
                notCoverable = true;
                //Trying every pieces for this particular slot, with every rotations also
                for (int n = 0; n < nbPieces; n++){
                    int idpiece = piecesLeft[n];
                    for (int k = 0; k < rotationsPieces[idpiece][1]; k++){
                        //When a piece can be added on the slot, we add it to the board and try finish with the pieces left
                        if(placePiece(idpiece, k, i, j, tboard)){
                            //printBoard(tboard);
                            //printf("e");
                            notCoverable = false;
                            //cheking if the bow is empty
                            int newList[nbPieces-1];
                            removeElement(piecesLeft, newList, idpiece, nbPieces);
                            totalSolutions += lpSolve(tboard, newList, nbPieces -1);
                            // Then remove the piece so we try to place other pieces there
                            remove_piece(idpiece, k, i, j, tboard);
                        }
                    }
                }
                //if no piece can be placed here, then there will not be any further solutions
                if(tboard[i][j]==0 && notCoverable){
                    return 0;
                }
            }
        }
        return totalSolutions;
    }
}

//Copy the int list of size n except the int element, then return it
void removeElement(int liste[], int newList[], int element, int n){
    int decalage = 0;
    for (int i = 0; i < n; i++){
        if(liste[i]==element){
            decalage--;
        }
        else{
            newList[i + decalage] = liste[i];
        }
    }
}



int main(){

    // to store the execution time of code
    double time_spent = 0.0;

    clock_t begin = clock();

    //add constraints to our board
    board[0][6] = 9;
    board[1][6] = 9;
    board[7][0] = 9;
    board[7][1] = 9;
    board[7][2] = 9;
    board[7][3] = 9;
    board[0][0] = 9;
    board[2][0] = 9;
    //board[6][3] = 9;
    board[7][6] = 9;

    total = lpSolve(board, idPieces, 10);
    printf("total = %i\n", total);

    clock_t end = clock();

    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("The elapsed time is %f seconds", time_spent);

    return 0;
}
