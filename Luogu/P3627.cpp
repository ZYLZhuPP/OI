#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;

int n, m, u, v, ans, f[N], S, P;
int isp[N], isP[N], val[N], Val[N];

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
        Val[con] = val[u]; isP[con] = isp[u];
        while (st.top() ^ u) {
            int v = st.top(); st.pop();
            pt[co[v] = con].push_back(v);
            Val[con] += val[v]; isP[con] |= isp[st.top()];
        }
        st.pop();
    }
}

vector<int > to[N];
int vis[N], in[N];
void rebuild() {
    int j;
    For (i, 1, con)
        for (auto &u : pt[i])
            for (auto &v : es[u]) if ((j = co[v]) ^ i && vis[j] ^ i) 
                to[i].push_back(j), in[j]++, vis[j] = i;
}

void solve() {
    f[co[S]] = Val[co[S]];
    rFor (u, co[S], 1) {
        if (isP[u]) ans = max(ans, f[u]);
        for (auto &v : to[u]) {
            f[v] = max(f[v], f[u] + Val[v]);
            in[v]--;
        }
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    For (i, 1, m) cin >> u >> v, es[u].push_back(v);
    For (i, 1, n) cin >> val[i];
    cin >> S >> P;
    For (i, 1, P) cin >> u, isp[u] = 1;
    Tarjan(S);
    rebuild();
    solve();
    cout << ans << endl;

    return 0;
}
