#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5, M = 1e5 + 5;

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
    inline bool operator ~ () const { return ~c; }
} io;

int T, n, m, a[N][N], b[N][N], c[3], d[3], x[3], y[3];
char op[M];

int main() {
    io >> T;
    while (T--) {
        io >> n >> m;
        For (i, 0, 2) c[i] = i, d[i] = 0;
        For (i, 1, n) For (j, 1, n) io >> a[i][j];
        scanf("%s", op + 1);
        For (i, 1, m) {
            if (op[i] == 'R') d[1]++;
            else if (op[i] == 'L') d[1]--;
            else if (op[i] == 'D') d[0]++;
            else if (op[i] == 'U') d[0]--;
            else if (op[i] == 'I') swap(c[1], c[2]), swap(d[1], d[2]);
            else if (op[i] == 'C') swap(c[0], c[2]), swap(d[0], d[2]);
        }
        For (i, 1, n) For (j, 1, n) {
            x[0] = i, x[1] = j, x[2] = a[i][j];
            For (k, 0, 2) y[k] = ((x[c[k]] + d[k] - 1) % n + n) % n + 1;
            b[y[0]][y[1]] = y[2];
        }
        For (i, 1, n) For (j, 1, n) printf("%d%c", b[i][j], " \n"[j==n]);
        puts("");
    }

    return 0;
}
