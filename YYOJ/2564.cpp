#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e4 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int Q, n, m, K, ans, tot, mx, a[N], b[N], f[N], g[N];

int main() {
    io >> Q;
    while (Q--) {
        ans = tot = mx = 0;
        io >> n >> m >> K;
        For (i, 1, n) {
            io >> a[i];
            cmax(mx, a[i]);
            if (a[i] <= m) b[++tot] = m + 1 - a[i];
        }
        sort(b + 1, b + tot + 1);
        if (K == n - 1) {
            ans = m + 1;
            For (i, 1, tot - 2) ans += b[i];
            printf("%d\n", max(ans, mx));
            continue;
        }
        n = tot;
        if (n <= 2) { printf("%d\n", mx); continue; }
        if (n <= 4) { printf("%d\n", max(m + 1, mx)); continue; }
        n -= 4;
        int S = 0;
        For (i, 1, n) S += b[i];
        int p = 1, s = 0;
        while (p <= n && s + b[p] <= S / 2) s += b[p++];
        For (i, 0, 2 * m) f[i] = 0;
        f[s - S / 2 + m] = p;
        For (i, p, n) {
            For (j, 0, 2 * m) g[j] = f[j];
            For (j, 0, m - 1) cmax(f[j + b[i]], g[j]);
            rFor (j, 2 * m, m + 1) For (k, g[j], f[j] - 1) cmax(f[j - b[k]], k);
        }
        rFor (i, m, 0) if (f[i]) { ans = S / 2 - (m - i); break; }
        printf("%d\n", max(mx, m + 1 + S - ans));
    }

    return 0;
}
