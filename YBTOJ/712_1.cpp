#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5, INF = 1e9;
const double alp = 0.75;

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

int n, m, op, x, y, ans;

namespace KDT {
    int D, rt, tot, id[N];
#define F(i) For (i, 0, 1)
    struct P {
        int v[2];
        P(int x = 0, int y = 0) { v[0] = x; v[1] = y; }
        int& operator [] (const int &i) { return v[i]; }
        int operator - (const P &a) const { return abs(v[0] - a.v[0]) + abs(v[1] - a.v[1]); }
        bool operator < (const P &a) const { return v[D] < a.v[D]; }
    } v[N];
    struct Node {
        int l, r, s, x[2][2];
        P v;
        Node() { l = r = s = 0; F(i) x[i][0] = INF, x[i][1] = -INF; }
        Node(P p): v(p) { l = r = 0; s = 1; F(i) F(j) x[i][j] = p[i]; }
    } o[N];
#define ls o[u].l
#define rs o[u].r
    inline void up(int u) {
        F(i) o[u].x[i][0] = min(o[u].v[i], min(o[ls].x[i][0], o[rs].x[i][0])), o[u].x[i][1] = max(o[u].v[i], max(o[ls].x[i][1], o[rs].x[i][1]));
        o[u].s = o[ls].s + o[rs].s + 1;
    }
    inline void pia(int u, int s) {
        if (!u) return;
        pia(ls, s); s += o[ls].s + 1; v[s] = o[id[s] = u].v; pia(rs, s);
    }
    int build(int l, int r, int d = 0) {
        if (l > r) return 0;
        int m = (l + r) >> 1, u = id[m];
        D = d; nth_element(v + l, v + m, v + r + 1);
        o[u] = Node(v[m]);
        ls = build(l, m - 1, d ^ 1); rs = build(m + 1, r, d ^ 1); up(u);
        return u;
    }
    void ins(int &u, P p, int d = 0) {
        if (!u) return u = ++tot, o[u] = Node(p), void();
        D = d; p < v[u]? ins(ls, p, d ^ 1): ins(rs, p, d ^ 1); up(u);
        if (max(o[ls].s, o[rs].s) > alp * o[u].s) pia(u, 0), u = build(1, o[u].s, d);
    }
    inline int dist(int u, P p) {
        if (!u) return INF;
        int r = 0;
        F(i) r += max(0, o[u].x[i][0] - p[i]) + max(0, p[i] - o[u].x[i][1]);
        return r;
    }
    void query(int u, P p) {
        ans = min(ans, o[u].v - p);
        int dl = dist(ls, p), dr = dist(rs, p);
        if (dl < dr) { if (dl < ans) { query(ls, p); if (dr < ans) query(rs, p); } }
        else { if (dr < ans) { query(rs, p); if (dl < ans) query(ls, p); } }
    }
}
using namespace KDT;

int main() {
    io >> n >> m;
    For (i, 1, n) io >> v[i][0] >> v[i][1], id[i] = i;
    rt = build(1, tot = n);
    while (m--) {
        io >> op >> x >> y;
        if (op == 1)
            ins(rt, P(x, y));
        else {
            ans = INF;
            query(rt, P(x, y));
            printf("%d\n", ans);
        }
    }

    return 0;
}
