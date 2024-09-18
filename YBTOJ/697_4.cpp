#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 105;

int n, m, tot, g[N][N], flag[N * N], ans;
const int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
char s[N];

namespace Hungary {
    vector<int > es[N * N];
    int mch[N * N], vis[N * N], tim;
    bool dfs(int u) {
        for (auto &v : es[u]) if (vis[v] ^ tim) {
            vis[v] = tim;
            if (!mch[v] || dfs(mch[v])) {
                mch[v] = u;
                mch[u] = v;
                return 1;
            }
        }
        return 0;
    }
    void find(int u) {
        flag[u] = 1;
        for (auto &v : es[u]) if (vis[v] ^ tim) {
            vis[v] = tim;
            if (mch[v]) find(mch[v]);
        }
    }
}
using namespace Hungary;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    For (i, 1, n) {
        cin >> (s + 1);
        For (j, 1, m) if (s[j] == '.')
            g[i][j] = ++tot;
    }
    For (i, 1, n) For (j, 1, m) if (g[i][j]) 
        For (k, 0, 3) {
            int x = i + dx[k], y = j + dy[k];
            if (x > 0 && x <= n && y > 0 && y <= m && g[x][y])
                es[g[i][j]].push_back(g[x][y]);
        }

    For (i, 1, n) For (j, 1, m) if (g[i][j] && (i + j) & 1) tim++, ans += dfs(g[i][j]);
    if (ans << 1 == tot) { puts("LOSE"); return 0; }
    else puts("WIN");
    For (i, 1, n) For (j, 1, m) if (g[i][j] && !mch[g[i][j]]) tim++, find(g[i][j]);

    For (i, 1, n) For (j, 1, m) if (flag[g[i][j]]) printf("%d %d\n", i, j);

    return 0;
}
