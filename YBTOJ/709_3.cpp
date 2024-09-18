#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }
inline int ml(int x, int y) { return 1ll * x * y % Mo; }
inline void mul(int &x, int y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r=1; for(;b;b>>=1,mul(a,a)) if(b&1) mul(r,a); return r; }

int n, m, u, v, ans, f[N][2];

stack<int > st;
vector<int > G[N], pt[N];
int dfn[N], low[N], tim, co[N], con;
void Tarjan(int u, int pre) {
    dfn[u] = low[u] = ++tim;
    st.push(u);
    for (auto &v : G[u]) if (v ^ pre) {
        if (!dfn[v]) Tarjan(v, u), low[u] = min(low[u], low[v]);
        else low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        pt[co[u] = ++con].pb(u);
        int v;
        while ((v = st.top()) ^ u) pt[co[v] = con].pb(v), st.pop();
        st.pop();
    }
}

int e[N], fa[N];
void rebuild() {
    int j;
    For (i, 1, con) {
        for (auto &u : pt[i]) for (auto &v : G[u])
            if ((j = co[v]) ^ i) {
                if (j > i) fa[i] = j;
            } else e[i]++;
        e[i] >>= 1;
    }
}

void solve() {
    For (i, 1, con)
        f[i][0] = qPow(2, e[i]), f[i][1] = qPow(2, e[i] + pt[i].size()) - f[i][0];
    For (u, 1, con - 1) {
        add(ans, ml(f[u][1], qPow(2, m - e[u] - 1)));
        int v = fa[u];
        e[v] += e[u] + 1;
        mul(f[v][1], mo(mo(f[u][0] << 1) + f[u][1]));
        add(f[v][1], ml(f[v][0], f[u][1]));
        mul(f[v][0], mo(f[u][0] << 1));
    }
    add(ans, f[con][1]);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    For (i, 1, m) cin >> u >> v, G[u].pb(v), G[v].pb(u);
    Tarjan(1, 0);
    rebuild();
    solve();
    cout << ans;

    return 0;
}
