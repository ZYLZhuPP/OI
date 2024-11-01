#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
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

int n, m, C, K, Q, a[N], cnt[N];
ll s[N], S[N];
vector<array<int, 3 > > ad[N];

namespace Seg {
    int mn[N << 2], o[N << 2][10], t[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void build(int p, int l, int r) {
        o[p][0] = r - l + 1;
        if (l == r) return;
        M; build(goL); build(goR);
    }
    inline void up(int p) {
        int u = ls, v = rs; if (mn[u] > mn[v]) swap(u, v);
        mn[p] = mn[u]; For (i, 0, K - 1) o[p][i] = o[u][i];
        int d = mn[v] - mn[u];
        For (i, 0, K - 1 - d) o[p][i + d] += o[v][i];
        mn[p] += t[p]; 
    }
    inline void upd(int p, int l, int r, int x, int y, int d) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mn[p] += d, t[p] += d, void();
        M; upd(goL, x, y, d); upd(goR, x, y, d); up(p);
    }
    inline int query() {
        int res = 0;
        For (i, 0, K - 1 - mn[1]) res += o[1][i];
        return res;
    }
}
using namespace Seg;

int main() {
    io >> n >> m >> C >> K >> Q;
    int x, y, X, Y;
    For (i, 1, C) io >> x >> y >> X >> Y, ad[x].pb({y, Y, 1}), ad[X + 1].pb({y, Y, - 1});
    build(1, 1, m);
    For (i, 1, n) {
        for (auto &[l, r, d] : ad[i]) upd(1, 1, m, l, r, d);
        a[i] = query(); a[i] = min(a[i], m - a[i]);
    }
    sort(a + 1, a + n + 1, greater<int >());
    For (i, 1, n) s[i] = s[i - 1] + a[i], S[i] = S[i - 1] + 1ll * a[i] * a[i], cnt[a[i]]++;
    rFor (i, m / 2, 0) cnt[i] += cnt[i + 1];
    while (Q--) {
        io >> X >> Y; y = Y / 2; x = min(X, cnt[y]);
        printf("%lld\n", 1ll * y * (Y - y) * x + Y * (s[X] - s[x]) - (S[X] - S[x]));
    }

    return 0;
}
