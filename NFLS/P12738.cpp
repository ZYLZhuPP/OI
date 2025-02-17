#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 3e6 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int n, len[N], son[N], f[N], dfn[N], tim;
ll K, cnt[N], ans;
basic_string<int > T[N];

inline void dfs(int u, int k) {
    cnt[f[dfn[u] = ++tim] = 1] += k;
    if (son[u]) dfs(son[u], k + 1);
    for (auto &v : T[u]) if (v ^ son[u]) {
        dfs(v, 1);
        For (i, 0, len[v]) cnt[f[dfn[u] + i + 1]] -= k, cnt[f[dfn[u] + i + 1] += f[dfn[v] + i]] += k;
    }
}

int main() {
    freopen("light.in", "r", stdin);
    freopen("light.out", "w", stdout);
    io >> n >> K;
    int x;
    For (i, 2, n) io >> x, T[x] += i;
    rFor (u, n, 1) for (auto &v : T[u]) if (cmax(len[u], len[v] + 1)) son[u] = v;
    dfs(1, 1);
    rFor (i, n, 1) ans += min(K, cnt[i]) * i, cmax(K -= cnt[i], 0ll);
    printf("%lld", ans);

    fclose(stdin); fclose(stdout);
    return 0;
}
