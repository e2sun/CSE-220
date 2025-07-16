#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "hw1.h"

int main(int argc, char **argv) {
    assert(argc == 4);
    initialize_board(argv[3], (int)strtoul(argv[1], NULL, 10), (int)strtoul(argv[2], NULL, 10));

    int game_finished=0;

    while (game_finished==0){
        int rows = (int)strtoul(argv[1], NULL, 10);
        int cols = (int)strtoul(argv[2], NULL, 10);

        print_board(rows, cols);

        printf("Choose a piece (x or o) or q to quit: ");
        char piece;
        scanf(" %c", &piece);
       

        if (piece=='q'){
            break;
        }

        int valid_piece=1;

        if (piece!='x' && piece!='o') {
            valid_piece = 0;
        }

        while (valid_piece==0){
            printf("Invalid choice. Choose a piece (x or o) or q to quit: ");
            scanf(" %c", &piece);
            if (piece=='q'){
                break;
            }
            if (piece=='x'|| piece=='o') {
                valid_piece=1;
            }
        }

        printf("Choose a row (0-%i): ", rows-1);
        int row;
        scanf(" %i", &row);

        int valid_row=1;

        if (row<0||row>=rows) {
            valid_row = 0;
        }

        while (valid_row==0){
            printf("Invalid choice. Choose a row (0-%i): ",rows-1);
            scanf(" %i", &row);
            if (row>=0&&row<rows) {
                valid_row=1;
            }
        }

        printf("Choose a column (0-%i): ", cols-1);
        int col;
        scanf(" %i", &col);

        int valid_col=0;

        while (valid_col == 0) {
            if (col >= 0 && col < cols) {  
                if (is_space_occupied(row, col) == 0) {
                    set_piece(row,col,piece);
                    if (is_four_in_a_row(rows, cols, row, col, piece) == 1) {
                        printf("Invalid choice. You have created 4-in-a-row.\n");
                        break;
                    } else{
                        valid_col=1;
                    }    
                }
                else if (is_space_occupied(row,col)==1) {
                    printf("Invalid choice. That space is already occupied.\n");
                    break;
                }
            }
            else if (col<0||col>=cols) {
                printf("Invalid choice. Choose a column (0-%i): ",cols-1);
                scanf(" %i", &col);  
            }

        }
        int count=0;
        for (int i=0;i<rows;i++){
            for (int y=0;y<cols;y++){
                if (is_space_occupied(i,y)==0){
                    count++;
                }
            } 
        }
        if (count==0){
            printf("Congratulations, you have filled the board with no 4-in-a-rows!\n");
            print_board(rows,cols);
            printf("\n");
            game_finished=1;
        }
        
    
    }
    
    return 0;
}
