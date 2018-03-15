//
//  dtw.h
//  dtw
//
//  Created by 侯山 on 2018/3/14.
//  Copyright © 2018年 侯山. All rights reserved.
//

#ifndef dtw_h
#define dtw_h
#define MIN(x,y)	((x)<(y)?(x):(y))

void gen_dist_mat(double** templ_mat, int templ_row, int templ_col,
                  double** test_mat, int test_row, int test_col,
                  double** dist_mat);

double dtw(double** dist_mat, int row, int col);



#endif /* dtw_h */
