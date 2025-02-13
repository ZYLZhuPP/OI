#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
inline bool cmax(int &x, const int &y) { return y>x? x=y, 1: 0; }
inline bool cmin(int &x, const int &y) { return y<x? x=y, 1: 0; }
const int N = 5e5 + 5, Mo = 1e9;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }
inline int ml(int x, int y) { return 1ll * x * y % Mo; }

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () const { return ~c; }
} io;

int n, ans;
int a[N], mn[N], mx[N], sn[N], sx[N], snp[N], sxp[N], sm[N], smp[N];

inline void cdq(int l, int r) {
    if (l == r) return add(ans, ml(a[l], a[l]));
    int m = (l + r) >> 1;
    cdq(l, m); cdq(m + 1, r);
    mn[m] = mx[m] = a[m + 1];
    sn[m] = sx[m] = snp[m] = sxp[m] = sm[m] = smp[m] = 0;
    For (i, m + 1, r) {
        cmin(mn[i] = mn[i - 1], a[i]); cmax(mx[i] = mx[i - 1], a[i]);
        add(sn[i] = sn[i - 1], mn[i]); add(sx[i] = sx[i - 1], mx[i]);
        add(snp[i] = snp[i - 1], ml(mn[i], i)); add(sxp[i] = sxp[i - 1], ml(mx[i], i));
        add(sm[i] = sm[i - 1], ml(mn[i], mx[i])); add(smp[i] = smp[i - 1], ml(ml(mn[i], mx[i]), i));
    }
    int p = m, q = m;
    int Mn = a[m], Mx = a[m];
    rFor (i, m, l) {
        cmin(Mn, a[i]); cmax(Mx, a[i]);
        while (p < r && mn[p + 1] >= Mn) p++;
        while (q < r && mx[q + 1] <= Mx) q++;
        int x = min(p, q);
        add(ans, ml(ml(Mx, Mn), 1ll * (m + x - 2 * i + 3) * (x - m) / 2 % Mo));
        if (p < q) add(ans, ml(Mx, mo(mo(snp[q] - snp[p]) - ml(i - 1, mo(sn[q] - sn[p])))));
        else add(ans, ml(Mn, mo(mo(sxp[p] - sxp[q]) - ml(i - 1, mo(sx[p] - sx[q])))));
        x = max(p, q);
        add(ans, mo(mo(smp[r] - smp[x]) - ml(i - 1, mo(sm[r] - sm[x]))));
    }
}

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    cdq(1, n);
    printf("%d", ans);

    return 0;
}
