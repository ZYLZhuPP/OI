#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 3e5 + 5;

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

struct OP {
    int x, y, t;
    bool operator < (const OP &a) const { return x^a.x? x<a.x: t>a.t; }
};
vector<OP > ops;

int n, m, k, p[N], ans[N], s[N];

inline void solve(vector<OP > &o, int l, int r) {
    if (o.empty()) return;
    if (l == r) { if (l <= k) for (auto &x : o) if (!x.t) ans[x.y] = l; return; }
    int m = (l + r) >> 1; ll S = 0;
    vector<OP > L, R;
    for (auto &x : o)
        if (x.t) { if (x.t <= m) S += x.y; }
        else s[x.y] = min(s[x.y] + S, (ll)p[x.y]);
    for (auto &x : o)
        if (x.t) { if (x.t <= m) L.pb(x); else R.pb(x); }
        else { if (p[x.y] <= s[x.y]) L.pb(x); else R.pb(x); }
    for (auto &x : o) if (!x.t) {
        if (p[x.y] > s[x.y]) p[x.y] -= s[x.y];
        s[x.y] = 0;
    }
    o.resize(0);
    solve(L, l, m); solve(R, m + 1, r);
}

int main() {
    io >> n >> m;
    int l, r, x;
    For (i, 1, m) io >> x, ops.pb({i, x, 0});
    For (i, 1, n) io >> p[i];
    io >> k;
    For (i, 1, k) {
        io >> l >> r >> x;
        if (l <= r) ops.pb({l, x, i}), ops.pb({r + 1, -x, i});
        else ops.pb({1, x, i}), ops.pb({r + 1, -x, i}), ops.pb({l, x, i});
    }
    sort(ops.begin(), ops.end());
    solve(ops, 1, k + 1);
    For (i, 1, n) if (ans[i]) printf("%d\n", ans[i]); else puts("NIE");

    return 0;
}
//Luogu SP10264
