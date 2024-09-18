#include<bits/stdc++.h>
using namespace std;

#define mkp make_pair
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e6 + 5;

int n, R, C, x[N], y[N], t[N], ans, f[N], val[N], Val[N];
const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
map<pair<int, int >, int > mp;

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
        Val[con] = val[u];
        int v;
        while ((v = st.top()) ^ u) {
            pt[co[v] = con].push_back(v);
            Val[con] += val[v];
            st.pop();
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
    rFor (u, con, 1) {
        if (!f[u]) f[u] = Val[u];
        ans = max(ans, f[u]);
        for (auto &v : to[u]) {
            f[v] = max(f[v], f[u] + Val[v]);
            in[v]--;
        }
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> R >> C;
    For (i, 1, n) {
        cin >> x[i] >> y[i] >> t[i];
        val[i] = 1;
        mp[mkp(x[i], y[i])] = i;
    }
    For (i, 1, n) {
        es[n + x[i]].push_back(i);
        es[n + R + y[i]].push_back(i);
        if (t[i] == 1) es[i].push_back(n + x[i]);
        else if (t[i] == 2) es[i].push_back(n + R + y[i]);
        else {
            For (k, 0, 7) {
                int p = mp[mkp(x[i] + dx[k], y[i] + dy[k])];
                if (p) es[i].push_back(p);
            }
        }
    }
    For (i, 1, n + R + C) if (!dfn[i]) Tarjan(i);
    rebuild();
    solve();
    cout << ans;

    return 0;
}
