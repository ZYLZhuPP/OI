#include"tree.h"
#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;

int n, w[N], fa[N], pa[N], id[N], sz[N], vis[N];
ll cnt[N], s1[N], s2[N], S;
vector<int > T[N];

inline int find(int x) { return pa[x]^x? pa[x] = find(pa[x]): x; }
inline void add(int x, int d, int v) { cnt[sz[x]] -= v; cnt[sz[x] += d] += v; }
inline void merge(int x, int y, int v) { pa[y] = x; cnt[sz[y]] -= v; add(x, sz[y], v); }

inline void upd(int u) {
    vis[u] = 1;
    if (fa[u] && vis[fa[u]]) add(find(fa[u]), -1, w[u]);
    for (auto &v : T[u]) {
        if (!vis[v]) add(u, 1, w[u]);
        else merge(u, v, w[u]);
    }
    if (vis[fa[u]]) merge(find(fa[u]), u, w[u]);
}

void init(vector<int > P, vector<int > W) {
    n = W.size();
    For (i, 1, n) w[i] = W[i - 1], id[i] = i, pa[i] = i;
    For (i, 2, n) T[fa[i] = P[i - 1] + 1].pb(i);
    For (i, 1, n) if (T[i].empty()) T[i].pb(0), S += w[i];
    sort(id + 1, id + n + 1, [&](int x, int y) { return w[x] > w[y]; });
    For (i, 1, n) upd(id[i]);
    rFor (i, n, 1) s1[i] = s1[i + 1] + cnt[i], s2[i] = s2[i + 1] + i * cnt[i];
}

ll query(int L, int R) {
    int x = min(n, R / L) + 1;
    return S * L + s2[x] * L - s1[x] * R;
}
