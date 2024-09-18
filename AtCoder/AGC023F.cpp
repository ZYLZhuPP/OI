#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef double lf;
const lf inf = 1e9;
const int N = 2e5 + 5;

struct IO {
	char c; int f;
#define gc() getchar()
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
		x *= f; return *this;
	}
	inline bool operator ~ () const { return ~c; }
} io;

int n, fa[N], pa[N], cnt[N][2], vis[N];
ll w[N];
priority_queue<pair<lf, int > > q;

inline int find(int x) { return pa[x]^x? pa[x] = find(pa[x]): x; }

inline void merge(int u, int v) {
    pa[v] = u;
    w[u] += w[v] + 1ll * cnt[u][1] * cnt[v][0];
    cnt[u][1] += cnt[v][1];
    cnt[u][0] += cnt[v][0];
    q.push({cnt[u][1]? 1.0 * cnt[u][0] / cnt[u][1]: inf, u});
}

int main() {
    io >> n;
    For (i, 2, n) io >> fa[i];
    For (i, 1, n) {
        int x;
        io >> x; cnt[i][x]++;
        q.push({cnt[i][1]? 1.0 * cnt[i][0] / cnt[i][1]: inf, i});
    }
    For (i, 1, n) pa[i] = i;
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        if (find(fa[u])) merge(pa[fa[u]], u);
    }
    printf("%lld", w[1]);

    return 0;
}
