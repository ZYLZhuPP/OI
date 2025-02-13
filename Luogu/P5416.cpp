#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e5 + 5;
const ll inf = 1e18;

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

struct OP { int l, r, id; };
vector<OP > ops, q;
int n, m, x[N], dfn[N], tim, opt[N], st[N];
ll c[N], ans[N];
vector<int > T[N];

namespace Seg {
    inline int dX(const int &i, const int &j) { return 2 * (x[i] - x[j]); }
    inline ll Y(const int &i) { return 1ll * x[i] * x[i] + c[i]; }
    inline ll dY(const int &i, const int &j) { return Y(i) - Y(j); }
    inline ll F(const int &i, const int &x0) { return 1ll * (x[i] - x0) * (x[i] - x0) + c[i]; }
    vector<int > o[N << 2];
    int pos[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void upd(int p, int l, int r, int x, int y, const int &id) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) {
            int t = (int)o[p].size() - 1;
            while (t > 0 && dY(id, o[p][t]) * dX(o[p][t], o[p][t - 1]) <= dY(o[p][t], o[p][t - 1]) * dX(id, o[p][t])) o[p].pop_back(), t--;
            return o[p].pb(id);
        }
        M; upd(goL, x, y, id); upd(goR, x, y, id);
    }
    inline ll query(int p, int l, int r, int x, const int &x0) {
        while (pos[p] < (int)o[p].size() - 1 && F(o[p][pos[p] + 1], x0) <= F(o[p][pos[p]], x0)) pos[p]++;
        ll res = o[p].size()? F(o[p][pos[p]], x0): inf;
        if (l == r) return res;
        M; return min(res, x<=m? query(goL, x, x0): query(goR, x, x0));
    }
}
using namespace Seg;

void dfs(int u) {
    dfn[u] = ++tim;
    int id = abs(opt[u]);
    if (opt[u] >= 0) st[id] = tim;
    else ops.pb({st[id], dfn[u] - 1, id});
    for (auto &v : T[u]) dfs(v);
    if (opt[u] >= 0) { if (tim >= st[id]) ops.pb({st[id], tim, id}); }
    else st[id] = tim + 1;
}

int main() {
    io >> n >> m >> c[0];
    For (i, 1, n - 1) {
        int op, fr, id, y, z;
        io >> op;
        if (op == 0) {
            io >> fr >> id >> x[id] >> y >> z >> c[id];
            T[fr].pb(i); opt[i] = id;
        } else if (op == 1) {
            io >> fr >> id;
            T[fr].pb(i); opt[i] = -id;
        }
    }
    dfs(0);
    sort(ops.begin(), ops.end(), [&](OP a, OP b) { return x[a.id] < x[b.id]; });
    for (auto &[l, r, id] : ops) upd(1, 1, n, l, r, id);

    int s, x0;
    For (i, 1, m) io >> s >> x0, q.pb({dfn[s], x0, i});
    sort(q.begin(), q.end(), [](OP a, OP b) { return a.r < b.r; });
    for (auto &[x, x0, id] : q) ans[id] = query(1, 1, n, x, x0);
    For (i, 1, m) printf("%lld\n", ans[i]);

    return 0;
}
