#include "stdio.h"
#include "stdlib.h"
#include <time.h>
#include "assert.h"
#include "math.h"

/**********************************************************************
    Debug functions
***********************************************************************/
void pretty_print_matrix(int **matrix, int length, char *name) {
    printf("\n%s", name);
    for (int i = 0; i < length; i++) {
        printf("\n");
        for (int j  = 0; j < length; j++ ) {
            printf("\t%d", matrix[i][j]);
        }
    }
    printf("\n\n");
}

void verify_matrix(int **c, int **d, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            assert(c[i][j] == d[i][j]);
        }
    }
    printf("\nVerification successful");
}

/**********************************************************************
    MMM routines
***********************************************************************/
void program0(int n, int **a, int **b, int **c) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}


void program1(int n, int NB, int **a, int **b, int **c) {
    int MU = 2, NU = 2, KU = 1;

    for (int i = 0; i < n; i+=NB) {
        for (int j = 0; j < n; j += NB) {
            for (int k = 0; k < n; k += NB) {
                // mini-MMM loop nest (i0, j0, k0)

                for(int i0= i; i0 < (i + NB); i0 += MU) {
                    for (int j0 = j; j0 < (j + NB); j0 += NU) {
                        for (int k0 = k; k0 < (k + NB); k0 += KU) {

                            // micro-MMM loop nest (k, i, j)
                            for(int k00 = k0; k00 < (k0 + KU); k00++) {
                                int a_t0 = a[i0][k00], a_t1 = a[i0 + 1][k00];
                                int b_t0 = b[k00][j0], b_t1 = b[k00][j0 + 1];

                                c[i0][j0] += a_t0 * b_t0;
                                c[i0][j0 + 1] += a_t0 * b_t1;
                                c[i0 + 1][j0] += a_t1 * b_t0;
                                c[i0 + 1][j0 + 1] += a_t1 * b_t1;
                            }
                        }
                    }
                }
            }
        }
    }
}

void program2(int n, int NB, int **a, int **b, int **c) {
    int MU = 2, NU = 2, KU = 2;

    for (int i =0; i < n; i+=NB) {
        for (int j = 0; j < n; j += NB) {
            for (int k = 0; k < n; k += NB) {
                // mini-MMM loop nest (i0, j0, k0)

                for(int i0 = i; i0 < (i + NB); i0 += MU) {
                    for (int j0 = j; j0 < (j + NB); j0 += NU) {
                        for (int k0 = k; k0 < (k + NB); k0 += KU) {

                            int a_t0 = a[i0][k0], a_t1 = a[i0 + 1][k0];
                            int b_t0 = b[k0][j0], b_t1 = b[k0][j0 + 1];

                            int a_t0k = a[i0][k0 + 1], a_t1k = a[i0 + 1][k0 + 1];
                            int b_t0k = b[k0 + 1][j0], b_t1k = b[k0 + 1][j0 + 1];

                            int x11 = a_t0 * b_t0, x12 = a_t0k * b_t0k;
                            int x21 = a_t0 * b_t1, x22 = a_t0k * b_t1k;
                            int x31 =  a_t1 * b_t0, x32 = a_t1k * b_t0k;
                            int x41 =  a_t1 * b_t1, x42 = a_t1k * b_t1k;

                            c[i0][j0] += x11 + x12;
                            c[i0][j0 + 1] += x21 + x22;
                            c[i0 + 1][j0] += x31 + x32;
                            c[i0 + 1][j0 + 1] += x41 + x42;

                        }
                    }
                }
            }
        }
    }
}

void program3(int n, int NB, int **a, int **b, int **c) {
    int MU = 2, NU = 2, KU = 4;

    for (int i =0; i < n; i+=NB) {
        for (int j = 0; j < n; j += NB) {
            for (int k = 0; k < n; k += NB) {
                // mini-MMM loop nest (i0, j0, k0)

                for(int i0=i; i0<(i + NB); i0+=MU) {
                    for (int j0 = j; j0 < (j + NB); j0 += NU) {
                        for (int k0 = k; k0 < (k + NB); k0 += KU) {

                            int a_t0 = a[i0][k0], a_t1 = a[i0 + 1][k0];
                            int b_t0 = b[k0][j0], b_t1 = b[k0][j0 + 1];

                            int a_t0k = a[i0][k0 + 1], a_t1k = a[i0 + 1][k0 + 1];
                            int b_t0k = b[k0 + 1][j0], b_t1k = b[k0 + 1][j0 + 1];

                            int a_t0k2 = a[i0][k0 + 2], a_t1k2 = a[i0 + 1][k0 + 2];
                            int b_t0k2 = b[k0 + 2][j0], b_t1k2 = b[k0 + 2][j0 + 1];

                            int a_t0k3 = a[i0][k0 + 3], a_t1k3 = a[i0 + 1][k0 + 3];
                            int b_t0k3 = b[k0 + 3][j0], b_t1k3 = b[k0 + 3][j0 + 1];

                            int x11 = a_t0 * b_t0, x12 = a_t0k * b_t0k, x13= a_t0k2 * b_t0k2, x14= a_t0k3 * b_t0k3;
                            int x21 = a_t0 * b_t1, x22 = a_t0k * b_t1k, x23 = a_t0k2 * b_t1k2, x24 = a_t0k3 * b_t1k3;
                            int x31 =  a_t1 * b_t0, x32 = a_t1k * b_t0k, x33 = a_t1k2 * b_t0k2, x34 = a_t1k3 * b_t0k3;
                            int x41 =  a_t1 * b_t1, x42 = a_t1k * b_t1k, x43 = a_t1k2 * b_t1k2,  x44 = a_t1k3 * b_t1k3;

                            c[i0][j0] += x11 + x12 + x13 + x14;
                            c[i0][j0 + 1] += x21 + x22 + x23 + x24;
                            c[i0 + 1][j0] += x31 + x32 + x33 + x34;
                            c[i0 + 1][j0 + 1] += x41 + x42 + x43 + x44;

                        }
                    }
                }
            }
        }
    }
}


/**********************************************************************
    Benchmarking and Parameter tuning
***********************************************************************/
void init(int n, int **a, int **b, int **c, int **d) {
    for (int i = 0; i < n; i ++) {
        a[i] = (int *) malloc(n * sizeof(int));
        b[i] = (int *) malloc(n * sizeof(int));
        c[i] = (int *) malloc(n * sizeof(int));
        if (d != NULL)
            d[i] = (int *) malloc(n * sizeof(int));
    }

    // initialize arrays
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j ++) {
            a[i][j] = (rand() % 100) + 1;
            b[i][j] = (rand() % 100) + 1;
            c[i][j] = 0;

            if (d != NULL)
                d[i][j] = 0;
        }
    }
}

int parameter_turning(int n, int iter_ctr) {
    // Parameter tunning Nb

    int **a = malloc(n * sizeof(int *));
    int **b = malloc(n * sizeof(int *));
    int **c = malloc(n * sizeof(int *));

//    int **d = malloc(n * sizeof (int *));

    init(n, a, b, c, NULL);

    FILE *fptr;
    fptr = fopen("NB-gflops-p3.txt", "a");

    if (fptr == NULL)
        return -1;

    // remove
//    program0(n, a, b, d);


    for (int k = 3; k < 7; k++) {
        int NB = (int) pow(2, k);
        double exec_time = 0.0;
        printf("\n NB: %d \n", NB);

        for (int ctr = 0; ctr < iter_ctr; ctr ++) {
            // Set C = 0 every iteration
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j ++) {
                    c[i][j] = 0;
//                    d[i][j] = 0;
                }
            }

            struct timespec begin, end;
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
            program3(n, NB, a, b, c);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

            // remove
//            verify_matrix(c, d, n);
            exec_time +=  ((double)end.tv_sec + 1.0e-9*end.tv_nsec) - ((double)begin.tv_sec + 1.0e-9*begin.tv_nsec);
        }

        double gflops = ((2 * pow(n, 3)) / (exec_time / iter_ctr)) * pow(10, -9);
        fprintf(fptr, "\nNB: %d, gflops: %f\n", NB, gflops);
        printf("\nNB: %d, gflops: %f\n", NB, gflops);

    }

    fclose(fptr);

    // free the arrays
    free(a);
    free(b);
    free(c);
    return 0;
}


int benchmark_matrix_mul(int NB, int iter_ctr) {

    // Benchmarking the entire mat mul
    FILE *fptr;
    fptr = fopen("Final-performance.txt", "a");

    for (int n = 32; n <= 4096; n += n) {
        int **a = malloc(n * sizeof(int *));
        int **b = malloc(n * sizeof(int *));
        int **c = malloc(n * sizeof(int *));

        init(n, a, b, c, NULL);

        double exec_time = 0.0;
        for (int ctr = 0; ctr < iter_ctr; ctr ++) {
            // Set C = 0 every iteration
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j ++) {
                    c[i][j] = 0;
                }
            }

            struct timespec begin, end;
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
            program3(n, NB, a, b, c);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

            exec_time +=  ((double)end.tv_sec + 1.0e-9*end.tv_nsec) - ((double)begin.tv_sec + 1.0e-9*begin.tv_nsec);
        }

        double gflops = ((2 * pow(n, 3)) / (exec_time / iter_ctr)) * pow(10, -9);

        fprintf(fptr, "\nN: %d, gflops: %f\n", n, gflops);
        printf("\nN: %d, gflops: %f\n", n, gflops);
    }
    return 0;
}

int main() {

//    parameter_turning(2048, 10);
    benchmark_matrix_mul(16, 10);

}



