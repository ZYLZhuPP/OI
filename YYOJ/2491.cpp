#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e3 + 5;

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

int n, m, x, ans[N];
bool g[N][N];
bitset<N > B;

inline bool dfs(int x, int k, bitset<N > b) {
    ans[k] = x;
    if (k == 1) return 1;
    int cnt = 0;
    For (i, 1, x) if (b[i]) cnt += (b[i] = g[i][x]);
    if (cnt < k - 1) return 0;
    rFor (i, x - 1, 1) if (b[i] && dfs(i, k - 1, b)) return 1;
    return 0;
}

int main() {
    io >> n >> m; x = n / 3;
    int u, v;
    For (i, 1, m) io >> u >> v, g[u][v] = g[v][u] = 1;
    For (i, 1, 2 * x - 1) B[i] = 1;
    For (i, 2 * x, n) if (dfs(i, x, B)) break;
    printf("%d\n", x);
    For (i, 1, x) printf("%d ", ans[i]);

    return 0;
}
