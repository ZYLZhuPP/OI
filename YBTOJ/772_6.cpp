#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef double lf;
const int N = 2e5 + 5;

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

int n, t, fa[N], p[N], cnt;
ll q[N], s[N], l[N], dis[N], Dis[N], f[N];
vector<int > es[N];

inline lf K(int x, int y) { return 1.l * (f[x] - f[y]) / (dis[x] - dis[y]); }

struct Stk {
    int *o, *top, *v, tp;
    Stk() { o = top = v = nullptr; }
    Stk(int s) { o = new int[s]; top = new int[s]; v = new int[s]; o[0] = top[0] = tp = 0; }
    void push(int u) {
        int t = top[tp];
        while (t > 1 && K(u, o[t]) < K(o[t], o[t - 1])) t--;
        t++; tp++; v[tp] = o[t]; top[tp] = t; o[t] = u;
    }
    void pop() {
        o[top[tp]] = v[tp];
        tp--;
    }
    int find(int x) {
        int l = 1, r = top[tp] - 1, res = top[tp];
        while (l <= r) {
            int m = (l + r) >> 1;
            if (K(o[m + 1], o[m]) > x) res = m, r = m - 1;
            else l = m + 1;
        }
        return o[res];
    }
};

namespace BIT {
#define lowbit(x) ((x) & -(x))
    Stk o[N];
    void init() { For (i, 1, N - 1) o[i] = Stk(lowbit(i)); }
    inline void ins(int k, int x) { for (; k < N; k += lowbit(k)) o[k].push(x); }
    inline void del(int k) { for (; k < N; k += lowbit(k)) o[k].pop(); }
}
using namespace BIT;

void solve(int u) {
    int v = lower_bound(Dis + 1, Dis + cnt + 1, dis[u] - l[u]) - Dis;
    for (int k = N - v; k; k -= lowbit(k)) {
        v = o[k].find(p[u]);
        if (v) f[u] = min(f[u], f[v] + (dis[u] - dis[v]) * p[u] + q[u]);
    }
}

void dfs(int u) {
    dis[u] = dis[fa[u]] + s[u];
    Dis[++cnt] = dis[u];
    if (u ^ 1) solve(u);
    ins(N - cnt, u);
    for (auto &v : es[u]) dfs(v);
    del(N - cnt);
    cnt--;
}

int main() {
    init();
    memset(f, 31, sizeof f); f[1] = 0;
    io >> n >> t;
    For (i, 2, n) io >> fa[i] >> s[i] >> p[i] >> q[i] >> l[i], es[fa[i]].pb(i);
    dfs(1);
    For (i, 2, n) printf("%lld\n", f[i]);

    return 0;
}
