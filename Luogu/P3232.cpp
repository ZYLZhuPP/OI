#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 505;

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

int n, m, u, v;
long double a[N][N], b[N], ans;
vector<long double > c;
vector<int > es[N];

void Gauss() {
    For (i, 1, n) {
        int r = i;
        For (j, i + 1, n) if (fabs(a[j][i]) > fabs(a[r][i])) r = j;
        if (r ^ i) For (j, i, n + 1) swap(a[i][j], a[r][j]);
        long double o;
        For (j, 1, n) if (j ^ i) {
            o = a[j][i] / a[i][i];
            For (k, i, n + 1) a[j][k] -= a[i][k] * o;
        }
    }
    For (i, 1, n) b[i] = a[i][n + 1] / a[i][i];
}

int main() {
    io >> n >> m;
    For (i, 1, m) io >> u >> v, es[u].push_back(v), es[v].push_back(u);
    a[n][n] = a[1][n + 1] = 1;
    For (u, 1, n - 1) {
        a[u][u] = 1;
        for (auto &v : es[u]) if (v ^ n)
            a[u][v] = -1.L / es[v].size();
    }

    Gauss();

    For (u, 1, n)
        for (auto &v : es[u]) if (v > u)
            c.push_back(b[u] / es[u].size() + b[v] / es[v].size());
    sort(c.begin(), c.end());

    For (i, 0, m - 1) ans += c[i] * (m - i);
    printf("%.3Lf", ans);

    return 0;
}
