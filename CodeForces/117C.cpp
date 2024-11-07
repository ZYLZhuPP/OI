#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e3 + 5;

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

int n, to[N];
char g[N][N];

int main() {
    io >> n;
    For (i, 1, n) scanf("%s", g[i] + 1);
    For (i, 1, n) For (j, 1, n) if (g[i][j] & 1 && (!to[i] || g[j][to[i]] & 1)) to[i] = j;
    For (i, 1, n) For (j, 1, n) if (g[to[i]][j] & 1 && g[j][i] & 1) return printf("%d %d %d", i, to[i], j), 0;
    puts("-1");

    return 0;
}
