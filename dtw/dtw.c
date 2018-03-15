//m1 --- 100 cols x 231 rows, template matrix
//m2 --- 100 cols x 114 rows, test matrix
//int m1_cols = 100; int m1_rows = 231;
//int m2_cols = 100; int m2_rows = 114;

#include "dtw.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>





void gen_dist_mat(double** templ_mat, int templ_row, int templ_col,
		  double** test_mat, int test_row, int test_col,
		  double** dist_mat)
{
    int m; int n; int i;
    for (n=0; n<templ_row; n++)
    {
        for (m=0; m<test_row; m++)
        {
            for (i=0;i<templ_col;i++)
            {
                dist_mat[n][m] += fabs(templ_mat[n][i]-test_mat[m][i]);
            }
        }
    }
    
}


/*
  DTW
 */
double dtw(double** dist_mat, int row, int col)
{
  if(row == 0 || col == 0)
    return 0.0;
  
    double simi_D;
    int i,j;
    double D1=0,D_min;
    //D[0][0]=dist_mat[0][0];
    for (j=0; j<col; j++)
    {
        for (i=0; i<row; i++)
        {
            if (i>0)
            {
                if(j==0)
                {
                    D_min=dist_mat[i-1][j];
                    dist_mat[i][j]+=D_min;
                }
                else
                {
                    D1=MIN(dist_mat[i-1][j],dist_mat[i][j-1]);
                    D_min=MIN(D1,dist_mat[i-1][j-1]);
                    dist_mat[i][j]+=D_min;
                }
            }
            else if (j==0)
                 {
                     D_min=0;
                     dist_mat[i][j]+=D_min;
                 }
            else
            {
                D_min=dist_mat[i][j-1];
                dist_mat[i][j]+=D_min;
            }
        }
    }

    simi_D = dist_mat[row - 1][col - 1];

    return simi_D;
}
