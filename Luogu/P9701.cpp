#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 4e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int T, n, m, U[N], V[N], W[N], pt[N], pos[N], l[N], r[N], cnt, tot, fa[N], pre[N], nxt[N];
ll ans;

inline int find(int x) { return fa[x]^x? fa[x] = find(fa[x]): x; }

inline void solve() {
    tot = cnt = 0;
    io >> n >> m;
    For (i, 1, m) {
        io >> U[i] >> V[i] >> W[i];
        pt[++tot] = U[i]; pt[++tot] = V[i];
    }
    sort(pt + 1, pt + tot + 1); tot = unique(pt + 1, pt + tot + 1) - pt - 1;
    int lst = 0;
    For (i, 1, tot) {
        if (pt[i] > lst + 1) cnt++, pos[cnt] = l[cnt] = lst + 1, r[cnt] = pt[i] - 1;
        cnt++; lst = pos[cnt] = l[cnt] = r[cnt] = pt[i];
    }
    if (pt[tot] < n) cnt++, pos[cnt] = l[cnt] = lst + 1, r[cnt] = n;
    ans = n - cnt;
    unordered_map<int, int > g[cnt + 1];
    For (i, 1, m) {
        int u = lower_bound(pos + 1, pos + cnt + 1, U[i]) - pos, v = lower_bound(pos + 1, pos + cnt + 1, V[i]) - pos;
        g[u][v] = g[v][u] = W[i];
    }
    n = cnt;
    fa[n + 1] = 0; For (i, 1, n) fa[i] = i;
    while (cnt > 1) {
        For (i, 1, n) if (find(i) == i) W[i] = 2e9;
        For (i, 1, n) pre[i] = fa[i]^fa[i - 1]? i - 1: pre[i - 1];
        rFor (i, n, 1) nxt[i] = fa[i]^fa[i + 1]? i + 1: nxt[i + 1];
        For (i, 1, n) {
            int j = i, f = fa[i];
            while (fa[j] == f || g[i].count(j)) j = fa[j]^f? j - 1: pre[j];
            if (j && cmin(W[f], l[i] - r[j])) V[f] = fa[j];
            j = i;
            while (fa[j] == f || g[i].count(j)) j = fa[j]^f? j + 1: nxt[j];
            if (j <= n && cmin(W[f], l[j] - r[i])) V[f] = fa[j];
            for (auto &[j, w] : g[i]) if (fa[j] ^ f && cmin(W[f], w)) V[f] = fa[j];
        }
        For (i, 1, n) if (find(i) == i && find(V[i]) ^ i) fa[i] = fa[V[i]], ans += W[i], cnt--;
    }
    printf("%lld\n", ans);
}

int main() {
    io >> T;
    while (T--) solve();

    return 0;
}
