#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "hw1.h"

char board[MAX_ROWS][MAX_COLS] = {0};

/*
Hint: Consider adding a global variable to store a string large enough to store a board.
*/

void initialize_board(const char *initial_state, int num_rows, int num_cols) {
    int index=0;
    for (int i=0;i<num_rows;i++){
        for (int j=0;j<num_cols;j++){
            board[i][j]=initial_state[index];
            index++;
        }
    }
}

void print_board(int rows, int cols){
    
    for (int i=0;i<rows;i++){
        for (int j=0;j<cols;j++){
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int is_space_occupied(int row, int col){
    if (board[row][col] == '-'){
        return 0;
    }
    else{
        return 1;
    }
}
void set_piece(int row, int col , char piece){
    board[row][col]=piece;
}


int is_four_in_a_row(int rows, int cols, int row, int col, char piece) {
    
    if (piece!='-'){
        board[row][col] = piece;
    } else{
        return 0;
    }

   


    // Horizontal check
    int count_horizontal = 0;
    for (int c = 0; c < cols; c++) {
        if (board[row][c] == piece) {
            count_horizontal++;
            if (count_horizontal == 4) {
                board[row][col] = '-';
                return 1; 
            }
        } else {
            count_horizontal = 0; 
            
        }
    }

    // Vertical check
    int count_vertical = 0;
    for (int r = 0; r < rows; r++) {
        if (board[r][col] == piece) {
            count_vertical++;
            if (count_vertical == 4) {
                board[row][col] = '-';
                return 1; 
            }
        } else {
            count_vertical = 0; 
            
        }
    }


    //diagonal check

    int count_diagonal = 0;
    int start_row = row;
    int start_col = col;
    
    while (start_row > 0 && start_col > 0) {
        start_row--;
        start_col--;
    }

    count_diagonal = 0;
    while (start_row < rows && start_col < cols) {
        if (board[start_row][start_col] == piece) {
            count_diagonal++;
            if (count_diagonal == 4) {
                 board[row][col] = '-';
                return 1; 
            }
        } else {
            count_diagonal = 0;
            
        }
        start_row++;
        start_col++;
    }

    start_row = row;
    start_col = col;

    while (start_row > 0 && start_col < cols - 1) {
        start_row--;
        start_col++;
    }

    count_diagonal = 0;
    while (start_row < rows && start_col >= 0) {
        if (board[start_row][start_col] == piece) {
            count_diagonal++;
            if (count_diagonal == 4) {
                board[row][col] = '-';
                return 1; 
            }
        } else {
            count_diagonal = 0; 
           
        }
        start_row++;
        start_col--;
    }

    
    return 0;
    
}




int is_game_finished(int rows,int cols){
    int count=0;
    for (int i=0;i<rows;i++){
        for (int y=0;y<cols;y++){
            if (is_space_occupied(i,y)==0){
                count++;
            }
        } 
    } 

    if (count==0){
        return 1; //game is finished
    } 
    return 0;
       
}
int count_x(int num_rows, int num_cols){
    int num_x=0;
    for (int r=0;r<num_rows;r++){
        for (int c=0;c<num_cols;c++){
            if (board[r][c]=='x'){
                num_x++; 
            }
        }
    }
    return num_x; 
}

int count_o(int num_rows, int num_cols){
    int num_o=0;
    for (int r=0;r<num_rows;r++){
        for (int c=0;c<num_cols;c++){
            if (board[r][c]=='o'){
                num_o++; 
            }
        }
    }
    return num_o; 
}



//ASK FOR HELP ON THIS!
int solve(const char *initial_state, int num_rows, int num_cols, int *num_x, int *num_o){
    initialize_board(initial_state, num_rows, num_cols);

    //print_board(num_rows,num_cols);


    char piece1= 'x';
    char piece2 = 'o';
    char piece3 = '-';
    int counter_x = count_x(num_rows,num_cols);
    //num_x = &counter_x;;
    int counter_o = count_o(num_rows,num_cols);
    //num_o = &counter_o;
    //int failed_attempts=0;
    //printf("%i",*num_x);

   for (int r=0;r<num_rows;r++){
        for (int c=0;c<num_cols;c++){
            if (is_four_in_a_row(num_rows,num_cols,r,c,board[r][c])==1){
                //printf("ROW: %i, COL: %i, IS FOUR IN A ROW: %i ", r,c,is_four_in_a_row(num_rows,num_cols,r,c,board[r][c]));
                return INITIAL_BOARD_FOUR_IN_A_ROW;
            }
            if ((board[r][c]!='x')&&(board[r][c]!='o')&&(board[r][c]!='-')){
                return INITIAL_BOARD_INVALID_CHARACTERS;
            }

        }
   }

   //Check if potential four-in-a-row and block it
   int valid_move=1;
   int modified=1;
   while (valid_move==1){
        beginning:
        for (int r=0;r<num_rows;r++){
            for (int c=0;c<num_cols;c++){
                if (board[r][c]=='-'){
                    if ((is_four_in_a_row(num_rows, num_cols, r,c,piece1)==1)&&(is_four_in_a_row(num_rows, num_cols, r,c,piece2)==1)){
                        return INITIAL_BOARD_NO_SOLUTION;
                    }


                    if (is_four_in_a_row(num_rows, num_cols, r,c,piece1)==1){
                        
                        //printf("ROW: %i and COL: %i and PIECE: %c\n", r, c, piece2);

                        set_piece(r,c,piece2);
                        counter_o++;

                        modified=1;
                        //print_board(num_rows,num_cols);
                       // printf("\n");

                        //printf("%i\n", *num_o);

                        goto beginning;


                    }

                    //Add a method to remove -

                    else if (is_four_in_a_row(num_rows, num_cols, r,c,piece2)==1){

                        //printf("ROW: %i and COL: %i and PIECE: %c\n", r, c, piece1);

                        set_piece(r,c,piece1);
                        counter_x++;

                        modified=1;
                        //print_board(num_rows,num_cols);

                        //printf("\n");

                        //printf("%i\n", *num_x);

                        goto beginning;
                    }

                    else{
                       // printf("IN THE ELSE STATEMENT");
                        set_piece(r,c,piece3);
                        modified=0;
                    }

                } 
                else{
                    continue;
                }
                
            }
        }

       
        if (modified==0){

            return HEURISTICS_FAILED;

        } else{
            
            valid_move=0;
        }
    }

    // print_board(num_rows,num_cols);

    *num_x = counter_x;
    *num_o = counter_o;
    //printf("%i\n", *num_x);
    //printf("%i\n", *num_o);
    return FOUND_SOLUTION;
}


char* generate_medium(const char *final_state, int num_rows, int num_cols) {
   
    initialize_board(final_state, num_rows, num_cols);

    print_board(num_rows, num_cols);

    char *tempBoard = (char *)malloc((num_rows * num_cols + 1) * sizeof(char));
    if (tempBoard == NULL) {
        return NULL; 
    }

    int z = 0;
    for (int x = 0; x < num_rows; x++) {
        for (int y = 0; y < num_cols; y++) {
            tempBoard[z] = board[x][y];
            z++;
        }
    }

    char *modify = (char *)malloc((num_rows * num_cols + 1) * sizeof(char));
    if (modify == NULL) {
        free(tempBoard);  
        return NULL;
    }

    int i = 0;
    for (int r = 0; r < num_rows; r++) {
        for (int c = 0; c < num_cols; c++) {
            modify[i] = board[r][c];
            printf("%c", modify[i]); 
            i++;
        }
        printf("\n");
    }

    modify[num_rows * num_cols] = '\0';

    for (int r = 0; r < num_rows; r++) {
        for (int c = 0; c < num_cols; c++) {
            char currentPiece = board[r][c];

            printf("CURRENT PIECE: %c\n", currentPiece);

            set_piece(r, c, '-');
            tempBoard[r * num_cols + c] = '-'; 

            int num_x = count_x(num_rows, num_cols);
            int num_o = count_o(num_rows, num_cols);
            
            
            //int num_x = count_x(num_rows, num_cols);

            if (solve(tempBoard, num_rows, num_cols, &num_x, &num_o) == 1) {
                modify[r * num_cols + c] = '-';  
                printf("PUTTING A DASH: %c \n", modify[r * num_cols + c]);
            } else {
                set_piece(r, c, currentPiece);  
                tempBoard[r * num_cols + c] = currentPiece; 
                modify[r * num_cols + c] = currentPiece;  
                printf("NOT CHANGING: %c \n", modify[r * num_cols + c]);
            }
        }
    }

    free(tempBoard);  
    return modify;  
}














