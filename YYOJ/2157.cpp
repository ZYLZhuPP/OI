#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef double lf;
const int N = 2e5 + 5;

struct IO {
	char c; int f;
#define gc() getchar()
	IO& operator >> (int &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
} io; 

int n, u, v, vis[N], w, rt;
lf ans, sq[N];
vector<int > es[N];

int sz[N], msz[N], dep[N], inq[N], fa[N], q[N];
int solve(int rt) {
    vis[rt] = 1;
    int h = 1, t = 0, s = 0; lf res = 0;
    sz[q[++t] = rt] = inq[rt] = 1; dep[rt] = 0;
    while (h <= t) {
        int u = q[h++];
        if (dep[u] < sq[s + 1] * w) res += sq[++s] * w - dep[u];
        else break;
        for (auto &v : es[u]) if (!inq[v]) {
            sz[q[++t] = v] = inq[v] = 1; dep[v] = dep[fa[v] = u] + 1;
        }
    }
    ans = max(ans, res);
    For (i, 1, t) inq[q[i]] = msz[q[i]] = 0;
    rFor (i, t, 1) {
        int u = q[i], f = fa[u];
        if (max(msz[u], t - sz[u]) <= t >> 1) return u;
        sz[f] += sz[u]; msz[f] = max(msz[f], sz[u]);
    }
}

int main() {
    srand(time(0));
    int ST = clock();
    io >> n >> w;
    For (i, 1, n) sq[i] = sqrt(i) - sqrt(i - 1);
    For (i, 1, n - 1) io >> u >> v, es[u].pb(v), es[v].pb(u);
    if (n <= 3000) For (i, 1, n) solve(i);
    else {
        while (clock() - ST <= 0.95 * CLOCKS_PER_SEC) {
            while (vis[rt = rand() % n + 1]);
            For (i, 1, 8) if (vis[rt = solve(rt)]) break;
        }
    }
    printf("%.2lf", ans);

    return 0;
}
