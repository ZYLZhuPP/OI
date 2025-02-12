#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)

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

int n, K;
vector<array<int, 2 > > a;

int main() {
    freopen("fraction.in", "r", stdin);
    freopen("fraction.out", "w", stdout);
    io >> n >> K;
    For (i, 2, n) For (j, 1, i - 1) if (__gcd(i, j) == 1) a.pb({j, i});
    sort(a.begin(), a.end(), [&](array<int, 2 > x, array<int, 2 > y) { return 1ll * x[0] * y[1] < 1ll * x[1] * y[0]; });
    printf("%d %d", a[K - 1][0], a[K - 1][1]);

    fclose(stdin); fclose(stdout);
    return 0;
}
