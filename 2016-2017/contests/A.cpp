

#include <vector>
#include <cstdlib>
#include <cassert>
#include <utility>
#include <string>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <bitset>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cassert>


inline int readInt();
inline int readUInt();
inline void readWord( char *s );
inline int fast_readchar(); // you may use readchar() instead of it

inline void writeInt( int x );
inline void fast_writechar( int x ); // you may use putchar() instead of it
inline void writeWord( const char *s );
inline void fast_flush();

static const int buf_size = 4096;

inline int fast_readchar() {
    static char buf[buf_size];
    static int len = 0, pos = 0;
    if (pos == len)
        pos = 0, len = fread(buf, 1, buf_size, stdin);
    if (pos == len)
        return -1;
    return buf[pos++];
}

inline int readUInt() {
    int c = fast_readchar(), x = 0;
    while (c <= 32)
        c = fast_readchar();
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = fast_readchar();
    return x;
}

inline int readInt() {
    int s = 1, c = fast_readchar();
    int x = 0;
    while (c <= 32)
        c = fast_readchar();
    if (c == '-')
        s = -1, c = fast_readchar();
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = fast_readchar();
    return x * s;
}

inline void readWord( char *s ) {
    int c = fast_readchar();
    while (c <= 32)
        c = fast_readchar();
    while (c > 32)
        *s++ = c, c = fast_readchar();
    *s = 0;
}


static int write_pos = 0;
static char write_buf[buf_size];

inline void fast_writechar( int x ) {
    if (write_pos == buf_size)
        fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
    write_buf[write_pos++] = x;
}

inline void fast_flush() {
    if (write_pos)
        fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
}

inline void writeInt( int x ) {
    if (x < 0)
        fast_writechar('-'), x = -x;

    char s[24];
    int n = 0;
    while (x || !n)
        s[n++] = '0' + x % 10, x /= 10;
    while (n--)
        fast_writechar(s[n]);
}

inline void writeLongLong( long long x ) {
    if (x < 0)
        fast_writechar('-'), x = -x;

    char s[100];
    int n = 0;
    while (x || !n)
        s[n++] = '0' + x % 10, x /= 10;
    while (n--)
        fast_writechar(s[n]);
}

inline void writeWord( const char *s ) {
    while (*s)
        fast_writechar(*s++);
}




const int MAX_SIZE = 200000;

int rev_bit[MAX_SIZE];
int bit[100];

int A[MAX_SIZE];
int B[MAX_SIZE];
int C[MAX_SIZE];

double re_A[MAX_SIZE];
double im_A[MAX_SIZE];
double re_B[MAX_SIZE];
double im_B[MAX_SIZE];
double re_C[MAX_SIZE];
double im_C[MAX_SIZE];

double w_re[MAX_SIZE];
double w_im[MAX_SIZE];

double rev_w_re[MAX_SIZE];
double rev_w_im[MAX_SIZE];

void precalc(int n, int bits) {
    bit[0] = n >> 1;

    for (int i = 1; i < bits; i++) {
        bit[i] = bit[i - 1] >> 1;
    }

    rev_bit[0] = 0;

    for (int i = 1; i < n; i++) {
        int pos = 0;

        while (bit[pos] & rev_bit[i - 1])
            pos++;

        rev_bit[i] |= bit[pos];

        for (; pos < bits; pos++) {
            rev_bit[i] |= rev_bit[i - 1] & bit[pos];
        }
    }

    double phi = 2 * M_PI / n;

    w_re[0] = 1;
    w_im[0] = 0;

    w_re[1] = cos(phi);
    w_im[1] = sin(phi);

    for (int i = 2; i < n; i++) {
        w_re[i] = w_re[i - 1] * w_re[1] - w_im[i - 1] * w_im[1];
        w_im[i] = w_im[i - 1] * w_re[1] + w_re[i - 1] * w_im[1];
    }

    rev_w_re[0] = 1;
    rev_w_im[0] = 0;

    rev_w_re[1] = cos(-phi);
    rev_w_im[1] = sin(-phi);

    for (int i = 2; i < n; i++) {
        rev_w_re[i] = rev_w_re[i - 1] * rev_w_re[1] - rev_w_im[i - 1] * rev_w_im[1];
        rev_w_im[i] = rev_w_im[i - 1] * rev_w_re[1] + rev_w_re[i - 1] * rev_w_im[1];
    }
}

void fft(int n, double *re, double *im) {
    for (int half_len = 1, len = 2, w_one = n >> 1; len <= n; half_len <<= 1, len <<= 1, w_one >>= 1) {
        for (int start = 0; start < n;) {

            int pos1 = start, pos2 = start + half_len;
            start += len;
            int root = 0;

            for (; pos2 < start; pos1++, pos2++, root += w_one) {
                double x_re = re[pos1];
                double x_im = im[pos1];
                double y_re = re[pos2];
                double y_im = im[pos2];
                double curr_w_re = w_re[root];
                double curr_w_im = w_im[root];

                double tmp = curr_w_re * y_re - curr_w_im * y_im;
                re[pos1] = x_re + tmp;
                re[pos2] = x_re - tmp;

                tmp = curr_w_re * y_im + curr_w_im * y_re;
                im[pos1] = x_im + tmp;
                im[pos2] = x_im - tmp;
            }
        }
    }
}

void rfft(int n, double *re, double *im) {
    for (int half_len = 1, len = 2, w_one = n >> 1; len <= n; half_len <<= 1, len <<= 1, w_one >>= 1) {
        for (int start = 0; start < n;) {

            int pos1 = start, pos2 = start + half_len;
            start += len;
            int root = 0;

            for (; pos2 < start; pos1++, pos2++, root += w_one) {
                double x_re = re[pos1];
                double x_im = im[pos1];
                double y_re = re[pos2];
                double y_im = im[pos2];
                double curr_w_re = rev_w_re[root];
                double curr_w_im = rev_w_im[root];

                double tmp = curr_w_re * y_re - curr_w_im * y_im;
                re[pos1] = x_re + tmp;
                re[pos2] = x_re - tmp;

                tmp = curr_w_re * y_im + curr_w_im * y_re;
                im[pos1] = x_im + tmp;
                im[pos2] = x_im - tmp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        re[i] /= n;
    }
}







int inv7[7] = {0, 1, 4, 5, 2, 3, 6};

void mul_fur_full(int n, int *a, int *b, int *dest) {
    int bits = 0;

    int tn = n;
    while (tn > 0) {
        bits++;
        tn >>= 1;
    }

    for (int i = 0; i < n; i++) {
        rev_bit[i] = 0;
    }

    precalc(n, bits);

    for (int i = 0; i < n; i++) {
        re_A[rev_bit[i]] = a[n - i - 1];
        im_A[rev_bit[i]] = 0;
    }

    for (int i = 0; i < n; i++) {
        re_B[rev_bit[i]] = b[n - i - 1];
        im_B[rev_bit[i]] = 0;
    }

    fft(n, re_A, im_A);
    fft(n, re_B, im_B);

    for (int i = 0; i < n; i++) {
        re_C[i] = re_A[rev_bit[i]] * re_B[rev_bit[i]] - im_A[rev_bit[i]] * im_B[rev_bit[i]];
        im_C[i] = re_A[rev_bit[i]] * im_B[rev_bit[i]] + im_A[rev_bit[i]] * re_B[rev_bit[i]];
    }

    rfft(n, re_C, im_C);

    for (int i = 0; i < n; i++) {
        dest[i] = (int)(re_C[n - i - 1] + 0.5) % 7;
    }
}

void mul_fur(int n, int *a, int *b, int *dest) {
    int bits = 0;

    int tn = n;
    while (tn > 0) {
        bits++;
        tn >>= 1;
    }

    for (int i = 0; i < n; i++) {
        rev_bit[i] = 0;
    }

    precalc(n, bits);

    int half_n = n >> 1;

    for (int i = 0; i < half_n; i++) {
        re_A[rev_bit[i]] = a[half_n - i - 1];
        im_A[rev_bit[i]] = 0;
    }

    for (int i = half_n; i < n; i++) {
        re_A[rev_bit[i]] = 0;
        im_A[rev_bit[i]] = 0;
    }

    for (int i = 0; i < half_n; i++) {
        re_B[rev_bit[i]] = b[half_n - i - 1];
        im_B[rev_bit[i]] = 0;
    }

    for (int i = half_n; i < n; i++) {
        re_B[rev_bit[i]] = 0;
        im_B[rev_bit[i]] = 0;
    }

    fft(n, re_A, im_A);
    fft(n, re_B, im_B);

    for (int i = 0; i < n; i++) {
        re_C[i] = re_A[rev_bit[i]] * re_B[rev_bit[i]] - im_A[rev_bit[i]] * im_B[rev_bit[i]];
        im_C[i] = re_A[rev_bit[i]] * im_B[rev_bit[i]] + im_A[rev_bit[i]] * re_B[rev_bit[i]];
    }

    rfft(n, re_C, im_C);

    for (int i = 0; i < n; i++) {
        dest[i] = (int)(re_C[n - i - 1] + 0.5) % 7;
    }
}

void mul_sq(int n, int *a, int *b, int *dest) {
    if (n == 2) {
        dest[0] = (a[1] * b[0]) % 7;
        return;
    }

    int half_n = n >> 1;

    for (int i = 0; i < half_n; i++) {
        dest[i] = 0;

        for (int j = 0; j < half_n; j++) {
            dest[i] += b[j] * a[half_n + i - j];
        }

        dest[i] %= 7;
    }
}

int mem[MAX_SIZE];
int tmp[MAX_SIZE];
int tmp1[MAX_SIZE];

void div_multiply(int n, int *a, int *b, int *dest) {
    if (n <= 512) {
        mul_sq(n, a, b, dest);
        return;
    }

    int half_n = n >> 1;

    for (int i = 0; i < half_n; i++) {
        tmp[i] = b[i];
    }

    for (int i = half_n; i < n; i++) {
        tmp[i] = 0;
    }

    mul_fur(n << 1, a, tmp, tmp1);

    for (int i = 0; i < half_n; i++) {
        dest[i] = tmp1[half_n + 1 + i];
    }
}

void div(int n, int *a, int *b, int *dest) {
    if (n == 1) {
        dest[0] = a[0] * inv7[b[0]] % 7;
        return;
    }

    int half_n = n >> 1;

    div(half_n, a, b, dest);

    div_multiply(n, b, dest, mem + half_n);

    for (int i = half_n; i < n; i++) {
        a[i] -= mem[i];

        if (a[i] < 0)
            a[i] += 7;
    }

    div(half_n, a + half_n, b, dest + half_n);
}

int copy_a[MAX_SIZE];
int copy_b[MAX_SIZE];
int copy_c[MAX_SIZE];
int a[MAX_SIZE];
int b[MAX_SIZE];
int c[MAX_SIZE];
int d[MAX_SIZE];


int main() {
    freopen("divpoly.in", "r", stdin);
    freopen("divpoly.out", "w", stdout);

    int deg_a = readUInt();

    for (int i = 0; i <= deg_a; i++) {
        a[i] = readUInt();
    }

    int deg_b = readUInt();

    for (int i = 0; i <= deg_b; i++) {
        b[i] = readUInt();
    }

    if (deg_a < deg_b) {
        writeInt(0);
        fast_writechar(' ');
        writeInt(0);
        fast_writechar('\n');
        writeInt(deg_a);
        fast_writechar(' ');
        for (int i = 0; i <= deg_a; i++) {
            writeInt(a[i]);
            fast_writechar(' ');
        }
        fast_writechar('\n');
    }

    else {
        int N = 1;
        int tda = deg_a + 1;

        while (tda > 0) {
            N <<= 1;
            tda >>= 1;
        }

        for (int i = 0; i <= deg_a; i++) {
            copy_a[i + N - deg_a - 1] = a[i];
        }

        for (int i = 0; i <= deg_b; i++) {
            copy_b[i + N - deg_b - 1] = b[i];
        }


        int n = 1;
        int deg_c = deg_a - deg_b;
        int tdc = deg_c + 1;

        while (tdc > 0) {
            n <<= 1;
            tdc >>= 1;
        }

        div(n, a, b, c);

        writeInt(deg_c);
        fast_writechar(' ');
        for (int i = 0; i <= deg_c; i++) {
            writeInt(c[i]);
            fast_writechar(' ');
        }
        fast_writechar('\n');

        for (int i = 0; i <= deg_c; i++) {
            copy_c[i + N - deg_c - 1] = c[i];
        }

        mul_fur_full(N, copy_b, copy_c, d);

        for (int i = 0; i < N; i++) {
            copy_a[i] -= d[i];

            if (copy_a[i] < 0) {
                copy_a[i] += 7;
            }
        }

        int k = 0;

        while (copy_a[k] == 0 && k < N) {
            k++;
        }

        if (k == N) {
            writeInt(0);
            fast_writechar(' ');
            writeInt(0);
            fast_writechar('\n');
        }

        else {
            writeInt(N - k - 1);
            fast_writechar(' ');
            for (; k < N; k++) {
                writeInt(copy_a[k]);
                fast_writechar(' ');
            }
            fast_writechar('\n');
        }
    }

    fast_flush();

    return 0;
}
