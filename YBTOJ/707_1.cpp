#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e4 + 5;

int n, m, u, v, ans;
int out[N];

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

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    For (i, 1, m) cin >> u >> v, es[u].push_back(v);
    For (i, 1, n) if (!dfn[i]) Tarjan(i);
    For (u, 1, n) for (auto &v : es[u]) if (co[u] ^ co[v]) out[co[u]]++;
    For (i, 1, color) if (!out[i]) {
        if (!ans) ans = pt[i].size();
        else { cout << 0; return 0; }
    }
    cout << ans;

    return 0;
}
