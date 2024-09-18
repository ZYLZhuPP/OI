#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;

int n, m, u, v, siz[N << 1];
ll ans;

stack<int > st;
vector<int > G[N], T[N << 1];
int dfn[N], low[N], tim, tot;
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

void init(int n) {
    tim = 0; tot = n;
    For (i, 0, n) G[i].resize(0);
    For (i, 0, n << 1) T[i].resize(0);
    memset(dfn, 0, sizeof dfn);
}

void dfs(int u, int pre) {
    siz[u] = u <= n;
    int w = u<=n? -1: T[u].size();
    for (auto &v : T[u]) if (v ^ pre) {
        dfs(v, u);
        ans += 2ll * w * siz[u] * siz[v];
        siz[u] += siz[v];
    }
    ans += 2ll * w * siz[u] * (tim - siz[u]);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    init(n);
    For (i, 1, m) cin >> u >> v, G[u].pb(v), G[v].pb(u);
    For (i, 1, n) if (!dfn[i]) {
        tim = 0;
        Tarjan(i); st.pop();
        dfs(i, 0);
    }
    cout << ans;

    return 0;
}
