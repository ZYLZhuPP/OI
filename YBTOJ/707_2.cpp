#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

int n, m, u, v, ans, sum, Mo, dis[N], f[N];

vector<int > es[N], pt[N];
stack<int > st;
int dfn[N], low[N], tim, co[N], con;
void Tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    st.push(u);
    for (auto &v : es[u]) 
        if (!dfn[v]) Tarjan(v), low[u] = min(low[u], low[v]);
        else if (!co[v]) low[u] = min(low[u], dfn[v]);
    if (low[u] == dfn[u]) {
        pt[co[u] = ++con].push_back(u);
        while (st.top() ^ u) pt[co[st.top()] = con].push_back(st.top()), st.pop();
        st.pop();
    }
}

vector<int > to[N];
int vis[N], in[N];
void rebuild() {
    For (i, 1, con)
        for (auto &u : pt[i])
            for (auto &v : es[u]) if (co[v] ^ i && vis[co[v]] ^ i)
                to[i].push_back(co[v]), in[co[v]]++, vis[co[v]] = i;
}

void solve() {
    queue<int > q;
    For (i, 1, con) if (!in[i]) dis[i] = pt[i].size(), f[i] = 1, q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ans = max(ans, dis[u]);
        for (auto &v : to[u]) {
            if (dis[v] < dis[u] + pt[v].size()) {
                dis[v] = dis[u] + pt[v].size();
                f[v] = f[u];
            } else if (dis[v] == dis[u] + pt[v].size())
                (f[v] += f[u]) %= Mo;
            in[v]--;
            if (!in[v]) q.push(v);
        }
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> Mo;
    For (i, 1, m) cin >> u >> v, es[u].push_back(v);
    For (i, 1, n) if (!dfn[i]) Tarjan(i);
    rebuild();
    solve();
    For (i, 1, con) if (dis[i] == ans) (sum += f[i]) %= Mo;
    cout << ans << endl;
    cout << sum;

    return 0;
}
