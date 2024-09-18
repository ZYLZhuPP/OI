#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 11, S = 1 << 10, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }

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

int n, m, k, a[S][N], b[S][N], f[S], g[S], ans;
char s[N];

int main() {
    io >> n >> m >> k;
    For (i, 0, n - 1) {
        scanf("%s", s);
        For (j, 0, m - 1) {
            int c = s[j] ^ 48;
            a[1 << i][c] |= 1 << j;
            b[1 << j][c] |= 1 << i;
        }
    }
    For (s, 1, (1 << n) - 1) For (i, 1, 9) a[s][i] = a[s&-s][i] | a[s ^ (s&-s)][i];
    For (s, 1, (1 << m) - 1) For (i, 1, 9) b[s][i] = b[s&-s][i] | b[s ^ (s&-s)][i];
    f[(1 << n) - 1] = 1;
    while (k--) {
        memset(g, 0, sizeof g);
        For (s, 1, (1 << n) - 1) For (i, 1, 9) add(g[a[s][i]], f[s]);
        memset(f, 0, sizeof f);
        For (s, 1, (1 << m) - 1) For (i, 1, 9) add(f[b[s][i]], g[s]);
    }
    For (s, 1, (1 << n) - 1) add(ans, f[s]);
    printf("%d", ans);

    return 0;
}
