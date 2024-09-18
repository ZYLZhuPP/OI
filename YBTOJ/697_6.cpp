#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 105;

int n, m, g[N][N], u, v;

namespace Hungary {
    vector<int > es[N];
    int mch[N], vis[N];
    bool dfs(int u) {
        for (auto &v : es[u]) if (!vis[v]) {
            vis[v] = 1;
            if (!mch[v] || dfs(mch[v])) {
                mch[v] = u;
                return 1;
            }
        }
        return 0;
    }
    int match(int n) {
        int res = 0;
        memset(mch, 0, sizeof mch);
        For (i, 1, n) {
            memset(vis, 0, sizeof vis);
            res += dfs(i);
        }
        return res;
    }
}
using namespace Hungary;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    For (i, 1, m) cin >> u >> v, g[u][v] = 1;
    For (k, 1, n) For (i, 1, n) if (g[i][k]) For (j, 1, n) g[i][j] |= g[k][j];
    For (i, 1, n) For (j, 1, n) if (g[i][j]) es[i].push_back(j);
    cout << n - match(n);

    return 0;
}
