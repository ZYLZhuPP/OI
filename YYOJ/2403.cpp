#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 4e3 + 5;

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

int n, m, a[N][N], R, S, b[N][N], c[N][N], q[N];

int main() {
    memset(b, 224, sizeof b);
    memset(c, 224, sizeof c);
    io >> n >> m;
    For (i, 1, n) For (j, 1, m) io >> a[i][j];
    io >> R >> S;
    For (i, 1, n) {
        int l = 1, r = 0;
        For (j, 1, m) {
            while (l <= r && j - q[l] >= S) l++;
            while (l <= r && a[i][q[r]] <= a[i][j]) r--;
            q[++r] = j;
            b[i][j] = a[i][q[l]];
        }
    }
    For (j, S, m) {
        int l = 1, r = 0;
        For (i, 1, n) {
            while (l <= r && i - q[l] >= R) l++;
            while (l <= r && b[q[r]][j] <= b[i][j]) r--;
            q[++r] = i;
            c[i][j] = b[q[l]][j];
        }
    }
    For (i, R, n) For (j, S, m) printf("%d%c", c[i][j], " \n"[j==m]);

    return 0;
}
