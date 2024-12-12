#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const ll inf = 1e18;
const int N = 1e5 + 5;

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
    int st[66], t;
#define pc(c) putchar(c)
    template<class C>
    inline IO& operator << (C x) {
        if (!x) pc('0'); if (x < 0) pc('-'), x = -x;
        while (x) st[++t] = x % 10, x /= 10;
        while (t) pc(st[t--] ^ 48);
        return *this;
    }
    inline IO& operator << (char x) {
        pc(x); return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int T, n, pos[N];
ll a[N << 1], f[N << 1], K;

inline ll F(int u, int x) {
    if (u << 1 >= n) {
        if (a[u << 1] < x) return f[u] = inf;
        return f[u] = (a[u << 1 | 1] < x) * a[u];
    }
    return f[u] = min(inf, F(u << 1, x) + min(a[u], F(u << 1 | 1, x)));
}

inline void dfs(int u) {
    int l = 1, r = n, res = 1;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (F(u, m) <= K) res = m, l = m + 1;
        else r = m - 1;
    }
    K -= F(u, res);
    int p = pos[res];
    io << a[p] << ' ' << a[p ^ 1] << ' ';
    for (p >>= 1; p ^ u; p >>= 1) {
        if (p & 1) K += f[p ^ 1];
        else if (f[p ^ 1] <= a[p >> 1]) K += f[p ^ 1];
        else if (K + a[p >> 1] >= f[p ^ 1]) K += a[p >> 1];
        dfs(p ^ 1);
    }
}

inline void solve() {
    io >> n >> K; n = 1 << n;
    For (i, 1, n - 1) io >> a[i];
    For (i, n, 2 * n - 1) io >> a[i], pos[a[i]] = i;
    dfs(1); io << '\n';
}

int main() {
    io >> T;
    while (T--) solve();

    return 0;
}
