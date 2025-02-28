#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5, B = 200;

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

int n, g[N], m;
ll a[N];
array<ll, 2 > f[N][B];

int main() {
    io >> n;
    For (i, 1, n) io >> a[i], a[i] += a[i - 1];
    memset(f, -1, sizeof f);
    For (i, 1, n) {
        ll lst = 0, cnt = 0, ans = 0;
        int j = i; g[m = 1] = j;
        while (~j) {
            int k = g[++m] = lower_bound(a, a + j + 1, a[j] - lst) - a - 1;
            if (j - k < B && ~f[j][j - k][0]) {
                ans = f[j][j - k][0], cnt = f[j][j - k][1];
                break;
            }
            if (~k) lst = a[j] - a[k];
            j = k;
        }
        reverse(g + 1, g + m + 1);
        For (j, 2, m) {
            if (g[j] - g[j - 1] < B) f[g[j]][g[j] - g[j - 1]] = {ans, cnt};
            ans += (g[j] + 1) * ++cnt;
        }
        printf("%lld ", ans);
    }

    return 0;
}