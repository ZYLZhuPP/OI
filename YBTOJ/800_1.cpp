#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
const int N = 15;
const lf eps = 1e-8;

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline IO& operator >> (double &x) {
        double p(1); x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = x * 10 + (c ^ 48), c = gc();
        if (!(c ^ 46)) while (isdigit(c = gc())) x += (c ^ 48) * (p /= 10);
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n;
lf a[N][N], A[N][N], b[N], B[N];

void Gauss(int n, int m) {
    int r; double x;
    For (i, 1, n) {
        r = i;
        For (j, i + 1, n) if (fabs(a[j][i]) > fabs(a[r][i])) r = j;
        swap(a[i], a[r]);
        if (fabs(a[i][i]) < eps) continue;
        x = a[i][i];
        For (j, i, n + m) a[i][j] /= x;
        For (j, 1, n) if (j ^ i){
            x = a[j][i];
            For (k, i, n + m) a[j][k] -= a[i][k] * x;
        }
    }
}

int main() {
    io >> n;
    For (i, 1, n) io >> b[i], B[i] = b[i] * b[i], b[i] *= 2;
    For (i, 1, n) For (j, 1, n) io >> a[i][j], A[i][j] = a[i][j] * a[i][j], a[i][j] *= 2;
    For (i, 1, n) For (j, 1, n) a[i][j] -= b[j], a[i][n + 1] += A[i][j] - B[j];
    Gauss(n, 1);
    For (i, 1, n) printf("%.3lf ", a[i][n + 1]);

    return 0;
}
