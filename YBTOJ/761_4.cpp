#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;

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
    For (i, 1, m) if (q[i]) puts(ans[i]? "1": "0");

    return 0;
}
