#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, M = 1e7 + 5;

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

int n, pri[N], psz, mip[N], ans[M], tot;

void init() {
    For (i, 2, N - 1) {
        if (!mip[i]) pri[mip[i] = ++psz] = i;
        For (j, 1, mip[i]) {
            if (i * pri[j] >= N) break;
            mip[i * pri[j]] = j;
        }
    }
}

inline bool isp(int n) {
    for (int i = 1; pri[i] * pri[i] <= n; ++i) if (!(n % pri[i])) return 0;
    return 1;
}

inline void dfs(int k, int n, int x) {
    if (n == 1) return ans[++tot] = x, void();
    if (pri[k] * pri[k] > n) {
        if (n > pri[k] && isp(n - 1)) ans[++tot] = x * (n - 1);
        return;
    }
    dfs(k + 1, n, x);
    for (int d = pri[k], s = d + 1; s <= n; s += (d *= pri[k])) if (!(n % s)) dfs(k + 1, n / s, x * d);
}

int main() {
    init();
    while (~(io >> n)) {
        tot = 0;
        dfs(1, n, 1);
        sort(ans + 1, ans + tot + 1);
        printf("%d\n", tot);
        For (i, 1, tot) printf("%d%c", ans[i], " \n"[i == tot]);
    }
}
