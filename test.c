#include <stdio.h>
#include <stdbool.h>

#define NbRows 8
#define NbColumns 7
#define NbPieces 10
#define MaxRotations 4


int board[NbRows][NbColumns] = {0};
int sum = 0;
int size;


int pieces[NbPieces][MaxRotations][5][2] = {

    //Le L inversé
    {{{0, 1}, {1, 1}, {2, 1}, {3, 0}, {3,1}}, {{0, 0}, {1, 0}, {1, 1}, {1, 2}, {1,3}}, {{0, 0}, {0, 1}, {1, 0}, {2, 0}, {3,0}}, {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {1,3}}},

    //Le T
    {{{0, 1}, {1, 1}, {2, 0}, {2, 1}, {2,2}}, {{0, 0}, {1, 0}, {1, 1}, {1, 2}, {2,0}}, {{0, 0}, {0, 1}, {0, 2}, {1, 1}, {2,1}}, {{0, 2}, {1, 0}, {1, 1}, {1, 2}, {2,2}}},

    //Le coin
    {{{0,0}, {0,1}, {0,2}, {1,0}, {2,0}}, {{0,0}, {0,1}, {0,2}, {1, 2}, {2,2}}, {{0, 2}, {1, 2}, {2, 0}, {2,1}, {2,2}}, {{0, 0}, {1, 0}, {2, 0}, {2,1}, {2,2}}},

    //Le Z (symétrie)
    {{{0,0}, {0,1}, {1,1}, {2, 1}, {2,2}}, {{0, 2}, {1, 0}, {1, 1}, {1, 2}, {2,0}}, {{0,0}, {0,1}, {1,1}, {2, 1}, {2,2}}, {{0, 2}, {1, 0}, {1, 1}, {1, 2}, {2,0}}},

    //Le long Z
    {{{0,1}, {1,1}, {2,0}, {2, 1}, {3,0}}, {{0, 0}, {0, 1}, {1, 1}, {1, 2}, {1,3}}, {{0,1}, {1,0}, {1,1}, {2, 0}, {3,0}}, {{0,0}, {0,1}, {0, 2}, {1, 2}, {1,3}}},

    //LE U
    {{{0,0}, {0,2}, {1,0}, {1, 1}, {1,2}}, {{0, 0}, {0, 1}, {1, 0}, {2,0}, {2,1}}, {{0,0}, {0,1}, {0,2}, {1,0}, {1,2}}, {{0,0},{0,1},{1,1},{2,0},{2,1}}},

    //Le radio
    {{{0, 0}, {1, 0}, {1, 1}, {2,0}, {2,1}}, {{0, 0}, {0, 1}, {0,2}, {1,0}, {1,1}}, {{0,0}, {0,1}, {1,0}, {1,1}, {2,1}}, {{0,1},{0,2},{1,0},{1,1},{1,2}}},

    //Le petit L inversé
    {{{0,1}, {1,1}, {2,0}, {2,1}}, {{0,0}, {1,0}, {1,1}, {1,2}}, {{0,0}, {0,1}, {1,0}, {2,0}}, {{0,0}, {0,1}, {0,2}, {1,2}}},

    //Le Z inversé debout
    {{{0,0}, {1,0}, {1,1}, {2,1}}, {{0,1}, {0,2}, {1,0}, {1,1}}, {{0,0}, {1,0}, {1,1}, {2,1}}, {{0,1}, {0,2}, {1,0}, {1,1}}},

    //Le I renversé
    {{{0,0}, {0,1}, {0,2}, {0,3}}, {{0,0}, {1,0}, {2,0}, {3,0}},{{0,0}, {0,1}, {0,2}, {0,3}}, {{0,0}, {1,0}, {2,0}, {3,0}}},

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
    }
    else{
        size = 4;
    }

    // place the piece on the board if it fits
    for (int i = 0; i < size; i++) {
        int piece_x = pieces[piece_num][rotation_num][i][0];
        int piece_y = pieces[piece_num][rotation_num][i][1];
        if (x + piece_x < 0 || x + piece_x >= NbRows || y + piece_y < 0 || y + piece_y >= NbColumns) {
            return false; // piece is out of bounds
        }
        if (board[x + piece_x][y + piece_y] != 0) {
            return false; // piece overlaps with another piece
        }
    }

    // place the piece on the board
    for (int i = 0; i < size; i++) {
        //printf("%i\n", size);
        int piece_x = pieces[piece_num][rotation_num][i][0];
        int piece_y = pieces[piece_num][rotation_num][i][1];
        board[x + piece_x][y + piece_y] = piece_num + 1; // mark the square as occupied by the piece (use piece_num + 1 to avoid using 0 as a valid piece number)
        }
    return true; // successfully placed the piece
}

void remove_piece(int piece_num, int rotation_num, int x, int y) {
    if(piece_num <=6)
    {
        size = 5;
    }
    else{
        size = 4;
    }
    //printf("piece_num = %d, size = %d, rotation_num = %d, x = %d, y= %d\n", piece_num, size, rotation_num, x, y);
    // remove the piece from the board
    for (int i = 0; i < size; i++) {
        int piece_x = pieces[piece_num][rotation_num][i][0];
        int piece_y = pieces[piece_num][rotation_num][i][1];
        board[x + piece_x][y + piece_y] = 0; // mark the square as unoccupied
    }
}


void solve_tetro_puzzle(int piece_num, int number) {
    int r, i ,j;

    //printf("Placing piece current number : %i\n", piece_num);

    // recursively try to place each piece on the board
    for(r = 0; r < MaxRotations; r++){
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

                        sum += 1;
                        // all pieces have been successfully placed on the board
                        printf("%s", "Solution found !\n");


                        solve_tetro_puzzle(piece_num + 1, number);

                        //remove_piece(piece_num, r, i, j);
                        continue;
                    }
                    else
                    {
                        //printf("%s\n", "Placing another piece");
                        solve_tetro_puzzle(piece_num + 1, number);
                    }
                    //printf("Removing piece number %i\n", piece_num+1);
                    remove_piece(piece_num, r, i, j);
                    /*for (int y = 0; y < NbRows; y++) {
                            for (int x = 0; x < NbColumns; x++) {
                                printf("%d ", board[y][x]);
                            }
                            printf("\n");
                            }*/
                }
            }
        }
    }
    //printf("%s\n", "all rotations done");
}



int main() {

    solve_tetro_puzzle(0, NbPieces-1);
    printf("sum = %i\n", sum);

    return 0;
}

