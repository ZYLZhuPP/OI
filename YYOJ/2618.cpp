#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 3e5 + 5;
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

namespace BIT {
    ll s[N]; int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, int w, int d) { for (; x < N; x += lowbit(x)) s[x] += w, o[x] += d; }
    inline ll query(int x, int w) { ll r = 0; for (; x; x -= lowbit(x)) r += s[x] + 1ll * o[x] * w; return r; }
}
using namespace BIT;

int n, dis[N], d[3][N], A[N], B[N], C[N];
vector<array<int, 4 > > op;
ll ans;

inline void get1(int d[], int l, int r, int k) {
    d[r] = 0;
    rFor (i, r - 1, l) {
        d[i] = d[i + 1] + A[i];
        if (i + 2 <= r) cmin(d[i], d[i + 2] + B[i]);
        if (i + 3 <= r) cmin(d[i], d[i + 3] + C[i]);
        if (k) ans += d[i];
    }
}

inline void get2(int d[], int l, int r, int k) {
    d[l] = 0;
    For (i, l + 1, r) {
        d[i] = d[i - 1] + A[i - 1];
        if (i - 2 >= l) cmin(d[i], d[i - 2] + B[i - 2]);
        if (i - 3 >= l) cmin(d[i], d[i - 3] + C[i - 3]);
        if (k) ans += d[i];
    }
}

inline void calc() {
    vector<int > a;
    for (auto &[x, y, k, w] : op) a.pb(y);
    sort(a.begin(), a.end()); unique(a.begin(), a.end());
    for (auto &[x, y, k, w] : op) y = lower_bound(a.begin(), a.end(), y) - a.begin() + 1;
    sort(op.begin(), op.end());
    for (auto &[x, y, k, w] : op) if (!k) upd(y, w, 1); else ans += query(y, w);
    for (auto &[x, y, k, w] : op) if (!k) upd(y, -w, -1);
    op.resize(0);
}

inline void solve(int l, int r) {
    if (r - l <= 4) {
        For (i, l + 1, r) get1(dis, l, i, 1);
        return;
    }
    int m = (l + r) >> 1;
    solve(l, m - 2); solve(m + 2, r);
    get1(d[0], l, m - 1, 1); get2(d[0], m - 1, r, 0);
    get1(d[1], l, m, 1); get2(d[1], m, r, 1);
    get1(d[2], l, m + 1, 0); get2(d[2], m + 1, r, 1);
    rFor (i, r, m + 1) op.pb({d[0][i] - d[1][i], d[0][i] - d[2][i], 0, d[0][i]});
    For (i, l, m - 1) op.pb({d[1][i] - d[0][i], d[2][i] - d[0][i], 1, d[0][i]});
    calc();
    rFor (i, r, m + 1) op.pb({d[1][i] - d[0][i], d[1][i] - d[2][i], 0, d[1][i]});
    For (i, l, m - 1) op.pb({d[0][i] - d[1][i] - 1, d[2][i] - d[1][i], 1, d[1][i]});
    calc();
    rFor (i, r, m + 1) op.pb({d[2][i] - d[0][i], d[2][i] - d[1][i], 0, d[2][i]});
    For (i, l, m - 1) op.pb({d[0][i] - d[2][i] - 1, d[1][i] - d[2][i] - 1, 1, d[2][i]});
    calc();
}

int main() {
    io >> n;
    For (i, 1, n - 1) io >> A[i];
    For (i, 1, n - 2) io >> B[i];
    For (i, 1, n - 3) io >> C[i];
    solve(1, n);
    printf("%lld", ans);

    return 0;
}
