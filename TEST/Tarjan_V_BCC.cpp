#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

vector<int > G[N], pt[N];
int n, m, dfn[N], low[N], tim, con, cut[N], stk[N], top;

void Tarjan(int u, int pre) {
    dfn[u] = low[u] = ++tim; stk[++top] = u;
    int cnt = 0;
    for (auto &v : G[u]) if (v ^ pre) {
        if (!dfn[v]) {
            ++cnt;
            Tarjan(v, u), cmin(low[u], low[v]);
            if ((!pre && cnt > 1) || (pre && dfn[u] <= low[v])) cut[u] = 1;
            if (dfn[u] <= low[v]) {
                pt[++con].push_back(u);
                do pt[con].pb(stk[top]);
                while (stk[top--] ^ v);
            }
        } else cmin(low[u], dfn[v]);
    }
    if (!pre && !cnt) pt[++con].push_back(u);
}

void init(int n) {
    For (i, 0, n) G[i].resize(0);
    For (i, 1, con) pt[i].resize(0);
    tim = con = 0;
    memset(dfn, 0, sizeof dfn);
    memset(cut, 0, sizeof cut);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    int u, v;
    For (i, 1, m) cin >> u >> v, G[u].push_back(v), G[v].push_back(u);
    For (i, 1, n) if (!dfn[i]) Tarjan(i, 0), top = 0;
    cout << con << endl;
    For (i, 1, con) {
        cout << pt[i].size() << " ";
        for (auto &u : pt[i]) cout << u << " ";
        cout << endl;
    }

    return 0;
}
