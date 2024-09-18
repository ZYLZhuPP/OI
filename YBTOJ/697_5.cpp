#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 10, M = 2e3 + 5;

int n, m, tot, a[1 << N];
char s[N];

namespace Hungary {
    vector<int > es[M];
    int mch[M], vis[M];
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
    while (cin >> n >> m, m) {
        tot = 0;
        memset(a, 0, sizeof a);
        For (i, 1, m) {
            int x = 0, pos = -1;
            cin >> s;
            For (j, 0, n - 1) {
                if (s[j] == '1') x |= (1 << j);
                else if (s[j] == '*') pos = j;
            }
            a[x] = 1;
            if (~pos) a[x ^ (1 << pos)] = 1;
        }
        For (i, 0, (1 << n) - 1) if (a[i]) {
            a[i] = ++tot;
            es[tot].resize(0);
            For (j, 0, n - 1) if (i >> j & 1) {
                int x = i ^ (1 << j);
                if (a[x]) es[a[i]].push_back(a[x]), es[a[x]].push_back(a[i]);
            }
        }
        cout << tot - match(tot) / 2 << endl;
    }

    return 0;
}
