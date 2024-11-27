#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef unsigned long long ull;
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

inline ull rd() {
    static ull x = 1145141;
    return x ^= x << 13, x ^= x >> 7, x ^= x << 17;
}

int n, m, q;
ull w[N], a[N], s[N], S, ans;

int main() {
    io >> n >> m;
    For (i, 1, n) w[i] = rd(), S += w[i];
    int u, v;
    For (i, 1, m) io >> u >> v, s[v] += w[u];
    For (i, 1, n) a[i] = s[i], ans += s[i];
    io >> q;
    int op;
    while (q--) {
        io >> op;
        if (op == 1) io >> u >> v, a[v] -= w[u], ans -= w[u];
        else if (op == 2) io >> u, ans -= a[u], a[u] = 0;
        else if (op == 3) io >> u >> v, a[v] += w[u], ans += w[u];
        else if (op == 4) io >> u, ans += s[u] - a[u], a[u] = s[u];
        puts(ans==S? "YES": "NO");
    }

    return 0;
}
