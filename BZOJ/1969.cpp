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

int n, m, fa[N], T, op[N], ans[N];
bool no[N];
array<int, 2 > es[N], qs[N];
map<array<int, 2 >, int > id;

inline int find(int x) { return fa[x]^x? fa[x] = find(fa[x]): x; }

namespace LCT {
    struct Node {
        int f, c[2], sz, rev;
#define l c[0]
#define r c[1]
        Node () { f = l = r = sz = rev = 0; }
    } o[N];
#define fu o[u].f
#define ls o[u].l
#define rs o[u].r
    inline bool is(const int &u) { return u==o[fu].r; }
    inline bool nrt(const int &u) { return !u||u==o[fu].l||is(u); }
    inline void up(int u) { o[u].sz = o[ls].sz + o[rs].sz + 1; }
    inline void rev(int u) { if (u) swap(ls, rs), o[u].rev ^= 1; }
    inline void down(int u) { if (o[u].rev) rev(ls), rev(rs), o[u].rev = 0; }
    inline void updown(int u) { if (nrt(u)) updown(fu); down(u); }
    inline void rot(int u) {
        int k = is(u), f = fu, ff = o[f].f, c = o[u].c[!k];
        if (nrt(f)) o[ff].c[is(f)] = u; o[u].c[!k] = f; o[f].c[k] = c;
        if (c) o[c].f = f; o[f].f = u; fu = ff;
        up(f); up(u);
    }
    inline void splay(int u) { updown(u); for (; nrt(u); rot(u)) if (nrt(fu)) rot(is(fu)^is(u)? u: fu); }
    inline void access(int u) { for (int f = u, v = 0; f; v = f, f = o[v].f = find(o[f].f)) splay(f), o[f].r = v, up(f); splay(u); }
    inline void makert(int u) { access(u); rev(u); }
    inline int findrt(int u) { access(u); down(u); while (ls) down(u = ls); splay(u); return u; }
    inline void link(int u, int v) { makert(u); if (findrt(v) ^ u) fu = v; }
    inline void cut(int u, int v) { makert(u); if (findrt(v) == u && o[v].f == u && !o[v].l) rs = o[v].f = 0; }
    inline void pick(int u, int v) { makert(u); access(v); splay(u); }
}
using namespace LCT;

inline void del(int &u, int rt) { if (u) fa[u] = rt, del(ls, rt), del(rs, rt), u = 0; }

inline void upd(int u, int v) {
    u = find(u); v = find(v);
    if (u == v) return;
    makert(u);
    if (findrt(v) ^ u) return void(fu = v);
    del(rs, u); up(u);
}

inline int query(int u, int v) {
    u = find(u); v = find(v);
    pick(u, v); return o[u].sz - 1;
}

int main() {
    io >> n >> m;
    For (i, 1, n) fa[i] = i, o[i].sz = 1;
    For (i, 1, m) {
        int u, v;
        io >> u >> v; if (u > v) swap(u, v);
        es[i] = {u, v}; id[es[i]] = i;
    }
    while (++T) {
        io >> op[T];
        if (op[T] == -1) break;
        int u, v;
        io >> u >> v; if (u > v) swap(u, v);
        qs[T] = {u, v};
        if (op[T] == 0) no[id[qs[T]]] = 1;
    }
    For (i, 1, m) if (!no[i]) upd(es[i][0], es[i][1]);
    rFor (i, T - 1, 1) {
        if (op[i] == 1) ans[i] = query(qs[i][0], qs[i][1]);
        else upd(qs[i][0], qs[i][1]);
    }
    For (i, 1, T - 1) if (op[i]) printf("%d\n", ans[i]);

    return 0;
}
