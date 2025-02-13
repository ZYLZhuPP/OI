#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e3 + 5;

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

int T, n, W, ap[N], bp[N], as[N], bs[N];
ll f[N][N], f0[N], ans;
int q[N];

int main() {
    io >> T >> n >> W;
    For (i, 1, T) io >> ap[i] >> bp[i] >> as[i] >> bs[i];

    memset(f, -31, sizeof f); f[0][0] = 0;
    For (k, 1, T) {
        int k_ = max(0, k - W - 1);
        For (i, 0, n) f[k][i] = f[k - 1][i];

        int h = 1, t = 0; q[++t] = 0; f0[0] = f[k_][0];
        For (i, 1, n) {
            f0[i] = f[k_][i] + i * ap[k];
            while (h <= t && q[h] < i - as[k]) h++;
            f[k][i] = max(f[k][i], f0[q[h]] - i * ap[k]);
            while (h <= t && f0[q[t]] <= f0[i]) t--;
            q[++t] = i;
        }

        h = 1, t = 0; q[++t] = n; f0[n] = f[k_][n] + n * bp[k];
        rFor (i, n - 1, 0) {
            f0[i] = f[k_][i] + i * bp[k];
            while (h <= t && q[h] > i + bs[k]) h++;
            f[k][i] = max(f[k][i], f0[q[h]] - i * bp[k]);
            while (h <= t && f0[q[t]] <= f0[i]) t--;
            q[++t] = i;
        }
    }

    For (i, 0, n) ans = max(ans, f[T][i]);
    printf("%lld", ans);

    return 0;
}
