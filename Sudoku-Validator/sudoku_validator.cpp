#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */

int n = 9; //n*n SUDOKU
int ar[9][9]; //SUDOKU Matrix
bool flag[11] = {false}; //Each thread validation element

typedef struct {
    int row;
    int coloumn;
} parameters;

//Runner function for row checker
void* row_checker(void* param) {
     bool mark = true;
     for(int i = 0; i < 9; i++) {
         bool row_mark[9] = {false};
         for(int j = 0; j < 9; j++) {
             row_mark[ar[i][j] - 1] = true;
         }
         for(int j = 0; j < 9; j++) {
             if(row_mark[j] == false) {
                 mark = false;
                 break;
             }
         }
         if(mark == false)
            break;
     }
     flag[0] = mark;
     pthread_exit(NULL);
}


//Runner function for coloumn checker
void* coloumn_checker(void* param) {
     bool mark = true;
     for(int i = 0; i < 9; i++) {
         bool coloumn_mark[9] = {false};
         for(int j = 0; j < 9; j++) {
             coloumn_mark[ar[j][i] - 1] = true;
         }
         for(int j = 0; j < 9; j++) {
             if(coloumn_mark[j] == false) {
                 mark = false;
                 break;
             }
         }
         if(mark == false)
            break;
     }
     flag[1] = mark;
     pthread_exit(NULL);
}

//Runner function for grid checker
void* grid_checker(void* param) {
    parameters* arg = (parameters*)param;
    bool mark = true;
    bool grid_mark[9] = {false};
    int r = arg->row;
    int c = arg->coloumn;

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            grid_mark[ar[r + i][r + j] - 1] = true;

    for(int i = 0; i < 9; i++)
        if(grid_mark[i] == false) {
            mark = false;
            break;
        }

    flag[r + c/3 + 2] = mark;
    pthread_exit(NULL);
}

//Driver function
int main() {
    bool mark = true; // Element to validate Sudoku
    printf("Enter SUDOKU elements row-wise : \n");    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &ar[j][i]);
    
    pthread_t ptid[11]; // Threads : 11

    pthread_create(&ptid[0], NULL, row_checker, NULL);
    pthread_create(&ptid[1], NULL, coloumn_checker, NULL);
    pthread_join(ptid[0], NULL);
    pthread_join(ptid[1], NULL);

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            parameters* data = (parameters*) malloc(sizeof(parameters));
            data->row = 3*i;
            data->coloumn = 3*j;
            pthread_create(&ptid[3*i + j + 2], NULL, grid_checker, data);
            pthread_join(ptid[3*i + j + 2], NULL);
        }
    }
    for(int i = 0; i < 11; i++) {
        if(flag[i] == false) {
            mark = false;
            break;
        }
    }
    if(mark == true)
        printf("SUDOKU puzzle is valid!\n");
    else
        printf("SUDOKU puzzle is invalid!\n");
}