#include <stddef.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "../matrix/matrix.h"

#define MAT_SIZE 512
#define BEST_OF_N 8

// This function is not good but at least solves the issue to have a quick test of the program
float random_float() {
    return (float) rand() / (float) RAND_MAX;
}

// First optimization is to run the compilation with -O2 to enable level 1 compilation optimizations
// From O3 and above it does not make any improvement in times
int main(void) {
    // allocate memory for the 3 matrices
    float *mat_data = malloc(MAT_SIZE * MAT_SIZE * 3 * sizeof(*mat_data));
    Mat a = {
        .rows = MAT_SIZE,
        .cols = MAT_SIZE,
        .data = mat_data
    };
    Mat b = {
        .rows = MAT_SIZE,
        .cols = MAT_SIZE,
        .data = mat_data + MAT_SIZE * MAT_SIZE
    };
    Mat c = {
        .rows = MAT_SIZE,
        .cols = MAT_SIZE,
        .data = mat_data + 2 * MAT_SIZE * MAT_SIZE
    };
    mat_fn(a, random_float);
    mat_fn(b, random_float);

    uint64_t fastest_ns = UINT64_MAX;
    for (size_t i = 0; i < BEST_OF_N; i++) {
        uint64_t start_ns = clock_gettime_nsec_np(CLOCK_MONOTONIC);
        mat_multiply(c, a, b);
        uint64_t dur_ns = clock_gettime_nsec_np(CLOCK_MONOTONIC) - start_ns;
        if (dur_ns < fastest_ns) {
            fastest_ns = dur_ns;
        }
    }
    double fastest_sec = fastest_ns / 1e9;

    printf("Best time: %6.3f s\n", fastest_sec);

    free(mat_data);
    return 0;
}
