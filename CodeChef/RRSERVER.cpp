#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 22, S = 1 << 20;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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
	inline bool operator ~ () { return ~c; }
} io;

int n, m, g[N][N], cnt[S], f[S];

int main() {
    io >> n >> m;
    int u, v;
    For (i, 1, m) io >> u >> v, g[u][v] = g[v][u] = 1;
    For (s, 0, (1 << n) - 1) {
        For (i, 1, n) if (!(s >> (i - 1) & 1)) {
            int s_ = s ^ (1 << (i - 1)), x = cnt[s];
            For (j, 1, n) {
                if (s >> (j - 1) & 1) x -= g[i][j];
                if (!(s_ >> (j - 1) & 1)) x += g[i][j];
            }
            cnt[s_] = x;
        } else break;
    }
    memset(f, 31, sizeof f);
    f[0] = 0;
    For (s, 0, (1 << n) - 1) {
        For (i, 1, n) if (!(s >> (i - 1) & 1)) {
            int s_ = s ^ (1 << (i - 1));
            cmin(f[s_], f[s] + cnt[s]);
        }
    }
    printf("%d", f[(1 << n) - 1]);

    return 0;
}
