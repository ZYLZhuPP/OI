#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 105;

int n, x, a, b;

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
int vis[N], in[N], out[N];
void rebuild() {
    For (i, 1, con)
        for (auto &u : pt[i])
            for (auto &v : es[u]) if (co[v] ^ i && vis[co[v]] ^ i)
                to[i].push_back(co[v]), out[i]++, in[co[v]]++, vis[co[v]] = i;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    For (i, 1, n) while (cin >> x, x) es[i].push_back(x);
    For (i, 1, n) if (!dfn[i]) Tarjan(i);
    rebuild();
    For (i, 1, con) a += !in[i], b += !out[i];
    cout << a << endl;
    cout << (con == 1? 0: max(a, b));

    return 0;
}
