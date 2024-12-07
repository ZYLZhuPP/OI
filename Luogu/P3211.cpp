#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
const int N = 105;
const lf eps = 1e-8;

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

vector<pair<int, int > > G[N];
int n, m;
lf a[N][N], ans;

void Gauss(int n, int m) {
    int r; double x;
    For (i, 1, n) {
        r = i;
        For (j, i + 1, n) if (fabs(a[j][i]) > fabs(a[r][i])) r = j;
        swap(a[i], a[r]);
        if (fabs(a[i][i]) < eps) continue;
        x = a[i][i];
        For (j, i, n + m) a[i][j] /= x;
        For (j, 1, n) if (j ^ i){
            x = a[j][i];
            For (k, i, n + m) a[j][k] -= a[i][k] * x;
        }
    }
}

void solve(int k) {
    memset(a, 0, sizeof a);
    For (i, 1, n) a[i][i] = 1;
    For (u, 1, n - 1) for (auto &[v, w] : G[u])
        if (w >> k & 1) a[u][v] += 1.0 / G[u].size(), a[u][n + 1] += 1.0 / G[u].size();
        else a[u][v] -= 1.0 / G[u].size();
    Gauss(n, 1);
    ans += (1 << k) * a[1][n + 1];
}

int main() {
    io >> n >> m;
    int u, v, w;
    For (i, 1, m) { io >> u >> v >> w, G[u].pb({v, w}); if (u ^ v) G[v].pb({u, w}); }
    For (i, 0, 30) solve(i);
    printf("%.3lf", ans);

    return 0;
}
