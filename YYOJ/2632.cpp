#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e5 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

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

ll T, n, a, b, c;
int ans;

int main() {
    io >> T;
    while (T--) {
        io >> n >> a >> b >> c; b %= c;
        if (!a) ans = ml(n, b);
        else {
            ans = 0;
            ll l = 1;
            while (l <= n) {
                ll x = (1ll * a * l + b) % c;
                ll d = min(n - l, (c - x - 1) / a);
                add(ans, ml(d + 1, x % Mo));
                add(ans, ml(d * (d + 1) / 2 % Mo, a));
                l += d + 1;
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}
