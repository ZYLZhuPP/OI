#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
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

int n, m, h[N], x[N], y[N], c[N];
int fa[N][18], ls[N], rs[N], dfn[N], dfn_[N], tim, stk[N], top;
ll f[N], sum;
vector<int > pt[N];

namespace BIT {
    ll o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int k, const ll &d) {
        for (; k <= n; k += lowbit(k)) o[k] += d;
    }
    inline ll query(int k) {
        ll r = 0;
        for (; k; k -= lowbit(k)) r += o[k];
        return r;
    }
}
using namespace BIT;

void dfs(int u, int pre) {
    if (!u) return;
    dfn[u] = ++tim; fa[u][0] = pre;
    For (i, 1, 17) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    dfs(ls[u], u); dfs(rs[u], u);
    dfn_[u] = tim;
}

int getpos(int x, int y) {
    rFor (i, 17, 0) if (h[fa[x][i]] < y) x = fa[x][i];
    return x;
}

void solve(int u) {
    if (!u) return;
    int l = ls[u], r = rs[u];
    solve(l); solve(r);
    if (l) upd(dfn[l], f[r]), upd(dfn_[l] + 1, -f[r]);
    if (r) upd(dfn[r], f[l]), upd(dfn_[r] + 1, -f[l]);
    f[u] = f[ls[u]] + f[rs[u]];
    for (auto &i : pt[u]) f[u] = max(f[u], query(dfn[x[i]]) + c[i] + f[ls[x[i]]] + f[rs[x[i]]]);
//    cout << f[u] << endl;
}

int main() {
    io >> n;
    h[0] = n + 1;
    For (i, 1, n) {
        io >> h[i];
        while (top && h[stk[top]] < h[i]) top--;
        ls[i] = rs[stk[top]]; rs[stk[top]] = i;
        stk[++top] = i;
    }
    dfs(stk[1], 0);
    io >> m;
    For (i, 1, m) {
        io >> x[i] >> y[i] >> c[i]; sum += c[i];
        pt[getpos(x[i], y[i])].pb(i);
    }
    solve(stk[1]);
    printf("%lld", sum - f[stk[1]]);

    return 0;
}
