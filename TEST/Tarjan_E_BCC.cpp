#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

vector<int > G[N], pt[N];
int dfn[N], low[N], tim, co[N], con, stk[N], top;

void Tarjan(int u, int pre) {
    dfn[u] = low[u] = ++tim; stk[++top] = u;
    for (auto &v : G[u]) if (v ^ pre) {
        if (!dfn[v]) Tarjan(v, u), cmin(low[u], low[v]);
        else cmin(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        con++;
        do co[stk[top]] = con, pt[con].pb(stk[top]);
        while (stk[top--] ^ u);
    }
}

int fa[N];
void rebuild() {
    int j;
    For (i, 1, con)
        for (auto &u : pt[i]) for (auto &v : G[u])
            if ((j = co[v]) ^ i && j > i) fa[i] = j;
}

void init(int n) {
    For (i, 0, n) G[i].resize(0);
    For (i, 1, con) pt[i].resize(0);
    tim = con = 0;
    memset(dfn, 0, sizeof dfn);
    memset(co, 0, sizeof co);
}

int main() {

    return 0;
}
