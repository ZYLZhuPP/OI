#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e3 + 5;

struct Node {
    int u, v, w;
} a[N];
int T, n, p, D, d[3], x, ans, cl[20];

namespace Hungary {
    struct Edge {
        int to, w;
    };
    vector<Edge > es[N];
    int mch[N], vis[N], tim;
    bool dfs(int u) {
        for (auto &e : es[u]) if (vis[e.to] ^ tim && !cl[e.w]) {
            int v = e.to; vis[v] = tim;
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

void dfs(int k, int t) {
    if (k > d[p]) return void(ans = min(ans, t + match(D)));
    cl[k] = 1; dfs(k + 1, t + 1);
    cl[k] = 0; dfs(k + 1, t);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> T;
    while (T--) {
        n = p = 0;
        cin >> d[0] >> d[1] >> d[2]; D = max(d[0], max(d[1], d[2]));
        For (i, 1, 2) if (d[i] < d[p]) p = i;
        For (i, 1, d[0]) For (j, 1, d[1]) For (k, 1, d[2]) {
            cin >> x;
            if (x) a[++n] = !p? Node{j, k, i}: p==2? Node{i, k, j}: Node{i, j, k};
        }
        ans = n;
        For (i, 1, D) es[i].resize(0);
        For (i, 1, n) {
            int u = a[i].u, v = a[i].v, w = a[i].w;
            es[u].push_back(Edge{v, w});
        }
        dfs(1, 0);
        cout << ans << endl;
    }

    return 0;
}
