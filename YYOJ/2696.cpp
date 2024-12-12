#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int n, m, X, vis[N];
vector<int > L[N], R[N];

int main() {
    io >> n >> m >> X;
    int l, r;
    For (i, 1, m) {
        io >> l >> r;
        R[l].pb(r); L[r].pb(l);
        if (l < X) vis[l] = 1;
        if (r > X) vis[r] = 1;
    }
    l = r = X;
    For (i, 1, r) for (auto &x : R[i]) cmax(r, x);
    rFor (i, n, l) for (auto &x : L[i]) cmin(l, x);
    For (i, l, r) if (vis[i]) printf("%d ", i);

    return 0;
}
