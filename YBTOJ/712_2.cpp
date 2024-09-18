#include<bits/stdc++.h>
using namespace std;

#define mkp make_pair
#define st first
#define nd second
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
const int N = 1e5 + 5, inf = 1e9;
template<class C> inline void clear(C &a) { a = C(); }

int n, m, x, y, k;
priority_queue<pair<lf, int> > q;

namespace KDT {
    int D, rt;
#define F(i) For(i, 0, 1)
   struct P {
        int v[2], id;
        P(int x = 0, int y = 0, int id = 0): id(id) { v[0] = x; v[1] = y; }
        int& operator [] (const int &i) { return v[i]; }
        lf operator - (const P &a) { return 1.l * (v[0] - a.v[0]) * (v[0] - a.v[0]) + 1.l * (v[1] - a.v[1]) * (v[1] - a.v[1]); }
        bool operator < (const P &a) { return v[D] < a.v[D]; }
    } v[N];
    struct Node {
        int l, r, x[2][2];
        P v;
        Node() { l = r = 0; F(i) x[i][0] = inf, x[i][1] = -inf; }
        Node(P p): v(p) { l = r = 0; F(i) F(j) x[i][j] = p[i]; }
    } o[N];
#define ls o[u].l
#define rs o[u].r
    inline void up(int u) {
        F(i) o[u].x[i][0] = min(o[u].v[i], min(o[ls].x[i][0], o[rs].x[i][0])), o[u].x[i][1] = max(o[u].v[i], max(o[ls].x[i][1], o[rs].x[i][1]));
    }
    int build(int l, int r, int d = 0) {
        if (l > r) return 0;
        int m = (l + r) >> 1, u = m;
        D = d; nth_element(v + l, v + m, v + r + 1);
        o[u] = Node(v[m]);
        ls = build(l, m - 1, d ^ 1); rs = build(m + 1, r, d ^ 1); up(u);
        return u;
    }
    inline lf dist(int u, P p) {
        if (!u) return -1;
        lf r = 0;
        F(i) F(j) r = max(r, p - P(o[u].x[0][i], o[u].x[1][j]));
        return r;
    }
    void query(int u, P p) {
        if (!u) return;
        lf d = o[u].v - p; int id = o[u].v.id;
        if (mkp(-d, id) < q.top()) q.pop(), q.push(mkp(-d, id));
        lf dl = dist(ls, p), dr = dist(rs, p); int idl = o[ls].v.id, idr = o[rs].v.id;
        if (mkp(-dl, idl) < mkp(-dr, idr)) {
            if (mkp(-dl, idl) < q.top()) query(ls, p);
            if (mkp(-dr, idr) < q.top()) query(rs, p);
        } else {
            if (mkp(-dr, idr) < q.top()) query(rs, p);
            if (mkp(-dl, idl) < q.top()) query(ls, p);
        }
    }
}
using namespace KDT;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    For (i, 1, n) cin >> v[i][0] >> v[i][1], v[i].id = i;
    rt = build(1, n);
    cin >> m;
    while (m--) {
        cin >> x >> y >> k;
        clear(q); while (k--) q.push(mkp(inf, inf));
        query(rt, P(x, y));
        cout << q.top().nd << endl;
    }

    return 0;
}
