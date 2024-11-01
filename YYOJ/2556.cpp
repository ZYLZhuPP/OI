#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const ll INF = 1e18;
const int N = 1e6 + 5, K = 1e6;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, m;
ll A[N], B[N], ans[N];
vector<array<int, 2 > > qmn[N], qmx[N];

namespace Seg {
    ll k[N << 3], b[N << 3];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline ll F(ll k, ll b, int x) { return k * x + b; }
    inline void upd_mn(int p, int l, int r, ll x, ll y) {
        M; if (F(x, y, m) < F(k[p], b[p], m)) swap(k[p], x), swap(b[p], y);
        if (F(x, y, l) < F(k[p], b[p], l)) upd_mn(goL, x, y);
        if (F(x, y, r) < F(k[p], b[p], r)) upd_mn(goR, x, y);
    }
    inline ll query_mn(int p, int l, int r, int x) {
        if (l > x || r < x) return INF;
        if (l == r) return F(k[p], b[p], x);
        M; return min(F(k[p], b[p], x), min(query_mn(goL, x), query_mn(goR, x)));
    }
    inline void upd_mx(int p, int l, int r, ll x, ll y) {
        M; if (F(x, y, m) > F(k[p], b[p], m)) swap(k[p], x), swap(b[p], y);
        if (F(x, y, l) > F(k[p], b[p], l)) upd_mx(goL, x, y);
        if (F(x, y, r) > F(k[p], b[p], r)) upd_mx(goR, x, y);
    }
    inline ll query_mx(int p, int l, int r, int x) {
        if (l > x || r < x) return -INF;
        if (l == r) return F(k[p], b[p], x);
        M; return max(F(k[p], b[p], x), max(query_mx(goL, x), query_mx(goR, x)));
    }
}
using namespace Seg;

int main() {
    io >> n >> m;
    int x, y;
    For (i, 1, n) io >> x >> y, A[i] = A[i - 1] + x, B[i] = B[i - 1] + y;
    For (i, 1, m) io >> x >> y, qmn[x - 1].pb({y, i}), qmx[x].pb({y, i});
    memset(b, 127, sizeof b);
    For (i, 0, n) {
        upd_mn(1, -K, K, -B[i], A[i]);
        for (auto &[k, id] : qmn[i]) ans[id] -= query_mn(1, -K, K, k);
    }
    memset(k, 0, sizeof k);
    memset(b, 128, sizeof b);
    rFor (i, n, 0) {
        upd_mx(1, -K, K, -B[i], A[i]);
        for (auto &[k, id] : qmx[i]) ans[id] += query_mx(1, -K, K, k);
    }
    For (i, 1, m) printf("%lld\n", ans[i]);

    return 0;
}
