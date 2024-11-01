#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;
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

int n;
ll ans1, ans2;
bool vise[N], visf[N];
vector<array<int, 4 > > E, F;

inline bool ok(int m) {
    For (i, 1, n) vise[i] = visf[i] = 0;
    int e = 0, f = 0;
    ll se = ans1, sf = m;
    while (e < (int)E.size() || f < (int)F.size()) {
        if (e < (int)E.size() && E[e][0] <= se) {
            auto [x, de, df, id] = E[e];
            vise[id] = 1;
            if (visf[id]) se += de, sf += df;
            e++;
        } else if (f < (int)F.size() && F[f][0] <= sf) {
            auto [x, de, df, id] = F[f];
            visf[id] = 1;
            if (vise[id]) se += de, sf += df;
            f++;
        } else return 0;
    }
    return 1;
}

int main() {
    io >> n;
    int le, lf, e, f;
    For (i, 1, n) io >> le >> lf >> e >> f, E.pb({le, e, f, i}), F.pb({lf, e, f, i});
    sort(E.begin(), E.end()); sort(F.begin(), F.end());
    ll s = 0;
    for (auto &[x, e, f, id] : E) cmax(ans1, x - s), s += e;
    int l = 0, r = 1e9; ans2 = 1e9;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (ok(m)) ans2 = m, r = m - 1;
        else l = m + 1;
    }
    printf("%lld %lld", ans1, ans2);

    return 0;
}
