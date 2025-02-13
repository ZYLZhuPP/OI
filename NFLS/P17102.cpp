#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
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

int n, a[N], f[N], g[N], s[N], L[N], ls[N], rs[N], q[N], mn[N];

inline void workL(int m, int r, int x) {
    int h = max(m + 1, mn[x]), t = min(r + 1, x + a[m]);
    if (h < t) add(g[h], f[x - 1]), add(g[t], -f[x - 1]);
}

inline void workR(int l, int m, int x) {
    int h = max(l - 1, x - a[m]), t = min(m - 1, L[x] - 1);
    if (h <= t) add(f[x], mo(s[t] - (h? s[h - 1]: 0)));
}

inline void solve(int l, int m, int r) {
    if (ls[m]) solve(l, ls[m], m - 1);
    workR(l, m, m); add(g[m], g[m - 1]), add(f[m], g[m]), s[m] = mo(s[m - 1] + f[m]);
    if (m - l + 1 < r - m) For (i, l, m) workL(m, r, i);
    else For (i, m + 1, r) workR(l, m, i);
    if (rs[m]) solve(m + 1, rs[m], r);
}

int main() {
    freopen("safpar.in", "r", stdin);
    freopen("safpar.out", "w", stdout);
    io >> n;
    For (i, 1, n) io >> a[i];
    int h = 1, t = 0;
    For (i, 1, n) {
        while (h <= t && a[i] <= a[q[t]]) t--;
        q[++t] = i;
        while (h < t && a[q[h + 1]] <= i - q[h]) h++;
        L[i] = max(min(q[h], i - a[q[h]] + 1), 0);
    }
    For (i, 0, n) mn[i] = n + 1;
    rFor (i, n, 1) mn[L[i]] = i;
    rFor (i, n - 1, 0) cmin(mn[i], mn[i + 1]);
    t = 0;
    For (i, 1, n) {
        while (t && a[i] >= a[q[t]]) ls[i] = q[t--];
        rs[q[t]] = i; q[++t] = i;
    }
    f[0] = s[0] = 1;
    solve(1, q[1], n);
    printf("%d", f[n]);

    fclose(stdin); fclose(stdout);
    return 0;
}
