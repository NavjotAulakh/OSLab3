/**
 * Name: Sodoku Solver (sodoku.c)
 * Members: Navjot Aulakh (100488741)
 * Description: Sudoku puzzle solver for 9x9 Grid using threads.
 * Date: March 9, 2018
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/**
 * Structure that holds the parameters passed to a thread.
 * This specifies where the thread should start verifying.
 */
typedef struct 
{
    // The starting row.
    int row;
    // The starting column.
    int col;
    // The pointer to the board.
    int (* board)[9];
} parameters;

// Prototype for the walk_rows function.
void * check_rows(void * params);

// Prototype for the walk_cols function.
void * check_cols(void * params);

// Prototype for 3x3 square function.
void * check_square(void * params);

int main(void) 
{
    // Initialize variables
    int  i=0,n=0;
    
    // Initialize the file pointer for reading
    FILE *file;
    file = fopen("puzzle.txt", "r");
    int board[9][9];
    // Inputs data from file into 2d array
    for(i = 0; i < 9; i++) {
        for(n = 0; n < 9; n++) {
            char s[] = "0";
            fscanf(file, " %c", &s[0]);
            board[i][n] = atoi(s);
        }
    }
    // Prints the 2d array
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            printf("%d  ",board[i][j]);
        }
        printf("\n");
    };
    fclose(file);
    
    // Create the parameters for checking the columns and rows
    parameters * param0 = (parameters *) malloc(sizeof(parameters));
    param0->row = 0;
    param0->col = 0;
    param0->board = (int(*)[9])board;
    
    // Create the 9 parameters for checking the 3x3 squares
    parameters * param1 = (parameters *) malloc(sizeof(parameters));
    param1->row = 0;
    param1->col = 0;
    param1->board = (int(*)[9])board;
    
    parameters * param2 = (parameters *) malloc(sizeof(parameters));
    param2->row = 0;
    param2->col = 3;
    param2->board = (int(*)[9])board;
    
    parameters * param3 = (parameters *) malloc(sizeof(parameters));
    param3->row = 0;
    param3->col = 6;
    param3->board = (int(*)[9])board;
    
    parameters * param4 = (parameters *) malloc(sizeof(parameters));
    param4->row = 3;
    param4->col = 0;
    param4->board = (int(*)[9])board;
    
    parameters * param5 = (parameters *) malloc(sizeof(parameters));
    param5->row = 3;
    param5->col = 3;
    param5->board = (int(*)[9])board;
    
    parameters * param6 = (parameters *) malloc(sizeof(parameters));
    param6->row = 3;
    param6->col = 6;
    param6->board = (int(*)[9])board;
    
    parameters * param7 = (parameters *) malloc(sizeof(parameters));
    param7->row = 6;
    param7->col = 0;
    param7->board = (int(*)[9])board;
    
    parameters * param8 = (parameters *) malloc(sizeof(parameters));
    param8->row = 6;
    param8->col = 3;
    param8->board = (int(*)[9])board;
    
    parameters * param9 = (parameters *) malloc(sizeof(parameters));
    param9->row = 6;
    param9->col = 6;
    param9->board = (int(*)[9])board;
    
    // Create 11 threads for processing the checks
    pthread_t thread_rows, thread_cols, thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8, thread9;
    
    // Create void pointer variables for checking the return from each thread
    void * board_rows;
    void * board_cols;
    void * square1;
    void * square2;
    void * square3;
    void * square4;
    void * square5;
    void * square6;
    void * square7;
    void * square8;
    void * square9;
    
    // Initilize the 11 threads for processing the sodoku
    pthread_create(&thread_rows, NULL, check_rows, (void *) param0);
    pthread_create(&thread_cols, NULL, check_cols, (void *) param0);
    pthread_create(&thread1, NULL, check_square, (void *) param1);
    pthread_create(&thread2, NULL, check_square, (void *) param2);
    pthread_create(&thread3, NULL, check_square, (void *) param3);
    pthread_create(&thread4, NULL, check_square, (void *) param4);
    pthread_create(&thread5, NULL, check_square, (void *) param5);
    pthread_create(&thread6, NULL, check_square, (void *) param6);
    pthread_create(&thread7, NULL, check_square, (void *) param7);
    pthread_create(&thread8, NULL, check_square, (void *) param8);
    pthread_create(&thread9, NULL, check_square, (void *) param9);

    // Wait for all threads to finish and join
    pthread_join(thread_rows, &board_rows);
    pthread_join(thread_cols, &board_cols);
    pthread_join(thread1, &square1);
    pthread_join(thread2, &square2);
    pthread_join(thread3, &square3);
    pthread_join(thread4, &square4);
    pthread_join(thread5, &square5);
    pthread_join(thread6, &square6);
    pthread_join(thread7, &square7);
    pthread_join(thread8, &square8);
    pthread_join(thread9, &square9);
    
    // Cast each void variable to int & Check whether the Sudoku Puzzle was solved
    if ( (int) board_rows == 1 && (int) board_cols == 1 && (int) square1 == 1 &&
         (int) square2 == 1 && (int) square3 == 1 && (int) square4 == 1 && (int) square5 == 1 &&
         (int) square6 == 1 && (int) square7 == 1 && (int) square8 == 1 && (int) square9 == 1 ) 
    {
        printf("The Sudoku Puzzle is Valid.\n");
    } else {
        printf("The Sudoku Puzzle is Invalid.\n");
    }
    
    return 0;
}

/**
 * This fucntion checks each row to see if it contains digits 1 to 9.
 * Ignores all 0s on the board
 * @param   (void *) parameters pointer
 * @return  (void *) 1 if all rows contain all digits 1 to 9 and 0 otherwise.
 */
void * check_rows(void * params) {
    parameters * data = (parameters *) params;
    int initRow = data->row;
    int initCol = data->col;
    for (int i = initRow; i < 9; ++i) {
        int row[10] = {0};
        for (int j = initCol; j < 9; ++j) {
            int val = data->board[i][j];
            if (val == 0) {
            // Ignore
                } else if (row[val] != 0) {
                    return (void *) 0;
                } else {
                    row[val] = 1;
                }
        }
    }
    return (void *) 1;
}

/**
 * This fucntion checks each coloumn to see if it contains digits 1 to 9.
 * Ignores all 0s on the board
 * @param   (void *) parameters pointer
 * @return  (void *) 1 if all rows contain all digits 1 to 9 and 0 otherwise.
 */
void * check_cols(void * params) {
    parameters * data = (parameters *) params;
    int initRow = data->row;
    int initCol = data->col;
    for (int i = initCol; i < 9; ++i) {
        int col[10] = {0};
        for (int j = initRow; j < 9; ++j) {
            int val = data->board[j][i];
            if (val == 0) { 
            // Ignore
                } else if (col[val] != 0) {
                    return (void *) 0;
                } else {
                    col[val] = 1;
                }
        }
    }
    return (void *) 1;
}

/**
 * This fucntion checks each of 3x3 (9) sqaure to see if they contain digits 1 to 9.
 * Ignores all 0s on the board
 * @param   (void *) parameters pointer
 * @return  (void *) 1 if all rows contain all digits 1 to 9 and 0 otherwise.
 */
void * check_square(void * params) {
    parameters * data = (parameters *) params;
    int initRow = data->row;
    int initCol = data->col;
    int square[10] = {0};
    for (int i = initRow; i < initRow + 3; ++i) {
        for (int j = initCol; j < initCol + 3; ++j) {
            int val = data->board[i][j];
            if (val == 0) {
            // Ignore
                } else if (square[val] != 0) {
                    return (void *) 0;
                } else {
                    square[val] = 1;
                }
        }
    }
    return (void *) 1;
}