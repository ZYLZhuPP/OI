#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 205;

int n, g[N][N], m[2];
const int dx[8] = {-1, -2, 1, 2, -1, -2, 1, 2};
const int dy[8] = {-2, -1, -2, -1, 2, 1, 2, 1};
char s[N];

namespace Hungary {
    vector<int > es[N * N];
    int mch[N * N], vis[N * N];
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
    cin >> n;
    For (i, 1, n) {
        cin >> (s + 1);
        For (j, 1, n) if (s[j] == '0')
            g[i][j] = ++m[(i + j) & 1];
    }
    For (i, 1, n) For (j, 1, n) if (g[i][j] && (i + j) & 1) {
        For (k, 0, 7) {
            int x = i + dx[k], y = j + dy[k];
            if (x > 0 && x <= n && y > 0 && y <= n && g[x][y])
                es[g[i][j]].push_back(g[x][y]);
        }
    }
    cout << m[0] + m[1] - match(m[1]);

    return 0;
}
