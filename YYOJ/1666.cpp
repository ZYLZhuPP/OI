#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (register int i = (l); i <= (r); ++i)
const int N = 2e5 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int mul(const int &x, const int &y) { return 1ll * x * y % Mo; } 

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
	inline bool operator ~() {return ~c;}
} io;

int n, m, px[N], py[N];
const int dx[4][4] = { {0,0,-1,-1}, {0,-1,-1,0}, {0,0,1,1}, {0,1,1,0} };
const int dy[4][4] = { {0,-1,-1,0}, {0,0,1,1}, {0,1,1,0}, {0,0,-1,-1} };
int ans;
vector<int > w[N];

namespace tr {
    struct Node {
        int mi, c, s;
        Node operator + (const Node &x) const { return mi == x.mi? Node{mi, c + x.c, mo(s + x.s)}: mi < x.mi? *this: x; }
    } o[N << 2];
    int tag[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    void pushup(int p) { o[p] = o[ls] + o[rs]; }
    void mark(int p, int d) { o[p].mi += d; tag[p] += d; }
    void pushdown(int p) { if (tag[p]) mark(ls, tag[p]), mark(rs, tag[p]), tag[p] = 0; }
    void build(int p, int l, int r) {
        if (l == r) { o[p] = Node{0, 1, l}; return; }
        M; build(goL); build(goR);
        pushup(p);
    }
    void upd(int p, int l, int r, int x, int y, int d) {
        if (r < x || y < l) return;
        if (x <= l && r <= y) return mark(p, d);
        pushdown(p); M; upd(goL, x, y, d); upd(goR, x, y, d);
        pushup(p);
    }
    Node query(int p, int l, int r, int x, int y) {
        if (x <= l && r <= y) return o[p];
        M; return m+1>y? query(goL, x, y): m<x? query(goR, x, y): query(goL, x, y) + query(goR, x, y);
    }
}

int f(int x) { return x == 1 || x == 3; }

void solve(int x, int y) {
    int v = w[x][y], a[5] = {0};
    For (i, 0, 3) {
        For (j, 0, 3) a[j + 1] = w[x + dx[i][j]][y + dy[i][j]];
        sort(a + 1, a + 5);
        int p = lower_bound(a + 1, a + 5, v) - a;
        For (j, 1, p) {
            int d = f(p - j + 1) - f(p - j);
            tr::upd(1, 1, n, a[j - 1] + 1, a[j], d);
        }
    }
}

int main() {
    io >> n >> m; 
    For (i, 0, n + 1) {
        w[i].resize(m + 2);
        w[i][0] = w[i][m + 1] = n * m + 1;
        For (j, 1, m) {
            if (!i || i > n) w[i][j] = n * m + 1;
            else io >> w[i][j], px[w[i][j]] = i, py[w[i][j]] = j;
        }
    }

    n = n * m;
    tr::build(1, 1, n);

    For (i, 1, n) {
        solve(px[i], py[i]);
        tr::Node res = tr::Node{4, 0, 0} + tr::query(1, 1, n, 1, i);
        add(ans, mo(mul(i + 1, res.c) - res.s));
    }

    printf("%d", ans);

    return 0;
}
