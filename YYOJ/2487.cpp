#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
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

int T, tot;
ll n, _[60], ans, K, m, A, B;

int main() {
    io >> T;
    while (T--) {
        ans = 1e18;
        io >> n >> K >> m >> A >> B;
        if (K == 1) { puts(n%m? "-1": "0"); continue; }
        _[tot = 0] = 1; while (_[tot] < m) _[tot + 1] = _[tot] * K, tot++;
        ans = tot * A;
        For (i, 0, 60) {
            int x = n % m;
            For (j, 0, tot - 1) if ((m - x * _[j] % m) % m <= _[j] - 1) { cmin(ans, i * B + j * A); break; }
            if (!n) break;
            n /= K;
        }
        printf("%lld\n", ans);
    }

    return 0;
}
