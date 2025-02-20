#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5;

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

int n, m, p[N], q[N];
ll a[N], b[N], s[N], t[N], ans;
vector<array<int, 2 > > ops[N];
map<int, ll > f;

inline void upd(int x, ll d) {
    for (auto it = f.lower_bound(x); d < 0; it = f.erase(it)) x = it->first, d += it->second;
    f[x] += d;
}

int main() {
    io >> n >> m;
    For (i, 1, n) io >> a[i] >> s[i] >> p[i], a[i] += a[i - 1];
    For (i, 1, m) io >> b[i] >> t[i] >> q[i], b[i] += b[i - 1];
    For (i, 1, n) if (s[i] >= a[i]) {
        int j = upper_bound(b + 1, b + m + 1, s[i] - a[i]) - b;
        ans += p[i];
        if (j <= m) ops[i].pb({j, -p[i]});
    }
    For (j, 1, m) if (t[j] >= b[j]) {
        int i = upper_bound(a + 1, a + n + 1, t[j] - b[j]) - a;
        if (i <= n) ops[i].pb({j, q[j]});
        else ans += q[j];
    }
    f[m + 1] = 1e18;
    For (i, 1, n) {
        sort(ops[i].begin(), ops[i].end(), [&](auto x, auto y) { return x[1] > y[1]; });
        for (auto &[j, d] : ops[i]) upd(j, d);
    }
    for (auto &[x, v] : f) if (x <= m) ans += v;
    printf("%lld", ans);

    return 0;
}