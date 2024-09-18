#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, inf = 1e9;

int n, x[N], y[N], Mn, Mx, ans;

namespace KDT {
    int D, rt, id[N];
#define F(i) For(i, 0, 1)
    struct P {
        int o[2];
        P(int x = 0, int y = 0) { o[0] = x; o[1] = y; }
        int operator [] (const int &i) const { return o[i]; }
        int operator - (const P &p) const { return abs(o[0] - p.o[0]) + abs(o[1] - p.o[1]); }
        bool operator < (const P &a) const { return o[D] < a.o[D]; }
    };
    struct Node {
        int l, r, sz, x[2][2];
        P v;
        Node() { l = r = sz = 0; F(i) x[i][0] = inf, x[i][1] = -inf; }
        Node(const P &p): v(p) { l = r = 0; sz = 1; F(i) F(j) x[i][j] = p[i]; }
    } o[N];
#define ls o[u].l
#define rs o[u].r
    inline void up(int u) {
        F(i) o[u].x[i][0] = min(o[u].v[i], min(o[ls].x[i][0], o[rs].x[i][0])), o[u].x[i][1] = max(o[u].v[i], max(o[ls].x[i][1], o[rs].x[i][1]));
        o[u].sz = o[ls].sz + o[rs].sz + 1;
    }
    int build(int l, int r, int d = 0) {
        if (l > r) return 0;
        int m = (l + r) >> 1;
        D = d; nth_element(id + l, id + m, id + r + 1, [&](const int &a, const int &b) { return o[a].v < o[b].v; } );
        int u = id[m];
        ls = build(l, m - 1, d ^ 1); rs = build(m + 1, r, d ^ 1); up(u);
        return u;
    }
    inline int mxdist(int u, const P &p) {
        int r = 0;
        F(i) F(j) r = max(r, p - P(o[u].x[0][i], o[u].x[1][j]));
        return r;
    }
    inline int mndist(int u, const P &p) {
        int r = 0;
        F(i) r += max(0, o[u].x[i][0] - p[i]) + max(0, p[i] - o[u].x[i][1]);
        return r;
    }
    void querymx(int u, const P &p) {
        if (!u) return;
        int d = p - o[u].v;
        if (d) Mx = max(Mx, d);
        int dl = mxdist(ls, p), dr = mxdist(rs, p);
        if (dl > dr) { if (dl > Mx) { querymx(ls, p); if (dr > Mx) querymx(rs, p); } }
        else { if (dr > Mx) { querymx(rs, p); if (dl > Mx) querymx(ls, p); } }
    }
    void querymn(int u, const P &p) {
        if (!u) return;
        int d = p - o[u].v;
        if (d) Mn = min(Mn, d);
        int dl = mndist(ls, p), dr = mndist(rs, p);
        if (dl < dr) { if (dl < Mn) { querymn(ls, p); if (dr < Mn) querymn(rs, p); } }
        else { if (dr < Mn) { querymn(rs, p); if (dl < Mn) querymn(ls, p); } }
    }
}
using namespace KDT;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    For (i, 1, n) {
        cin >> x[i] >> y[i];
        o[id[i] = i] = Node(P(x[i], y[i]));
    }
    rt = build(1, n);
    ans = inf;
    For (i, 1, n) {
        Mx = 0; Mn = inf;
        querymx(rt, P(x[i], y[i])); querymn(rt, P(x[i], y[i]));
        ans = min(ans, Mx - Mn);
    }
    cout << ans;

    return 0;
}
