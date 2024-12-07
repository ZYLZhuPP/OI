#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5;

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
    inline bool operator ~ () { return ~c; }
} io;

int T, n, vis[N], k[N];

int main() {
    io >> T;
    while (T--) {
        io >> n;
        For (i, 1, n - 1) vis[i] = k[i] = 0;
        vis[0] = 1;
        For (i, 1, n - 1) {
            ll x;
            io >> x;
            while (!vis[k[x] * x % n] || vis[(k[x] + 1) * x % n]) k[x]++;
            vis[(k[x] + 1) * x % n] = 1;
            printf("%lld %lld %lld\n", k[x] * x % n, (k[x] + 1) * x % n, x);
        }
    }

    return 0;
}