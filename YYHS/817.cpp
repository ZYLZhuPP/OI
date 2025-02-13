#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 1e3 + 5, T = 2e3 + 5;
const int Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }
inline int mul(int x, int y) { return 1ll * x * y % Mo; }

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
	inline bool operator ~ () {return ~c;}
} io;

int n, m, t, invm, g[N][T], h[N][T], invh[N][T], f[N][T], p[N][T], ans[N];

int qPow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = mul(res, a);
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

int main() {
    io >> n >> m >> t;
    t = min(t, n + m - 1);
    invm = qPow(m, Mo - 2);

    For (i, 1, n) For (j, 1, t) g[i][j] = (j<=m? invm: 0) + mul(g[i][j - 1], g[i - 1][j - 1]);
    For (i, 1, n) For (j, 1, t) h[i][j] = mo(1 - (j<t? g[i - 1][j]: 0)), invh[i][j] = qPow(h[i][j], Mo - 2);
    
    For (j, 1, t) f[1][j] = p[1][j] = j, add(ans[1], mul(f[1][j], mul(g[1][j], h[1][j])));

    For (i, 2, n) {
        For (j, 1, t) f[i][j] = j + mul(mo(ans[i - 1] - (j<t? mul(p[i - 1][j], g[i - 1][j]): 0)), invh[i][j]);
        rFor (j, t, 1) p[i][j] = i>1? mo(mul(f[i][j], h[i][j]) + mul(mo(1 - h[i][j]), p[i][j + 1])): j;
        For (j, 1, t) add(ans[i], mul(f[i][j], mul(g[i][j], h[i][j])));
    }

    printf("%d", ans[n]);
    
    return 0;
}
