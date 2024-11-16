#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e5 + 5;

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

int n, m, dep[N], s[N][2];
vector<int > es[N];
ll ans;

inline void dfs0(int u, int pre) {
    dep[u] = dep[pre] + 1; s[u][dep[u] & 1] = 1;
    for (auto &v : es[u]) if (v ^ pre) dfs0(v, u), s[u][0] += s[v][0], s[u][1] += s[v][1];
}

int main() {
    io >> n >> m;
    if (m == n) return printf("%d", n / 2), 0;
    int u, v;
    For (i, 1, m) io >> u >> v, es[u].pb(v), es[v].pb(u);
    dfs0(1, 0);
    if (s[1][0] ^ s[1][1]) return puts("-1"), 0;
    For (i, 1, n) ans += abs(s[i][0] - s[i][1]);
    printf("%lld", ans);

    return 0;
}
