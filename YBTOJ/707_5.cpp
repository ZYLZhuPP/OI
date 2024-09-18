#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 4e3 + 5;

int n, m;
string x, y;
unordered_map<string, int > a, b;

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

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n;
    For (i, 1, n) {
        cin >> x >> y;
        a[x] = b[y] = i;
    }
    cin >> m;
    For (i, 1, m) {
        cin >> x >> y;
        es[a[x]].push_back(b[y]);
    }
    For (i, 1, n) if (!dfn[i]) Tarjan(i);
    For (i, 1, n) cout << (pt[co[i]].size() > 1? "Unsafe\n": "Safe\n");

    return 0;
}
