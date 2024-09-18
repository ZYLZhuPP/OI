#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5, inf = 1e9;
const double alp = 0.75;

int n, x, y, op, a, b, c, d, ans;

namespace KDT {
    int D, rt, tot, id[N];
#define F(i) For(i, 0, 1)
    struct P {
        int o[2], v;
        P(int x = 0, int y = 0, int v = 0): v(v) { o[0] = x; o[1] = y; }
        int operator [] (const int &i) const { return o[i]; }
        bool operator < (const P &a) const { return o[D] < a.o[D]; }
    };
    struct Node {
        int l, r, sz, s, x[2][2];
        P v;
        Node() { l = r = sz = s = 0; F(i) x[i][0] = inf, x[i][1] = -inf; }
        Node(const P &p): v(p) { l = r = 0; sz = 1; s = p.v; F(i) F(j) x[i][j] = p[i]; }
        Node(const int &a, const int &b, const int &c, const int &d) { x[0][0] = a; x[0][1] = c; x[1][0] = b; x[1][1] = d; }
        bool out(const Node &a) const { F(i) if (x[i][0] > a.x[i][1] || x[i][1] < a.x[i][0]) return 1; return 0; }
        bool in(const Node &a) const { F(i) if (x[i][0] < a.x[i][0] || x[i][1] > a.x[i][1]) return 0; return 1; }
    } o[N];
#define ls o[u].l
#define rs o[u].r
    inline void up(int u) {
        F(i) o[u].x[i][0] = min(o[u].v[i], min(o[ls].x[i][0], o[rs].x[i][0])), o[u].x[i][1] = max(o[u].v[i], max(o[ls].x[i][1], o[rs].x[i][1]));
        o[u].sz = o[ls].sz + o[rs].sz + 1;
        o[u].s = o[ls].s + o[rs].s + o[u].v.v;
    }
    inline void pia(int u, int s) { if (!u) return; pia(ls, s); s += o[ls].sz + 1; id[s] = u; pia(rs, s); }
    int build(int l, int r, int d = 0) {
        if (l > r) return 0;
        int m = (l + r) >> 1;
        D = d; nth_element(id + l, id + m, id + r + 1, [&](const int &a, const int &b) { return o[a].v < o[b].v; } );
        int u = id[m];
        ls = build(l, m - 1, d ^ 1); rs = build(m + 1, r, d ^ 1); up(u);
        return u;
    }
    inline void check(int &u, int d) { if (max(o[ls].sz, o[rs].sz) > alp * o[u].sz) pia(u, 0), u = build(1, o[u].sz, d); }
    void ins(int &u, const P &p, int d = 0) {
        if (!u) return u = ++tot, o[u] = Node(p), void();
        D = d; p < o[u].v? ins(ls, p, d ^ 1): ins(rs, p, d ^ 1); up(u); check(u, d);
    }
    int query(int u, const Node &p) {
        if (!u || o[u].out(p)) return 0;
        if (o[u].in(p)) return o[u].s;
        return Node(o[u].v).in(p) * o[u].v.v + query(ls, p) + query(rs, p);
    }
}
using namespace KDT;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    while (cin >> op, op ^ 3) {
        if (op == 1) {
            cin >> x >> y >> d; x ^= ans; y ^= ans; d ^= ans;
            ins(rt, P(x, y, d));
        } else {
            cin >> a >> b >> c >> d; a ^= ans; b ^= ans; c ^= ans; d ^= ans;
            cout << (ans = query(rt, Node(a, b, c, d))) << endl;
        }
    }

    return 0;
}
