#include <stdio.h>
#include <stdbool.h>
#include <time.h>  

#define NbRows 8
#define NbColumns 7
#define NbPieces 10
#define MaxRotations 4


int board[NbRows][NbColumns] = {0};
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


bool PlacePiece(int piece_num, int rotation_num, int x, int y) {
    if(piece_num <=6)
    {
        size = 5;
        if(piece_num == 3){
            rotation = 2;
        }
        else{
            rotation = 4;
        }
    }
    else{
        size = 4;
        if(piece_num >= 8){
            rotation = 2;
        }else{
        rotation = 4;
        }
    }


    for (int i = 0; i < size; i++) {
        int piece_x = pieces[piece_num][rotation_num][i][0];
        int piece_y = pieces[piece_num][rotation_num][i][1];
        if (x + piece_x < 0 || x + piece_x >= NbRows || y + piece_y < 0 || y + piece_y >= NbColumns) {
            return false;
        }
        if (board[x + piece_x][y + piece_y] != 0) {
            return false;
        }
    }


    for (int i = 0; i < size; i++) {
        //printf("%i\n", size);
        int piece_x = pieces[piece_num][rotation_num][i][0];
        int piece_y = pieces[piece_num][rotation_num][i][1];
        board[x + piece_x][y + piece_y] = piece_num + 1;}
    return true;

}

void remove_piece(int piece_num, int rotation_num, int x, int y) {
    if(piece_num <=6)
    {
        size = 5;
        if(piece_num == 3){
            rotation = 2;
        }
        else{
            rotation = 4;
        }
    }
    else{
        size = 4;
        if(piece_num >= 8){
            rotation = 2;
        }else{
        rotation = 4;
        }
    }
    //printf("piece_num = %d, size = %d, rotation_num = %d, x = %d, y= %d\n", piece_num, size, rotation_num, x, y);

    for (int i = 0; i < size; i++) {
        int piece_x = pieces[piece_num][rotation_num][i][0];
        int piece_y = pieces[piece_num][rotation_num][i][1];
        board[x + piece_x][y + piece_y] = 0;
    }
}


void solve_tetro_puzzle(int piece_num, int number) {
    int r, i ,j;

    if(piece_num <=6)
    {
        if(piece_num == 3){
            rotation = 2;
        }
        else{
            rotation = 4;
        }
    }
    else{
        if(piece_num >= 8){
            rotation = 2;
        }else{
        rotation = 4;
        }
    }

    //printf("Placing piece current number : %i\n", piece_num);

    for(r = 0; r < rotation; r++){
        for(i = 0; i < NbRows; i++){
            for(j = 0; j < NbColumns; j++){
                //printf("i = %i, j = %i, r = %i\n", i, j, r);
                if(PlacePiece(piece_num, r, i, j))
                {

                    /*for (int y = 0; y < NbRows; y++) {
                            for (int x = 0; x < NbColumns; x++) {
                            printf("%d ", board[y][x]);
                            }
                            printf("\n");
                        }
                    printf("\n");*/

                    //printf("Piece placed number : %i\n", piece_num);
                    if (piece_num == number)
                    {

                        total += 1;
                        /*printf("Solution found (%d)!\n", total);

                        for (int x = 0; x < NbRows; x++) {
                            for (int y = 0; y < NbColumns; y++) {
                            printf("%d ", board[x][y]);
                            }
                            printf("\n");
                        }
                        printf("\n");*/

                    }
                    else
                    {
                        //printf("%s\n", "Placing another piece");
                        solve_tetro_puzzle(piece_num + 1, number);
                    }
                    //printf("Removing piece number %i\n", piece_num+1);
                    remove_piece(piece_num, r, i, j);
                }
            }
        }
    }
    //printf("%s\n", "all rotations done");
}



int main(){

    // to store the execution time of code
    double time_spent = 0.0;
 
    clock_t begin = clock();

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
    solve_tetro_puzzle(0, NbPieces-1);
    printf("total = %i\n", total);

    clock_t end = clock();
 
    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
 
    printf("The elapsed time is %f seconds", time_spent);

    return 0;
}
