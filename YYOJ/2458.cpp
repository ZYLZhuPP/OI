#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e4 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }

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

int T, ans[N], S[2][N], a[N], b[N], fac[N], ivf[N];
vector<int > F, R;
vector<array<int, 3 > > qs[N];

int main() {
    io >> T;
    int n, m, k;
    For (i, 1, T) io >> n >> m >> k, qs[k].pb({n, m, i}), F.pb(n), F.pb(m), R.pb(m + k), R.pb(n);

    sort(F.begin(), F.end()); sort(R.begin(), R.end());
    int x = 1, p = 0;
    For (i, 0, 2e7) { if (i) mul(x, i); while (p < 2 * T && F[p] == i) fac[p++] = x; }
    x = qPow(x, Mo - 2); p = 2 * T - 1;
    rFor (i, 2e7, 0) { while (p >= 0 && R[p] == i) ivf[p--] = x; mul(x, i); }

    S[0][0] = 1;
    For (k, 0, 5000) {
        if (k) { S[k&1][0] = 0; For (i, 1, k) S[k&1][i] = mo(S[!(k&1)][i - 1] + ml(i, S[!(k&1)][i])); }
        for (auto &[n, m, id] : qs[k]) {
            a[0] = fac[lower_bound(F.begin(), F.end(), n) - F.begin()];
            For (i, 1, k) a[i] = ml(a[i - 1], n + i);
            b[k] = ivf[lower_bound(R.begin(), R.end(), m + k) - R.begin()];
            rFor (i, k, 1) b[i - 1] = ml(b[i], m + i);
            int x = 1;
            For (i, 0, k) add(ans[id], ((k-i)&1? -1: 1) * ml(ml(S[k&1][i], x), ml(a[i], b[i]))), mul(x, m + i);
            mul(ans[id], ml(fac[lower_bound(F.begin(), F.end(), m) - F.begin()], ivf[lower_bound(R.begin(), R.end(), n) - R.begin()]));
        }
    }

    For (i, 1, T) printf("%d\n", ans[i]);

    return 0;
}
