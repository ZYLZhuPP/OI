#include<bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e4 + 5, M = 2e5 + 5, inf = 1e9;

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

int n, m, ans = inf, val[N + M];
pair<pair<int, int >, pair<int, int > > q[M];

namespace LCT {
    struct Node {
        int c[2], f, v, id, rev;
#define l c[0]
#define r c[1]
        Node() { l = r = f = v = rev = 0; }
    } o[N + M];
#define fu o[u].f
#define ls o[u].l
#define rs o[u].r
    inline bool is(const int &u) { return o[fu].r==u; }
    inline bool nrt(const int &u) { return !u||o[fu].l==u||is(u); }
    inline void chk(int &x, const int &y) { x = val[y]>val[x]? y: x; }
    inline void up(int u) { o[u].v = u; chk(o[u].v, o[ls].v); chk(o[u].v, o[rs].v); }
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
    inline void access(int u) { for (int f = u, v = 0; f; v = f, f = o[f].f) splay(f), o[f].r = v, up(f); splay(u); }
    inline void makert(int u) { access(u); rev(u); }
    inline int findrt(int u) { access(u); down(u); while (ls) down(u = ls); splay(u); return u; }
    inline void link(int u, int v) { makert(u); fu = v; }
    inline void pick(int u, int v) { makert(u); access(v); splay(u); }
}
using namespace LCT;

int main() {
    io >> n >> m;
    For (i, 1, m) io >> q[i].nd.st >> q[i].nd.nd >> q[i].st.st >> q[i].st.nd;
    sort(q + 1, q + m + 1);
    For (i, 1, m) {
        int u = q[i].nd.st, v = q[i].nd.nd, a = q[i].st.st, b = q[i].st.nd;
        if (u == v) continue;
        val[i + n] = b;
        if (findrt(u) ^ findrt(v)) link(u, i + n), link(v, i + n);
        else {
            pick(u, v);
            int x = o[u].v;
            if (b < val[x]) {
                splay(x); o[o[x].l].f = o[o[x].r].f = 0;
                link(u, i + n); link(v, i + n);
            }
        }
        if (findrt(1) == findrt(n)) pick(1, n), ans = min(ans, a + val[o[1].v]);
    }
    printf("%d", ans<inf? ans: -1);

    return 0;
}
