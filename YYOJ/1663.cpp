#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef unsigned long long ull;
const int N = 45;

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
    inline bool operator ~() {return ~c;}
} io;

ull g[N];
int n, m, x, ans, u, v, cnt[N];
long double p;

namespace BK {
    bool dfs(int u, int k, ull vis, ull to) {
        if (!to) { return k > ans? ans = k, 1: 0; }
        rFor (i, u - 1, 1) if (to >> i & 1) {
            if (k + cnt[i] <= ans) return 0;
            if(dfs(i, k + 1, vis | (1ull << i), to & g[i])) return 1;
        }
        return 0;
    }

    void solve() {
        ans = 0;
        For (i, 1, n) {
            dfs(i, 1, 1ull << i, g[i]);
            cnt[i] = ans;
        }
    }
}

int main() {
    io >> n >> m >> x; p = x;
    For (i, 1, m) {
        io >> u >> v;
        if (u < v) swap(u, v);
        g[u] |= 1ull << v;
    }
    BK::solve();
    printf("%.6Lf", 0.5L * (p * p - p * p / ans));
    return 0;
}
