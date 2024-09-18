#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 505;

int n, m, e, u, v;

namespace Hungary {
    vector<int > es[N];
    int mch[N], vis[N], tim;
    bool dfs(int u) {
        for (auto &v : es[u]) if (vis[v] ^ tim) {
            vis[v] = tim;
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
            tim++;
            res += dfs(i);
        }
        return res;
    }
}
using namespace Hungary;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> e;
    while (e--) cin >> u >> v, es[u].emplace_back(v);
    cout << match(n);

    return 0;
}
