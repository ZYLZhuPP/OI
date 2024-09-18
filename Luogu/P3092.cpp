#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;
inline bool cmax(int &x, const int &y) { return y>x? x=y, 1: 0; }

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

int K, n, sum, w[20], a[N], g[20][N], f[1 << 16], h[1 << 16], ans = -1;

int main() {
    io >> K >> n;
    For (i, 1, K) io >> w[i], sum += w[i];
    For (i, 1, n) io >> a[i];
    For (i, 1, K) {
        int r = 0, s = 0;
        For (l, 0, n) {
            s -= a[l];
            while (r < n && s + a[r + 1] <= w[i]) s += a[++r];
            g[i][l] = r;
        }
    }
    For (s, 0, (1 << K) - 1) {
        For (i, 1, K) if (!(s >> (i - 1) & 1)) {
            int s_ = s | (1 << (i - 1));
            if (cmax(f[s_], g[i][f[s]])) h[s_] = h[s] + w[i];
        }
        if (f[s] == n) cmax(ans, sum - h[s]);
    }
    printf("%d", ans);

    return 0;
}
