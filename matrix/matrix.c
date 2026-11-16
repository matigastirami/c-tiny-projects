#include "matrix.h"
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

/**
 * Generic to initialize a matrix with whichever value the fn() generates
 * as long as it returns a float
 */
void mat_fn(Mat m, float fn(void)) {
    for (size_t i = 0; i < m.rows * m.cols; i++) {
        m.data[i] = fn();
    }
}

/**
 * Prints a matrix in the terminal
 */
void print_matrix(Mat m) {
    for (size_t i = 0; i < m.rows; i++) {
        for (size_t j = 0; j < m.cols; j++) {
            printf(" %f ", m.data[i * m.cols + j]);
        }
        printf("\n");
    }
}

/**
 * Detrmines if 2 matrices can be multiplied
 */
int can_mat_mul(Mat a, Mat b) {
    return a.cols == b.rows;
}

/**
 * It multiplies 2 matrices
 * Params:
 * @a first matrix
 * @b second matrix
 * @res result matrix in which result will be returned
 */
int mat_multiply(Mat res, Mat a, Mat b) { // pass by value instead of ref as Mat is quite small
    if (!can_mat_mul(a, b)) {
        return -1;
    }

    memset(res.data, 0, res.rows * res.cols * sizeof(*res.data));

    for (uint32_t i = 0; i < a.cols; i++) {
        // Flipping k and j loops is very good for memory jumps and caching and in the case of this computer
        // the program got ~3.2x faster than having j then k loop
        for (uint32_t k = 0; k < a.cols; k++) {
            for (uint32_t j = 0; j < b.rows; j++) {
                res.data[i * res.cols + j] += a.data[i * a.cols + k] * b.data[k * b.cols + j];
            }
        }
    }
    return 0;
}
