#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e5 + 5;

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

int n, m, q, a[N], b[N];
ll S, s;
set<ll > se;

inline ll query() {
    auto a = se.lower_bound(-S), b = a!=se.begin()? prev(a): a;
    if (a == se.end()) a = b;
    return min(abs(*a + S), abs(*b + S));
}

int main() {
    io >> n >> m >> q;
    For (i, 1, n) io >> a[i], S += (i&1? 1: -1) * a[i];
    For (i, 1, m) io >> b[i];
    For (i, 1, n) s += (i&1? -1: 1) * b[i];
    se.insert(s);
    For (i, 1, m - n) s = -s - b[i] + (n&1? -1: 1) * b[i + n], se.insert(s);
    printf("%lld\n", query());
    int l, r, v;
    while (q--) {
        io >> l >> r >> v;
        if (l > r) swap(l, r);
        if ((r - l + 1) & 1) S += (l&1? 1: -1) * v;
        printf("%lld\n", query());
    }

    return 0;
}
