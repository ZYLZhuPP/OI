#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5, M = 1e4 + 5;

int n, m, x[M], y[M], z, ans, pos[N], T;

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

inline bool cross(int l, int r, int x, int y) {
    return (l < x && x < r && r < y) || (x < l && l < y && y < r);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> T;
    while (T--) {
        ans = 1;
        cin >> n >> m;
        For (i, 1, m) cin >> x[i] >> y[i];
        For (i, 1, n) cin >> z, pos[z] = i;
        if (m > 3 * n - 6) {
            puts("NO");
            continue;
        }
        init(m << 1 | 1);
        For (i, 1, m) {
            x[i] = pos[x[i]], y[i] = pos[y[i]];
            if (x[i] > y[i]) swap(x[i], y[i]);
        }
        For (i, 1, m) For (j, i + 1, m) if (cross(x[i], y[i], x[j], y[j])) {
            es[i << 1].push_back(j << 1 | 1);
            es[i << 1 | 1].push_back(j << 1);
            es[j << 1].push_back(i << 1 | 1);
            es[j << 1 | 1].push_back(i << 1);
        }
        For (i, 2, m << 1 | 1) if (!dfn[i]) Tarjan(i);
        For (i, 1, m) if (co[i << 1] == co[i << 1 | 1]) ans = 0;
        puts(ans? "YES": "NO");
    }

    return 0;
}
