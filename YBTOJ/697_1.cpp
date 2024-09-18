#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 505;

int n, k, u, v;

namespace Hungary {
    vector<int > es[N];
    int mch[N]; bool vis[N];
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
            if (dfs(i)) res++;
        }
        return res;
    }
}
using namespace Hungary;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> k;
    For (i, 1, k) cin >> u >> v, es[u].emplace_back(v);
    cout << match(n);

    return 0;
}
