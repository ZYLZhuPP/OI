#include<bits/stdc++.h>
#include"silent.h"
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 105;

int fa[N];

inline int find(int x) { return fa[x]^x? fa[x] = find(fa[x]): x; }

void solve(int n, char tp) {
    if (n == 1) return answer("1");
    iota(fa + 1, fa + n + 1, 1);
    vector<vector<bool > > vis(n + 1, vector<bool >(n + 1));
    For (_, 1, 10) {
        vector<int > rt, q(n), tot(n + 1), pt[n + 1];
        For (i, 1, n) {
            pt[find(i)].pb(i);
            if (fa[i] == i) rt.pb(i);
        }
        sort(rt.begin(), rt.end(), [&](const int &x, const int &y) { return pt[x].size() > pt[y].size(); });
        For (i, 0, (int)rt.size() - 1) For (j, i + 1, (int)rt.size() - 1) {
            int x = rt[i], y = rt[j];
            if (tot[x] == pt[x].size() || tot[y] == pt[y].size()) continue;
            bool flag = 0;
            for (auto &u : pt[x]) for (auto &v : pt[y]) flag |= vis[u][v];
            if (!flag) {
                int u = pt[x][tot[x]++], v = pt[y][tot[y]++];
                q[u - 1] = v, q[v - 1] = u;
            }
        }
        string res = query(q);
        for (auto &u : q) if (u) {
            int v = q[u - 1];
            if (u > v) continue;
            if (res[u - 1] & res[v - 1] & 1) fa[find(u)] = find(v);
            else vis[u][v] = vis[v][u] = 1;
        }
    }
    vector<int > sz(n + 1);
    For (i, 1, n) sz[find(i)]++;
    string res(n, '0');
    For (i, 1, n) if (2 * sz[find(i)] > n) res[i - 1] = '1';
    answer(res);
}
