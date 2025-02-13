#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;

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


int n, m, fa[N], sz[N], w[N], ans, cnt;

inline int find(int u) { return u^fa[u]? find(fa[u]): u; }

void merge(int u, int v) {
    cnt++;
    int fu = find(u), fv = find(v);
    if (fu == fv) return;
    if (sz[fu] < sz[fv]) swap(u, v), swap(fu, fv);
    fa[fv] = fu; sz[fu] += sz[fv]; w[fv] = cnt;
}

int query(int u, int v) {
    if (find(u) ^ find(v)) return 0;
    int res = 0;
    while (u ^ v) {
        if (sz[u] > sz[v]) swap(u, v);
        res = max(res, w[u]);
        u = fa[u];
    }
    return res;
}

int main() {
    io >> n >> m;
    For (i, 1, n) fa[i] = i, sz[i] = 1;
    int op, u, v;
    while (m--) {
        io >> op >> u >> v;
        u ^= ans; v ^= ans;
        if (op == 0) merge(u, v);
        else if (op == 1) printf("%d\n", ans = query(u, v));
    }

    return 0;
}
