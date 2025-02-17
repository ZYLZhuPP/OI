#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5;
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

int n, q[N], m;
ll f[N];
array<int, 2 > a[N], b[N];

int main() {
    freopen("elevator.in", "r", stdin);
    freopen("elevator.out", "w", stdout);
    io >> n;
    For (i, 1, n) io >> a[i][0] >> a[i][1];
    sort(a + 1, a + n + 1);
    For (i, 1, n) {
        while (m && a[i][1] >= b[m][1]) m--;
        b[++m] = a[i];
    }
    int p = 0, l = 1, r = 0;
    q[++r] = 0;
    For (i, 1, m) {
        while (p + 1 < i && f[p + 1] <= b[i][0]) p++;
        f[i] = b[i][0] + 2ll * b[p + 1][1];
        while (l <= r && q[l] <= p) l++;
        if (l <= r) cmin(f[i], f[q[l]] + 2 * b[q[l] + 1][1]);
        while (l <= r && f[i] + 2 * b[i + 1][1] <= f[q[r]] + 2 * b[q[r] + 1][1]) r--;
        q[++r] = i;
    }
    printf("%lld", f[m]);

    fclose(stdin); fclose(stdout);
    return 0;
}
