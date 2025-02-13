#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e4 + 5, inf = 1e9;

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
	inline bool operator ~ () const { return ~c; }
} io;

int n, x, ans;

namespace Splay {
    int tot, rt;
    struct Node {
        int c[2], f, v;
#define l c[0]
#define r c[1]
        Node(int v = 0, int f = 0): f(f), v(v) { l = r = 0; }
    } o[N];
#define fu o[u].f
#define ls o[u].l
#define rs o[u].r
    inline bool is(const int &u) { return u == o[fu].r; }
    inline void up(const int &u) { }
    inline void rot(int u) {
        int k = is(u), f = fu, ff = o[f].f, c = o[u].c[!k];
        if (ff) o[ff].c[is(f)] = u; o[u].c[!k] = f; o[f].c[k] = c;
        if (c) o[c].f = f; o[f].f = u; fu = ff;
        up(f); up(u);
    }
    inline void splay(int u, int g = 0) { for (; fu ^ g; rot(u)) if (o[fu].f ^ g) rot(is(fu)^is(u)? u: fu); if (!g) rt = u; }
    inline void ins(int &u, int k, int f = 0) {
        if (!u) return o[u = ++tot] = Node(k, f), splay(u);
        ins(o[u].c[o[u].v < k], k, u);
    }
    inline int pre() {
        int u = o[rt].l;
        if (!u) return -inf;
        while (rs) u = rs;
        return o[u].v;
    }
    inline int suf() {
        int u = o[rt].r;
        if (!u) return inf;
        while (ls) u = ls;
        return o[u].v;
    }
}
using namespace Splay;

int main() {
    io >> n;
    For (i, 1, n) {
        io >> x;
        ins(rt, x);
        ans += i==1? x: min(x - pre(), suf() - x);
    }
    cout << ans;

    return 0;
}
