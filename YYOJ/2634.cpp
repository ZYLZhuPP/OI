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

int n, m, fa[N], s[N], a[N], tot, rt = 1, re, dep[N];
vector<int > es[N];
ll ans;

inline int find(int x) { return fa[x]^x? fa[x] = find(fa[x]): x; }

inline void dfs(int u, int pre) {
    fa[u] = pre; dep[u] = dep[pre] + 1; s[u] = dep[u]&1? 1: -1;
    for (auto &v : es[u]) if (v ^ pre) dfs(v, u), s[u] += s[v];
}

int main() {
    io >> n >> m;
    For (i, 1, n) fa[i] = i;
    int u, v;
    For (i, 1, m) {
        io >> u >> v;
        if (find(u) ^ find(v)) fa[fa[u]] = fa[v];
        else { rt = u; re = v; continue; }
        es[u].pb(v), es[v].pb(u);
    }
    dfs(rt, 0);
    if (n == m) {
        for (int u = re; u; u = fa[u]) a[++tot] = s[u];
        if (tot & 1) {
            if (s[rt] & 1) return puts("-1"), 0;
            for (int u = re; u; u = fa[u]) s[u] -= s[rt] >> 1;
        } else {
            if (s[rt]) return puts("-1"), 0;
            sort(a + 1, a + tot + 1);
            for (int u = re; u; u = fa[u]) s[u] -= a[tot >> 1];
        }
    } else if (s[rt]) return puts("-1"), 0;
    For (i, 1, n) ans += abs(s[i]);
    printf("%lld", ans);

    return 0;
}
