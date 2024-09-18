#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 2e5 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline int mul(int x, int y) { return 1ll * x * y % Mo; }

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

int n, m, a[N], b[N], _2[N];

struct Node {
    int mx, s;
    Node(int mx = 0, int s = 0): mx(mx), s(s) { }
    Node operator + (const Node &x) const {
        return mx>x.mx? *this: x.mx>mx? x: Node{mx, mo(s + x.s)};
    }
} f[N], g[N];

namespace tr {
    Node o[2][N];
#define lowbit(x) ((x) & -(x))
    void upd(int x, Node d, int op) {
        for (; x > 0 && x < m; x += op * lowbit(x))
            o[op == 1][x] = o[op == 1][x] + d;
    }
    Node query(int x, int op) {
        Node res;
        for (; x > 0 && x < m; x += op * lowbit(x))
            res = res + o[op == -1][x];
        return res;
    }
}

int main() {
    io >> n;
    For (i, 1, n) io >> a[i], b[i] = a[i];
    sort(b + 1, b + n + 1);
    m = unique(b + 1, b + n + 1) - b;
    For (i, 1, n) a[i] = lower_bound(b + 1, b + m, a[i]) - b;
    _2[0] = 1; For (i, 1, n) _2[i] = mo(_2[i - 1] << 1);

    rFor (i, n, 1) {
        f[i] = tr::query(a[i] + 1, 1);
        f[i].mx++; if (!f[i].s) f[i].s = 1;
        tr::upd(a[i], f[i], -1);
    }
    rFor (i, n, 1) {
        g[i] = tr::query(a[i] - 1, -1);
        g[i].mx++; if (!g[i].s) g[i].s = 1;
        tr::upd(a[i], g[i], 1);
    }
    
    Node ans;
    For (i, 1, n) {
        int x = f[i].mx + g[i].mx - 1;
        ans = ans + Node{x, mul(_2[n - x], mul(f[i].s, g[i].s))};
    }

    printf("%d %d", ans.mx, ans.s);

    return 0;
}
