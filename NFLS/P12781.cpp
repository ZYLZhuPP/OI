#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

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

int T;
queue<array<int, 2 > > q[N][2];

namespace Seg {
    struct Node {
        int mx, l, r, c;
        Node(int mx = 0, int l = 0, int r = 0, int c = 1): mx(mx), l(l), r(r), c(c) { }
        Node operator + (const Node &a) const {
            Node res(max(mx, a.mx), l, a.r, 0);
            res.c = (mx==res.mx? c: 0) + (a.mx==res.mx? a.c: 0);
            if (r == res.mx && a.l == res.mx) res.c--;
            return res;
        }
    } o[N << 2];
    int t[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p] = o[ls] + o[rs]; }
    inline void mark(int p, const int &v) { o[p] = {v, v, v, 1}; t[p] = v; }
    inline void down(int p) { if (t[p]) mark(ls, t[p]), mark(rs, t[p]), t[p] = 0; }
    inline void upd(int p, int l, int r, int x, int y, const int &v) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mark(p, v);
        down(p); M; upd(goL, x, y, v); upd(goR, x, y, v); up(p);
    }
    inline Node query(int p, int l, int r, int x, int y) {
        if (x <= l && r <= y) return o[p];
        down(p); M; return y<=m? query(goL, x, y): x>m? query(goR, x, y): (query(goL, x, y) + query(goR, x, y));
    }
}
using namespace Seg;

inline void solve() {
    int l, r, h, ans, flag;
    io >> l >> r >> h; l++;
    Node now = query(1, 0, N, l, r);
    ans = now.c - 1; flag = 0;
    
    while (q[l - 1][0].size() && q[l - 1][0].front()[1] <= now.mx) q[l - 1][0].pop();
    while (q[l - 1][0].size() && (q[l - 1][0].front()[1] <= now.mx + h)) flag |= (q[l - 1][0].front()[0] <= now.mx), ans++, q[l - 1][0].pop();
    if (q[l - 1][0].size() && q[l - 1][0].front()[0] <= now.mx) flag = 1;
    if (!flag && query(1, 0, N, l - 1, l - 1).mx >= now.mx && now.l != now.mx) ans++;
    if (now.l != now.mx) q[l][1].push({now.l + 1, now.mx});
    
    flag = 0;
    while (q[r + 1][1].size() && q[r + 1][1].front()[1] <= now.mx) q[r + 1][1].pop();
    while (q[r + 1][1].size() && (q[r + 1][1].front()[1] <= now.mx + h)) flag |= (q[r + 1][1].front()[0] <= now.mx), ans++, q[r + 1][1].pop();
    if (q[r + 1][1].size() && q[r + 1][1].front()[0] <= now.mx) flag = 1;
    if (!flag && query(1, 0, N, r + 1, r + 1).mx >= now.mx && now.r != now.mx) ans++;
    if (now.r != now.mx) q[r][0].push({now.r + 1, now.mx});

    upd(1, 0, N, l, r, now.mx + h);
    printf("%d\n", ans);
}

int main() {
    freopen("block.in", "r", stdin);
    freopen("block.out", "w", stdout);
    io >> T;
    while (T--) solve();

    fclose(stdin); fclose(stdout);
    return 0;
}
