#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef array<int, 2 > P;
const int N = 1e6 + 5;
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

int T, n, m, en, head[N], to[N << 1], nxt[N << 1], w[N << 1], S[N][3], tim, dfn[N], on[N];
int go[N], mn[N], b[N], ans, V, E, rt, c0, c1, c2;
P Mn;

inline void add(int u, int v, int i) {
    nxt[++en] = head[u]; head[u] = en;
    to[en] = v; w[en] = u == S[i][1] || u == S[i][S[i][0]];
}

inline int dfs0(int u, int pre) {
    dfn[u] = ++tim; V++;
    int res = 0;
    for (int i = head[u], v; v = to[i], i; i = nxt[i]) if (i ^ pre ^ 1 && dfn[v] <= dfn[u]) {
        E++;
        if (dfn[v] || (v = dfs0(v, i))) res = v;
    }
    if (res) on[u] = 1;
    return res^u? res: (rt = u, 0);
}

inline void dfs1(int u, int pre) {
    bool flag = 0;
    if (u == rt && pre) return;
    for (int i = head[u], v; v = to[i], i; i = nxt[i]) if (i ^ pre ^ 1) {
        if (flag && on[v]) continue;
        if (on[v]) {
            flag = 1;
            if (w[i] && w[i ^ 1] && u ^ v) c2++;
            else c0 += w[i], c1 += w[i ^ 1];
        } else ans += w[i ^ 1];
        dfs1(v, i);
    }
}

inline P dfs2(int u, int pre, int x) {
    P res = {x, u}; mn[u] = n;
    for (int i = head[u], v; v = to[i], i; i = nxt[i]) if (v ^ pre) {
        b[v] = w[i] && w[i ^ 1];
        ans += w[i ^ 1];
        P y = dfs2(v, u, x + w[i] - w[i ^ 1] - b[v]);
        if (y[0] < res[0]) go[u] = v, mn[u] = res[0], res = y;
        else cmin(mn[u], y[0]);
    }
    if (u == rt) Mn = res;
    return res;
}

inline int dfs3(int u, int x, int d) {
    if (u == Mn[1]) return Mn[0];
    cmin(x, mn[u] + d);
    if (b[go[u]]) {
        if (Mn[0] + 1 >= x) return Mn[0];
        Mn[0]++; x--; d++;
    }
    return dfs3(go[u], x, d);
}

inline void solve() {
    ans = tim = 0; en = 1;
    io >> n >> m;
    For (i, 1, m) dfn[i] = head[i] = on[i] = 0;
    For (i, 1, n) {
        io >> S[i][0];
        For (j, 1, S[i][0]) io >> S[i][j];
    }
    int x, u, v;
    For (i, 1, n) {
        io >> x;
        if (x == 1) io >> u, add(u, u, i), en++, w[en] = w[en ^ 1];
        else io >> u >> v, add(u, v, i), add(v, u, i);
    }
    For (i, 1, m) if (head[i] && !dfn[i]) {
        E = V = 0;
        dfs0(i, 0);
        if (E > V) { puts("-1"); return; }
        if (E == V) {
            c0 = c1 = c2 = 0;
            dfs1(rt, 0);
            if (c0 > c1) swap(c0, c1);
            if (c0 + c2 <= c1) ans += c0 + c2;
            else ans += (c0 + c1 + c2) >> 1;
        } else {
            rt = i;
            dfs2(i, 0, 0);
            ans += dfs3(i, n, 0);
        }
    }
    printf("%d\n", ans);
}

int main() {
    io >> T;
    while (T--) solve();

    return 0;
}
