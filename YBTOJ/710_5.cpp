#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 3e3 + 5, Mo = 59393;

int n, k, a[11], g[N], f[N], pre[N], d[N];

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> k;
    For (i, 0, k) cin >> a[i];
    For (i, 0, n) {
        g[i] = a[k];
        rFor (j, k - 1, 0) g[i] = (g[i] * i + a[j]) % Mo;
    }
    f[0] = g[1] * n;
    For (i, 1, n - 2) For (j, i, n - 2) {
        if (f[j] < f[j - i] + g[i + 1] - g[1]) {
            f[j] = f[j - i] + g[i + 1] - g[1];
            pre[j] = i;
        }
    }
    if (n == 1) return printf("0 %d", g[0]), 0;
    if (n == 2) return printf("1 %d\n1 2", g[1] * 2), 0;
    printf("%d %d\n", n - 1, f[n - 2]);
    int t = 0;
    for (int i = n - 2; i; i -= pre[i]) d[++t] = pre[i];
    for (int i = 1, p = t + 1; i <= t; ++p) {
        while (p <= n && d[p]) p++;
        printf("%d %d\n", i, p);
        while (i <= t && !--d[i] && i < p) printf("%d %d\n", i, i<t? i+1: n), ++i;
    }

    return 0;
}
