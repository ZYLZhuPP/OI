#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e4 + 5;

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

int T, n, m, U[N], V[N], fa[N], vis[N], id[N];

inline int find(int x) { return fa[x]^x? fa[x] = find(fa[x]): x; }

inline bool cross(int x, int X, int y, int Y) {
    if (X < x) swap(x, X), swap(y, Y);
    if (x == X || y == Y || x == Y || X == y) return 0;
    return X < y && y < Y;
}

inline bool ok() {
    For (i, 1, 2 * m) fa[i] = i;
    For (i, 1, m) if (!vis[i]) For (j, 1, m) if (!vis[j]) if (cross(U[i], U[j], V[i], V[j])) {
        int u = find(i), v = find(j);
        if (u == v) return 0;
        fa[u] = find(j + m);
        fa[v] = find(i + m);
    }
    return 1;
}

int main() {
    io >> T;
    while (T--) {
        io >> n >> m;
        For (i, 1, m) io >> U[i] >> V[i];
        int x;
        For (i, 1, n) io >> x, id[x] = i;
        if (m > 3 * n - 6) { puts("NO"); continue; }
        For (i, 1, m) {
            U[i] = id[U[i]]; V[i] = id[V[i]];
            if (U[i] > V[i]) swap(U[i], V[i]);
            vis[i] = V[i] == U[i] + 1 || (U[i] == 1 && V[i] == n);
        }
        puts(ok()? "YES": "NO");
    }

    return 0;
}
