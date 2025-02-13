#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

struct IO {
    static const int BufS=1<<21;
	char buf[BufS], *S, *T, c, f;
	#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () { return ~c; }
} io;

int n, m, val[N];

namespace LCT {
    struct Node {
        int f, c[2], v, rev;
#define l c[0]
#define r c[1]
        Node () { f = l = r = v = rev = 0; }
    } o[N];
#define fu o[u].f
#define ls o[u].l
#define rs o[u].r
    inline bool is(const int &u) { return u==o[fu].r; }
    inline bool nrt(const int &u) { return !u||u==o[fu].l||is(u); }
    inline void up(int u) { o[u].v = o[ls].v ^ o[rs].v ^ val[u]; }
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
    inline void link(int u, int v) { makert(u); if (findrt(v) ^ u) fu = v; }
    inline void cut(int u, int v) { makert(u); if (findrt(v) == u && o[v].f == u && !o[v].l) rs = o[v].f = 0; }
    inline void pick(int u, int v) { makert(u); access(v); splay(u); }
}
using namespace LCT;

int main() {
    io >> n >> m;
    For (i, 1, n) io >> val[i];
	
    while (m--) {
        int k, u, v;
        io >> k >> u >> v;
        switch (k) {
        case 0:
            pick(u, v);
	    	printf("%d\n", o[u].v); 
	    	break;
        case 1:
            link(u, v); 
	    	break;
        case 2:
            cut(u, v); 
	    	break;
        case 3:
        	splay(u);
        	val[u] = v;
        	break;
        }
    }

    return 0;
}
