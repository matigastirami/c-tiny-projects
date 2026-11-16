#ifndef _MAT_H
#define _MAT_H

#include <stdint.h>

typedef struct {
    uint32_t rows, cols; // 32 bits is more than enough for the size
    float *data;
} Mat;

void mat_fn(Mat m, float fn(void));
void print_matrix(Mat m);
int can_mat_mul(Mat a, Mat b);
int mat_multiply(Mat res, Mat a, Mat b);

#endif
