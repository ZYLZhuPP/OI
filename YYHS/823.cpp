#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e4 + 5;

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
ll a[N], x, sa[N], s[N], sum[N], f[N], g[N], X[N], Y[N];
int l, r, q[N];

int main() {
    io >> n >> m;
    For (i, 1, n) io >> a[i], sa[i] = sa[i - 1] + a[i];
    For (i, 2, n) io >> x, s[i] = s[i - 1] + x;
    For (i, 1, n) sum[i] = sum[i - 1] + a[i] * s[i];

    For (i, 1, m) {
        l = 1; r = 0;
        if (i > 1) For (j, 1, n) {
            ll K = s[j];
            X[j] = sa[j]; Y[j] = g[j] + sum[j];
            auto F = [&](int k) { return g[k] + (sa[j] - sa[k]) * s[j] - sum[j] + sum[k]; };
            
            while (l < r && 1.L * (Y[j] - Y[q[r]]) * (X[q[r]] - X[q[r - 1]]) <= 1.L * (Y[q[r]] - Y[q[r - 1]]) * (X[j] - X[q[r]])) r--;
            q[++r] = j;
            while (l < r && Y[q[l + 1]] - Y[q[l]] <= K * (X[q[l + 1]] - X[q[l]])) l++;
            f[j] = F(q[l]);
        } else For (j, 1, n) f[j] = sa[j] * s[j] - sum[j];
        
        l = 1; r = 0;
        For (j, 1, n) {
            ll K = sa[j];
            X[j] = s[j]; Y[j] = f[j] - sum[j] + sa[j] * s[j];
            auto F = [&](int k) { return f[k] + sum[j] - sum[k] - (sa[j] - sa[k]) * s[k]; };

            while (l < r && 1.L * (Y[j] - Y[q[r]]) * (X[q[r]] - X[q[r - 1]]) <= 1.L * (Y[q[r]] - Y[q[r - 1]]) * (X[j] - X[q[r]])) r--;
            q[++r] = j;
            while (l < r && Y[q[l + 1]] - Y[q[l]] <= K * (X[q[l + 1]] - X[q[l]])) l++;
            g[j] = F(q[l]);
        }
    }

    printf("%lld", g[n]);

    return 0;
}

