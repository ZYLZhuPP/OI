#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

int n, m, u, v, Q, q, ans, s, a[N];

stack<int > st;
vector<int > G[N], T[N << 1];
int dfn[N << 1], low[N], tim, tot;
void Tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    st.push(u);
    for (auto &v : G[u])
        if (!dfn[v]) {
            Tarjan(v), low[u] = min(low[u], low[v]);
            if (low[v] == dfn[u]) {
                T[++tot].pb(u); T[u].pb(tot);
                T[tot].pb(v); T[v].pb(tot);
                while (st.top() ^ v)
                    T[tot].pb(st.top()), T[st.top()].pb(tot), st.pop();
                st.pop();
            }
        } else low[u] = min(low[u], dfn[v]);
}

int dep[N << 1], dis[N << 1], fa[18][N << 1];
void dfs(int u, int pre) {
    dfn[u] = ++tim; fa[0][u] = pre;
    dep[u] = dep[pre] + 1; 
    dis[u] = dis[pre] + (u <= n);
    For (i, 1, 17) fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for (auto &v : T[u]) if (v ^ pre) dfs(v, u);
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    rFor (i, 17, 0) if (dep[fa[i][u]] >= dep[v]) u = fa[i][u];
    if (u == v) return u;
    rFor (i, 17, 0) if (fa[i][u] ^ fa[i][v]) u = fa[i][u], v = fa[i][v];
    return fa[0][u];
}

void init(int n) {
    tim = 0; tot = n;
    For (i, 0, n) G[i].resize(0);
    For (i, 0, n << 1) T[i].resize(0);
    memset(dfn, 0, sizeof dfn);
    memset(dis, 0, sizeof dis);
    memset(fa, 0, sizeof fa);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> Q;
    while (Q--) {
        cin >> n >> m;
        init(n);
        For (i, 1, m) cin >> u >> v, G[u].pb(v), G[v].pb(u);
        Tarjan(1); st.pop();
        tim = 0; dfs(1, 0);
        cin >> q;
        while (q--) {
            ans = 0;
            cin >> s;
            For (i, 1, s) cin >> a[i];
            sort(a + 1, a + s + 1, [&](int x, int y) { return dfn[x] < dfn[y]; });
            For (i, 1, s) {
                u = a[i], v = a[i % s + 1];
                ans += dis[u] + dis[v] - 2 * dis[lca(u, v)];
            }
            cout << (ans / 2 + (lca(a[1], a[s]) <= n) - s) << endl;
        }
    }

    return 0;
}
