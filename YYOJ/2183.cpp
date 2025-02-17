#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef __int128 lll;

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

int T, k, ans;
ll n;

inline lll qPow(lll a, int b) {
    lll r = 1;
    while (b) {
        if (b & 1) r *= a;
        a *= a;
        b >>= 1;
    }
    return r;
}

int main() {
    io >> T;
    while (T--) {
        ans = 0;
        io >> n >> k;
        if (k == 3) {
            For (a, 1, n) {
                if (1ll * a * a * a >= n) break;
                int x = round((-3.L * a * a + sqrt(3.L * a) * sqrt(4.L * n - 1.L * a * a * a)) / (6 * a));
                if (x > 0 && 3ll * a * x * (x + a) + 1ll * a * a * a == n) ans++;
            }
        } else {
            int r = 2, l = 1;
             while (l < r) {
                 while (qPow(r, k) - qPow(l, k) > n) l++;
                 if (l == r) break;
                 if (qPow(r, k) - qPow(l, k) == n) ans++;
                 r++;
            }
        }
        printf("%d\n", ans);
    }
    
    return 0;
}
