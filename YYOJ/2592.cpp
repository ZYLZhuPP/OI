#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }
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

int n, m, a[N], s[N];
vector<array<int, 3 > > b;

int main() {
    io >> n; m = n / 2;
    For (i, 1, n) io >> a[i], s[i] = s[i - 1] + a[i];
    For (i, 1, n) {
        int l = i, r = i + m - 1, x = 0;
        if (r <= n) x = s[r] - s[l - 1];
        else x = s[n] - s[l - 1] + s[r - n];
        b.pb({-x, l, r});
    }
    sort(b.begin(), b.end());
    int L = b[0][1], R = b[0][2];
    for (auto &[x, l, r] : b) {
        if ((R > n) != (r > n)) {
            if (R > n) swap(l, L), swap(r, R);
            if (l <= R) r = n;
            else l = 1, r -= n;
        }
        cmax(L, l); cmin(R, r);
        if (L > R) { printf("%d", s[n] + x); break; }
    }

    return 0;
}
