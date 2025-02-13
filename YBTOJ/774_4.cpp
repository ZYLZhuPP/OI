#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1.5e5 + 5;

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

int n, m, w[N];

namespace DSU {
    int fa[N], val[N];
    inline void init(int n) { For (i, 1, n) fa[i] = i, val[i] = w[i]; }
    inline int find(int u) { return fa[u]^u? fa[u] = find(fa[u]): u; }
}
using namespace DSU;

namespace LCT {
    struct Node {
        int c[2], f, s, rev;
#define l c[0]
#define r c[1]
        Node() { l = r = f = s = rev = 0; }
    } o[N];
#define fu (o[u].f=find(o[u].f))
#define ls o[u].l
#define rs o[u].r
    inline bool is(const int &u) { return o[fu].r==u; }
    inline bool nrt(const int &u) { return !u||o[fu].l==u||is(u); }
    inline void up(int u) { o[u].s = o[ls].s + o[rs].s + val[u]; }
    inline void rev(int u) { if (u) swap(ls, rs), o[u].rev ^= 1; }
    inline void down(int u) { if (o[u].rev) rev(ls), rev(rs), o[u].rev = 0; }
    inline void updown(int u) { if (nrt(u)) updown(fu); down(u); }
    inline void rot(int u) {
        int k = is(u), f = fu, ff = o[f].f = find(o[f].f), c = o[u].c[!k];
        if (nrt(f)) o[ff].c[is(f)] = u; o[u].c[!k] = f; o[f].c[k] = c;
        if (c) o[c].f = f; o[f].f = u; fu = ff;
        up(f); up(u);
    }
    inline void splay(int u) { updown(u); for (; nrt(u); rot(u)) if (nrt(fu)) rot(is(fu)^is(u)? u: fu); }
    inline void access(int u) { for (int f = u, v = 0; f; v = f, f = o[f].f = find(o[f].f)) splay(f), o[f].r = v, up(f); splay(u); }
    inline void makert(int u) { access(u); rev(u); }
    inline int findrt(int u) { access(u); down(u); while (ls) down(u = ls); splay(u); return u; }
    inline void link(int u, int v) { makert(u); if (findrt(v) ^ u) fu = v; }
    inline void pick(int u, int v) { makert(u); access(v); splay(u); }
    inline void merge(int u, int rt) {
        if (!u) return;
        fa[u] = rt;
        merge(ls, rt); merge(rs, rt);
    }
}
using namespace LCT;

int main() {
    io >> n >> m;
    int x, u, v, op;
    For (i, 1, n) io >> w[i], o[i].s = w[i];
    init(n);
    while (m--) {
        io >> op >> u >> v;
        if (op == 1) {
            u = find(u); v = find(v);
            if (findrt(u) ^ findrt(v)) link(u, v);
            else {
                pick(u, v);
                val[u] = o[u].s;
                merge(u, u);
            }
        } else if (op == 2) {
            x = find(u);
            splay(x);
            val[x] += v - w[u];
            o[x].s += v - w[u];
            w[u] = v;
        } else if (op == 3) {
            u = find(u); v = find(v);
            if (findrt(u) ^ findrt(v)) puts("-1");
            else {
                pick(u, v);
                printf("%d\n", o[u].s);
            }
        }
    }

    return 0;
}
