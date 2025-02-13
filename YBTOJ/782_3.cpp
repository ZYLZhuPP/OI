#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 505, M = 1e5 + 5, inf = 1e9;

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

namespace BIT {
    int o[N][N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, int y, const int &d) { for (int i = x; i < N; i += lowbit(i)) for (int j = y; j < N; j += lowbit(j)) o[i][j] += d; }
    inline int query(int x, int y) { int r = 0; for (int i = x; i; i -= lowbit(i)) for (int j = y; j; j -= lowbit(j)) r += o[i][j]; return r; }
}
using namespace BIT;

struct OP { int x, y, X, Y, k, id; };
vector<OP > ops;
int n, q, ans[M], op[M];

inline void solve(vector<OP > &o, int l, int r) {
    if (o.empty()) return;
    if (l == r) { for (auto &x : o) ans[x.id] = l; return; }
    int m = (l + r) >> 1;
    vector<OP > L, R;
    for (auto &[x, y, X, Y, k, id] : o) {
        if (op[id] == 1) {
            if (k <= m) upd(x, y, 1), L.pb({x, y, X, Y, k, id});
            else R.pb({x, y, X, Y, k, id});
        } else {
            int p = query(X, Y) - query(x - 1, Y) - query(X, y - 1) + query(x - 1, y - 1);
            if (k <= p) L.pb({x, y, X, Y, k, id});
            else R.pb({x, y, X, Y, k - p, id});
        }
    }
    o.resize(0);
    for (auto &[x, y, X, Y, k, id] : L) if (op[id] == 1) upd(x, y, -1);
    solve(L, l, m); solve(R, m + 1, r);
}

int main() {
    io >> n >> q;
    int x, y, X, Y, k;
    op[0] = 1; For (i, 1, n) For (j, 1, n) io >> x, ops.pb({i, j, i, j, x, 0});
    For (i, 1, q) io >> x >> y >> X >> Y >> k, ops.pb({x, y, X, Y, k, i}), op[i] = 2;
    solve(ops, 0, inf);
    For (i, 1, q) printf("%d\n", ans[i]);

    return 0;
}
