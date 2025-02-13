#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 105;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int n, m, K, a[N][N], b[N][N][N], s[N][N], w[N], h[N], p[N], ans;

inline int push(int u, int x, int y) {
    int res = 0;
    For (i, x, x + w[u] - 1) For (j, y, y + h[u] - 1) res += a[i][j], b[u][i][j] = a[i][j], a[i][j] = 0;
    return res;
}

inline void back(int u, int x, int y) {
    For (i, x, x + w[u] - 1) For (j, y, y + h[u] - 1) a[i][j] = b[u][i][j];
}

inline int solve(int k, int r) {
    int res = r, u = p[k];
    if (k == 1) {
        For (i, 1, n) For (j, 1, m) {
            s[i][j] = a[i][j] + s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
            if (i >= w[u] && j >= h[u]) cmax(res, r + s[i][j] - s[i - w[u]][j] - s[i][j - h[u]] + s[i - w[u]][j - h[u]]);
        }
        return res;
    }
    cmax(res, solve(k - 1, r + push(u, n - w[u] + 1, 1))); back(u, n - w[u] + 1, 1);
    cmax(res, solve(k - 1, r + push(u, 1, m - h[u] + 1))); back(u, 1, m - h[u] + 1);
    For (o, 1, 4) {
        int i = rand() % (m - h[u] + 1) + 1;
        cmax(res, solve(k - 1, r + push(u, 1, i))); back(u, 1, i);
        cmax(res, solve(k - 1, r + push(u, n - w[u] + 1, i))); back(u, n - w[u] + 1, i);
        i = rand() % (n - w[u] + 1) + 1;
        cmax(res, solve(k - 1, r + push(u, i, 1))); back(u, i, 1);
        cmax(res, solve(k - 1, r + push(u, i, m - h[u] + 1))); back(u, i, m - h[u] + 1);
    }
    return res;
}

int main() {
    srand(time(0));
    io >> n >> m >> K;
    For (i, 1, K) io >> w[i];
    For (i, 1, K) io >> h[i];
    if (K == 1) return printf("%d", w[1] * h[1]), 0;
    if (K == 2) return printf("%d", w[1] * h[1] + w[2] * h[2] - max(0, w[1] + w[2] - n) * max(0, h[1] + h[2] - m)), 0;
    For (x, 1, K - 1) For (y, x + 1, K) {
        For (i, 1, n) For (j, 1, m) a[i][j] = 1;
        int res = push(x, 1, 1) + push(y, n - w[y] + 1, m - h[y] + 1);
        int tot = 0;
        For (i, 1, K) if (i ^ x && i ^ y) p[++tot] = i;
        For (i, 1, tot) swap(p[1], p[i]), cmax(ans, solve(tot, res));
    }
    printf("%d", ans);

    return 0;
}
