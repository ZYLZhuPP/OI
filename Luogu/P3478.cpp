#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5;
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

int n, sz[N];
ll f[N];
vector<int > T[N];
pair<ll, int > ans;

int dfs(int u, int pre, int dep) {
    sz[u] = 1;
    ll ret = dep;
    for(int &v : T[u]) if (v ^ pre) {
        ret += dfs(v, u, dep + 1);
        sz[u] += sz[v];
    }
    return ret;
}

void dfs(int u, int pre) {
    cmax(ans, {f[u], u});
    for(int &v : T[u]) if (v ^ pre) {
        f[v] = f[u] + n - (sz[v] << 1);
        dfs(v, u);
    }
}

int main() {
    io >> n;
    int u, v;
    For (i, 1, n - 1) io >> u >> v, T[u].pb(v), T[v].pb(u);
    f[1] = dfs(1, 0, 1);
    dfs(1, 0);
    printf("%d", ans.second);
    return 0;
}