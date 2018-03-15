//
//  main.c
//  dtw
//
//  Created by 侯山 on 2018/3/14.
//  Copyright © 2018年 侯山. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "dtw.h"
#include <time.h>

double** matrix_init(int row, int col)
{
    double** ptr = (double**)malloc(row * sizeof(double*));
    for(int row_index = 0; row_index < row; ++row_index)
    {
        ptr[row_index] = (double*)malloc(col * sizeof(double));
    }
    return ptr;
}

int main(int argc, char** argv)
{
    if(argc != 4)
    {
        printf("Usage: %s m1_row_number m2_row_number shared_col_number\n", argv[0]);
        return 0;
    }
    
    int m1_rows = atoi(argv[1]);
    int m2_rows = atoi(argv[2]);
    int shared_cols = atoi(argv[3]);
    
    //matrices initialisation
    double** m1 = matrix_init(m1_rows, shared_cols);
    double** m2 = matrix_init(m2_rows, shared_cols);
    double** md = matrix_init(m1_rows, m2_rows);
    
    srand((unsigned char)time(NULL));
    
    printf("\nmatrix1: row = %d, col = %d\n", m1_rows, shared_cols);
    //Fill m1 with random numbers 0.00 -- 9.99
    for(int row = 0; row < m1_rows; ++row)
    {
        for(int col = 0; col < shared_cols; ++col)
        {
            m1[row][col] = (double)(rand() % 1000) / 100;
            printf("%f\t", m1[row][col]);
        }
        printf("\n");
    }
    
    printf("\nmatrix2: row = %d, col = %d\n", m2_rows, shared_cols);
    //Fill m2 with random numbers 0.00 -- 99.99
    for(int row = 0; row < m2_rows; ++row)
    {
        for(int col = 0; col < shared_cols; ++col)
        {
            m2[row][col] = (double)(rand() % 10000) / 100;
            printf("%f\t", m2[row][col]);
        }
        printf("\n");
    }
    
    
    gen_dist_mat(m1, m1_rows, shared_cols,
                 m2, m2_rows, shared_cols,
                 md);
    
    printf("\nDistance matrix:\n");
    for(int row = 0; row < m1_rows; ++row)
    {
        for(int col = 0; col < m2_rows; ++col)
        {
            printf("%f\t", md[row][col]);
        }
        printf("\n");
    }
    
    double similarity = dtw(md, m1_rows, m2_rows);
    
    printf("\nDTW matrix:\n");
    for(int row = 0; row < m1_rows; ++row)
    {
        for(int col = 0; col < m2_rows; ++col)
        {
            printf("%f\t", md[row][col]);
        }
        printf("\n");
    }
    
    printf("\nsimilatiry = %f\n", similarity);
    
    //Free memory? I dont care.
    return 0;
}
