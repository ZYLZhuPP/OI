#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

vector<int > G[N], T[N << 1];
int dfn[N], low[N], tim, tot, stk[N], top;

inline void Tarjan(int u) {
    dfn[u] = low[u] = ++tim; stk[++top] = u;
    for (auto &v : G[u])
        if (!dfn[v]) {
            Tarjan(v), cmin(low[u], low[v]);
            if (low[v] == dfn[u]) {
                T[++tot].pb(u); T[u].pb(tot);
                do T[tot].pb(stk[top]), T[stk[top]].pb(tot);
                while (stk[top--] ^ v);
            }
        } else cmin(low[u], dfn[v]);
}

inline void init(int n) {
    tim = 0; tot = n;
    For (i, 0, n) G[i].resize(0);
    For (i, 0, n << 1) T[i].resize(0);
    memset(dfn, 0, sizeof dfn);
}

int main() {

    return 0;
}
