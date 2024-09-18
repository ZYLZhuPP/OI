#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 505;

int T, n, h, m, a[N], b[N], c[N], d[N], st[N], ed[N];

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
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        For (i, 1, n) {
            scanf("%02d:%02d %d %d %d %d", &h, &m, &a[i], &b[i], &c[i], &d[i]);
            st[i] = h * 60 + m;
            ed[i] = st[i] + abs(a[i] - c[i]) + abs(b[i] - d[i]);
            es[i].resize(0);
        }
        For (i, 1, n) For (j, 1, n)
            if (ed[i] + abs(a[j] - c[i]) + abs(b[j] - d[i]) < st[j])
                es[i].push_back(j);
        printf("%d\n", n - match(n));
    }

    return 0;
}
