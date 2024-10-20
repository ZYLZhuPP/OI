#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e7 + 5;
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

int n, X, Y, Z, m[2], c[N], top, cnt[N];
ll ans, stk[N];

int main() {
    io >> n >> X >> Y >> Z >> m[0] >> m[1] >> c[0] >> c[1];
    ll x = 0; stk[++top] = x;
    For (i, 0, n - 1) {
        if (i > 1) c[i] = (1ll * c[i - 1] * X + 1ll * c[i - 2] * Y + Z) % m[i & 1] + 1;
        if (i & 1) {
            ll y = x - c[i], z = stk[1];
            while (top && stk[top] > y) ans += cnt[top--];
            if (top && stk[top] == y) ans += cnt[top]++;
            else stk[++top] = y, cnt[top] = y > z;
            ans += x - max(z, y); x = y;
        } else x += c[i];
    }
    printf("%lld", ans);

    return 0;
}
