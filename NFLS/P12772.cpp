#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
typedef long long ll;
const int N = 5e5 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int n, m, a[N], b[N], R, g[N], q[N];
ll f[N];

inline lf K(const int &i, const int &j) { return 1.0 * (f[i] - f[j]) / (b[j + 1] - b[i + 1]); }
inline void solve(const int &C) {
    int h = 1, t = 0;
    q[++t] = 0;
    For (i, 1, m) {
        while (h < t && K(q[h], q[h + 1]) < a[i]) h++;
        f[i] = f[q[h]] + 1ll * a[i] * b[q[h] + 1] - C; g[i] = g[q[h]] + 1;
        while (h < t && K(q[t - 1], q[t]) > K(q[t], i)) t--;
        q[++t] = i;
    }
}

inline ll WQS(int K) {
    int l = -1e9, r = 1e9, res = l;
    while (l <= r) {
        int mid = (l + r) >> 1;
        solve(mid);
        if (g[m] <= K) res = mid, l = mid + 1;
        else r = mid - 1;
    }
    solve(res);
    return f[m] + 1ll * g[m] * res;
}

int main() {
    freopen("group.in", "r", stdin);
    freopen("group.out", "w", stdout);
    io >> n >> R;
    int mx = 0, x;
    For (i, 1, n) {
        io >> x;
        if (cmax(mx, x)) a[++m] = x, b[m] = n - i + 1;
    }
    solve(0);
    printf("%lld", g[m]<=R? f[m]: WQS(R));

    fclose(stdin); fclose(stdout);
    return 0;
}
