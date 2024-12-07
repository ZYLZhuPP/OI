#include<bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef pair<int, int > P;
const int N = 1e5 + 5;

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

int n, m, K;

namespace DSU {
    int fa[N << 1], sz[N << 1], top;
    P stk[N << 1];
    inline int find(int x) { return fa[x]^x? fa[x] = find(fa[x]): x; }
    inline void merge(int x, int y) {
        if (sz[x] < sz[y]) swap(x, y);
        stk[++top] = P(x, y);
        fa[y] = x; sz[x] += sz[y];
    }
    inline void undo(int t) {
        while (top > t) {
            int x = stk[top].st, y = stk[top].nd;
            fa[y] = y; sz[x] -= sz[y];
            top--;
        }
    }
}
using namespace DSU;

namespace Seg {
    vector<P > o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void upd(int p, int l, int r, int x, int y, const P &v) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return o[p].pb(v);
        M; upd(goL, x, y, v); upd(goR, x, y, v);
    }
    inline void solve(int p, int l, int r, int flag) {
        int t = top;
        for (auto [u, v] : o[p]) {
            if (find(u) == find(v)) flag = 0;
            else merge(find(u), find(v + n)), merge(find(u + n), find(v));
        }
        if (l == r) puts(flag? "Yes": "No");
        else { M; solve(goL, flag); solve(goR, flag); }
        undo(t);
    }
}
using namespace Seg;

int main() {
    io >> n >> m >> K;
    while (m--) {
        int u, v, l, r;
        io >> u >> v >> l >> r;
        upd(1, 1, K, l + 1, r, P(u, v));
    }
    For (i, 1, 2 * n) fa[i] = i, sz[i] = 1;
    solve(1, 1, K, 1);

    return 0;
}
