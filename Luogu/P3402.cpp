#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;

struct IO {
	static const int BufS = 1 << 20;
	char ibuf[BufS], *S, *T, c; int f;
#define gc() ((S==T && (T=(S=ibuf)+fread(ibuf, 1, BufS, stdin)), S==T)? EOF: *S++)
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
		x *= f; return *this;
	}
	inline IO& operator >> (char &x){
		while ((c = gc()) < 33 && ~c);
		x = c; return *this;
	}
	inline IO& operator >> (char *x){
		while ((c = gc()) < 33 && ~c);
		while (c > 32) *x++ = c, c = gc();
		*x = 0; return *this;
	}
	inline IO& operator >> (double &x){
		double p(1); x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = x * 10 + (c ^ 48), c = gc();
		if (!(c ^ 46)) while (isdigit(c = gc())) x += (c ^ 48) * (p /= 10);
		x *= f; return *this;
	}
	char obuf[BufS]; int E, st[66], t;
#define pc(c) (obuf[E==BufS && (E-=fwrite(obuf, 1, BufS, stdout)), E++]=c)
    inline void flush() {fwrite(obuf, 1, E, stdout);}
    ~IO() {flush();}
    template<class C>
    inline IO& operator << (C x) {
        if (!x) pc('0'); if (x < 0) pc('-'), x = -x;
        while (x) st[++t] = x % 10, x /= 10;
        while (t) pc(st[t--] ^ 48);
        return *this;
    }
    inline IO& operator << (char x) {
        pc(x); return *this;
    }
    template<class C>
    inline IO& operator << (C *x) {
        while (*x) pc(*x++);
        return *this;
    }
	inline bool operator ~ () const { return ~c; }
} io;

int n, m, fa[N], dep[N], ans[N], a[N], b[N], q[N];
vector<int > es[N];

inline int find(int u) { return fa[u]^u? find(fa[u]): u; }
inline void dfs(int u) {
    int fu = find(a[u]), fv = find(b[u]), d = dep[fu] == dep[fv];
    if (q[u]) ans[u] = fu == fv;
    else if (fu ^ fv) {
        if (dep[fu] < dep[fv]) swap(fu, fv);
        fa[fv] = fu; dep[fu] += d;
    }
    for (auto &v : es[u]) dfs(v);
    if (!q[u] && fu ^ fv) fa[fv] = fv, dep[fu] -= d;
}

int main() {
    io >> n >> m;
    For (i, 1, n) fa[i] = i;
    For (i, 1, m) {
        int op, x;
        io >> op;
        if (op == 1) {
            io >> a[i] >> b[i];
            es[i - 1].pb(i);
        } else if (op == 2) {
            io >> x;
            es[x].pb(i);
        } else if (op == 3) {
            io >> a[i] >> b[i];
            es[i - 1].pb(i); q[i] = 1;
        }
    }
    dfs(0);
    For (i, 1, m) if (q[i]) io << ans[i] << '\n';

    return 0;
}
