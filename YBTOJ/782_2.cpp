#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, inf = 1e9;

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
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, const int &d) { for (; x < N; x += lowbit(x)) o[x] += d; }
    inline int query(int x) { int r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
}
using namespace BIT;

struct OP { int x, y, k, id; };
vector<OP > ops;
int n, m, op[N], ans[N], a[N];

inline void solve(vector<OP > &o, int l, int r) {
    if (o.empty()) return;
    if (l == r) { for (auto &x : o) ans[x.id] = l; return; }
    int m = (l + r) >> 1;
    vector<OP > L, R;
    for (auto &[x, y, k, id] : o) if (op[id] == 1) {
        if (y <= m) upd(x, k), L.pb({x, y, k, id});
        else R.pb({x, y, k, id});
    } else {
        int p = query(y) - query(x - 1);
        if (k <= p) L.pb({x, y, k, id});
        else R.pb({x, y, k - p, id});
    }
    o.resize(0);
    for (auto &x : L) if (op[x.id] == 1) upd(x.x, -x.k);
    solve(L, l, m);
    solve(R, m + 1, r);
}

int main() {
    io >> n >> m;
    int l, r, k, x;
    op[0] = 1; For (i, 1, n) io >> a[i], ops.pb({i, a[i], 1, 0});
    For (i, 1, m) {
        char ch[3];
        scanf("%s", ch);
        op[i] = ch[0] == 'C'? 1: 2;
        if (op[i] == 1) io >> k >> x, ops.pb({k, a[k], -1, i}), ops.pb({k, a[k] = x, 1, i});
        else io >> l >> r >> k, ops.pb({l, r, k, i});
    }
    solve(ops, 0, inf);
    For (i, 1, m) if (op[i] == 2) printf("%d\n", ans[i]);

    return 0;
}
