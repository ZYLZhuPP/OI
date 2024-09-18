#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5;

int n, m, u, v, vis[N];
vector<int > es[N];
char a, b;
string ans;

void dfs(int u) {
    vis[u] = 1;
    for (auto &v : es[u]) if (!vis[v]) dfs(v);
}

bool ok(int x) {
    memset(vis, 0, sizeof vis);
    dfs(x);
    For (i, 1, n) if (vis[i << 1] && vis[i << 1 | 1]) return 0;
    return 1;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    For (i, 1, m) {
        cin >> u >> a >> v >> b;
        u = (u << 1) + (a == 'Y');
        v = (v << 1) + (b == 'Y');
        es[u ^ 1].push_back(v);
        es[v ^ 1].push_back(u);
    }
    For (i, 1, n) {
        int x = ok(i << 1), y = ok(i << 1 | 1);
        if (!x && !y) return puts("IMPOSSIBLE"), 0;
        else if (x && !y) ans += "N";
        else if (!x && y) ans += "Y";
        else ans += '?';
    }
    cout << ans;

    return 0;
}
