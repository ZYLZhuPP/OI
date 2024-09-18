#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

int n, m, d, x[N], y[N];
char a[N], b[N], s[N];

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

char ch[3][2] = { {'B', 'C'}, {'C', 'A'}, {'A', 'B'} };
int id[3][3] = { {-1, 0, 1}, {1, -1, 0}, {0, 1, -1} };
bool solve() {
    init(n << 1 | 1);
    For (i, 1, m) {
        int u = x[i], v = y[i];
        if (a[i] == s[u] - 32) continue;
        int idu = u << 1 | id[s[u] - 'a'][a[i] - 'A'];
        if (b[i] == s[v] - 32) { es[idu].push_back(idu ^ 1); continue; }
        int idv = v << 1 | id[s[v] - 'a'][b[i] - 'A'];
        es[idu].push_back(idv);
        es[idv ^ 1].push_back(idu ^ 1);
    }
    For (i, 2, n << 1 | 1) if (!dfn[i]) Tarjan(i);
    For (i, 1, n) if (co[i << 1] == co[i << 1 | 1]) return 0;
    return 1;
}

bool dfs(int k) {
    if (k > n) return solve();
    if (s[k] ^ 'x') return dfs(k + 1);
    s[k] = 'a';
    if (dfs(k + 1)) return 1;
    s[k] = 'b';
    return dfs(k + 1);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> d;
    cin >> (s + 1);
    cin >> m;
    For (i, 1, m) cin >> x[i] >> a[i] >> y[i] >> b[i];
    if (!dfs(1)) { puts("-1"); return 0; }
    else
        For (i, 1, n) cout << ch[s[i] - 'a'][co[i << 1 | 1] < co[i << 1]];

    return 0;
}
