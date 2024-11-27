#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5, inf = 2e9;
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

int n, m, q, lg[N];
int amx[N][25], amn[N][25], afx[N][25], azn[N][25];
int bmx[N][25], bmn[N][25];

int main() {
    io >> n >> m >> q;
    For (i, 2, max(n, m)) lg[i] = lg[i >> 1] + 1;
    int x;
    For (i, 1, n) {
        io >> x;
        amx[i][0] = amn[i][0] = x;
        afx[i][0] = (x < 0 ? x : -inf);
        azn[i][0] = (x >= 0 ? x : inf);
    }

    For (i, 1, m) {
        io >> x;
        bmx[i][0] = bmn[i][0] = x;
    }   

    For (j, 1, lg[n]) {
        For (i, 1, n - (1 << j) + 1) {
            int p = i + (1 << (j - 1));
            amx[i][j] = max(amx[i][j - 1], amx[p][j - 1]);
            afx[i][j] = max(afx[i][j - 1], afx[p][j - 1]);
            amn[i][j] = min(amn[i][j - 1], amn[p][j - 1]);
            azn[i][j] = min(azn[i][j - 1], azn[p][j - 1]);
        }
    }

    For (j, 1, lg[m]) {
        For (i, 1, m - (1 << j) + 1) {
            int p = i + (1 << (j - 1));
            bmx[i][j] = max(bmx[i][j - 1], bmx[p][j - 1]);
            bmn[i][j] = min(bmn[i][j - 1], bmn[p][j - 1]);
        }
    }

    int la, ra, lb, rb;
    while (q--) {
        io >> la >> ra >> lb >> rb;
        int sa = lg[ra - la + 1], sb = lg[rb - lb + 1];
        int pa = ra - (1 << sa) + 1, pb = rb - (1 << sb) + 1;

        int amax = max(amx[la][sa], amx[pa][sa]);
        int amin = min(amn[la][sa], amn[pa][sa]);
        int afmx = max(afx[la][sa], afx[pa][sa]);
        int azmn = min(azn[la][sa], azn[pa][sa]);
        int bmax = max(bmx[lb][sb], bmx[pb][sb]);
        int bmin = min(bmn[lb][sb], bmn[pb][sb]);

        ll ans = -2e18;

        cmax(ans, 1ll * amax * (amax >= 0 ? bmin : bmax));
        cmax(ans, 1ll * amin * (amin >= 0 ? bmin : bmax));
        if (afmx > -inf) cmax(ans, 1ll * afmx * (afmx >= 0 ? bmin : bmax));
        if (azmn < inf) cmax(ans, 1ll * azmn * (azmn >= 0 ? bmin : bmax));
        printf("%lld\n", ans);
    }
    
    return 0;
}