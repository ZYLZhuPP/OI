#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5;

int n, m, a, b, c1, c2, ans;

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
        int v;
        while ((v = st.top()) ^ u) pt[co[v] = con].push_back(v), st.pop();
        st.pop();
    }
}

void init(int n) {
    For (i, 0, n) es[i].resize(0);
    For (i, 1, con) pt[i].resize(0);
    tim = con = 0;
    memset(dfn, 0, sizeof dfn);
    memset(co, 0, sizeof co);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    while (cin >> n >> m) {
        ans = 1;
        init(n << 1);
        For (i, 1, m) {
            cin >> a >> b >> c1 >> c2;
            a = (a << 1) + c1; b = (b << 1) + c2;
            es[a].push_back(b ^ 1); es[b].push_back(a ^ 1);
        }
        For (i, 0, (n << 1) - 1) if (!dfn[i]) Tarjan(i);
        For (i, 0, n - 1) if (co[i << 1] == co[i << 1 | 1]) ans = 0;
        cout << (ans? "YES": "NO") << endl;
    }
    
    return 0;
}
