#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e4 + 5;

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

int n, m;

namespace LCT {
    struct Node {
        int c[2], f; ll v, sz, x, s, sl, sr, t, rev;
#define l c[0]
#define r c[1]
        Node() { l = r = f = v = sz = x = s = sl = sr = t = rev = 0; }
        Node(int v): v(v) { l = r = f = 0; sz = 1; x = s = sl = sr = v; t = rev = 0; }
    } o[N];
#define fu o[u].f
#define ls o[u].l
#define rs o[u].r
    inline bool is(const int &u) { return o[fu].r==u; }
    inline bool nrt(const int &u) { return !u||o[fu].l==u||is(u); }
    inline void up(int u) {
        Node &I = o[u], &L = o[ls], &R = o[rs];
        I.sz = L.sz + R.sz + 1; I.s = L.s + R.s + I.v;
        I.sl = L.sl + R.sl + (L.s + I.v) * (R.sz + 1);
        I.sr = L.sr + R.sr + (R.s + I.v) * (L.sz + 1);
        I.x = L.x + R.x + L.sr * (R.sz + 1) + R.sl * (L.sz + 1) + I.v * (L.sz + 1) * (R.sz + 1);
    }
    inline void mark(int u, const int &d) {
        if (!u) return;
        o[u].v += d; o[u].t += d;
        ll sz = o[u].sz;
        o[u].s += sz * d;
        o[u].sl += sz * (sz + 1) / 2 * d;
        o[u].sr += sz * (sz + 1) / 2 * d;
        o[u].x += sz * (sz + 1) * (sz + 2) / 6 * d;
    }
    inline void rev(int u) { if (u) swap(ls, rs), swap(o[u].sl, o[u].sr), o[u].rev ^= 1; }
    inline void down(int u) {
        if (o[u].rev) rev(ls), rev(rs), o[u].rev = 0;
        if (o[u].t) mark(ls, o[u].t), mark(rs, o[u].t), o[u].t = 0;
    }
    inline void updown(int u) { if (nrt(u)) updown(fu); down(u); }
    inline void rot(int u) {
        int k = is(u), f = fu, ff = o[f].f, c = o[u].c[!k];
        if (nrt(f)) o[ff].c[is(f)] = u; o[u].c[!k] = f; o[f].c[k] = c;
        if (c) o[c].f = f; o[f].f = u; fu = ff;
        up(f); up(u);
    }
    inline void splay(int u) { updown(u); for (; nrt(u); rot(u)) if (nrt(fu)) rot(is(fu)^is(u)? u: fu); }
    inline void access(int u) { for (int f = u, v = 0; f; v = f, f = o[f].f) splay(f), o[f].r = v, up(f); splay(u); }
    inline void makert(int u) { access(u); rev(u); }
    inline int findrt(int u) { access(u); down(u); while (ls) down(u = ls); splay(u); return u; }
    inline void link(int u, int v) { makert(u); if (findrt(v) ^ u) fu = v; }
    inline void cut(int u, int v) { makert(u); if (findrt(v) == u && o[v].f == u && !o[v].l) rs = o[v].f = 0; }
    inline void pick(int u, int v) { makert(u); access(v); splay(u); }
}
using namespace LCT;

int main() {
    io >> n >> m;
    int x, u, v, d, op;
    For (i, 1, n) io >> x, o[i] = Node(x);
    For (i, 1, n - 1) io >> u >> v, link(u, v);
    while (m--) {
        io >> op >> u >> v;
        if (op == 1) cut(u, v);
        else if (op == 2) link(u, v);
        else if (op == 3) {
            io >> d;
            if (findrt(u) ^ findrt(v)) continue;
            pick(u, v);
            mark(u, d);
        } else if (op == 4) {
            if (findrt(u) ^ findrt(v)) { puts("-1"); continue; }
            pick(u, v);
            ll x = o[u].x, y = o[u].sz * (o[u].sz + 1) / 2, g = __gcd(x, y);
            printf("%lld/%lld\n", x / g, y / g);
        }
    }

    return 0;
}
