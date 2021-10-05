
void program0(int n, int a[n][n], int b[n][n], int c[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}


void program1(int n, int NB, int a[n][n], int b[n][n], int c[n][n]) {
    int MU = 2, NU = 2, KU = 1;

    for (int i =0; i < n; i+=NB) {
        for (int j = 0; j < n; j += NB) {
            for (int k = 0; k < n; k += NB) {
                // mini-MMM loop nest (i0, j0, k0)

                for(int i0=i; i0<(i + NB); i0+=MU) {
                    for (int j0 = j; j0 < (j + NB); j0 += NU) {
                        for (int k0 = k; k0 < (k + NB); k0 += KU) {

                            // micro-MMM loop nest (k, i, j
                            for(int k00=k0; k00 < (k0 + KU); k00++) {
                                int a_t0 = a[i0][k00], a_t1 = a[i0 + 1][k00];
                                int b_t0 = b[k00][j0], b_t1 = b[k00][j0 + 1];

                                c[i0][j0] += a_t0 * b_t0;
                                c[i0][j0 + 1] += a_t0 * b_t1;
                                c[i0 + 1][j0] += a_t1 * b_t0;
                                c[i0 + 1][j0 + 1] += a_t1 * b_t1;
                                for(int i00=i0; i00 < (i0 + MU); i00++) {
                                    for(int j00=j0; j00 < (j0 + NU); j00++) {
                                        c[i00][j00] += a[i00][k00]*b[k00][j00];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void program2(int n, int NB, int a[n][n], int b[n][n], int c[n][n]) {
    int MU = 2, NU = 2, KU = 2;

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

                            int x11 = a_t0 * b_t0, x12 = a_t0k * b_t0k;
                            int x21 = a_t0 * b_t1, x22 = a_t0k * b_t1k;
                            int x31 =  a_t1 * b_t0, x32 = a_t1k * b_t0k;
                            int x41 =  a_t1 * b_t1, x42 = a_t1k * b_t1k;

                            c[i0][j0] += x11 + x12;
                            c[i0][j0 + 1] += x21 + x22;
                            c[i0 + 1][j0] += x31 + x32;
                            c[i0 + 1][j0 + 1] += x41 * x42;

                        }
                    }
                }
            }
        }
    }
}

void program3(int n, int NB, int a[n][n], int b[n][n], int c[n][n]) {
    int MU = 2, NU = 2, KU = 2;

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
                            c[i0 + 1][j0 + 1] += x41 * x42 + x43 + x44;

                        }
                    }
                }
            }
        }
    }
}




