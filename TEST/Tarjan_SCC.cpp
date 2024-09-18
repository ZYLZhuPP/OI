#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

vector<int > es[N], pt[N];
int dfn[N], low[N], tim, co[N], color, stk[N], top;

void Tarjan(int u) {
    dfn[u] = low[u] = ++tim; stk[++top] = u;
    for (auto &v : es[u])
        if (!dfn[v]) Tarjan(v), cmin(low[u], low[v]);
        else if (!co[v]) cmin(low[u], dfn[v]);
    if (low[u] == dfn[u]) {
        color++;
        do co[stk[top]] = color, pt[color].pb(stk[top]);
        while (stk[top--] ^ u);
    }
}

void init(int n) {
    For (i, 0, n) es[i].resize(0);
    For (i, 1, color) pt[i].resize(0);
    tim = color = 0;
    memset(dfn, 0, sizeof dfn);
    memset(co, 0, sizeof co);
}

vector<int > to[N];
int vis[N], in[N];
void rebuild() {
    int j;
    For (i, 1, color)
        for (auto &u : pt[i])
            for (auto &v : es[u]) if ((j = co[v]) ^ i && vis[j] ^ i)
                to[i].pb(j), in[j]++, vis[j] = i;
}

int main() {

    return 0;
}
