#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5;

int n, m, u, v, ans;
char a, b;

vector<int > es[N], pt[N];
stack<int > st;
int dfn[N], low[N], tim, co[N], con;
void Tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    st.push(u);
    for (auto &v : es[u])
        if (!dfn[v]) Tarjan(v), low[u] = min(low[u], low[v]);
        else if (!co[v]) low[u] = min(low[u], dfn[v]);
    if (low[u] == dfn[u]) {
        pt[co[u] = ++con].push_back(u);
        int v;
        while ((v = st.top()) ^ u) pt[co[v] = con].push_back(v), st.pop();
        st.pop();
    }
}

void init(int n) {
    For (i, 0, n) es[i].resize(0);
    For (i, 1, con) pt[i].resize(0);
    tim = con = 0;
    memset(dfn, 0, sizeof dfn);
    memset(co, 0, sizeof co);
}

int main() {
    while (scanf("%d%d", &n, &m), n) {
        ans = 1;
        init(n << 1);
        For (i, 1, m) {
            scanf("%d%c %d%c", &u, &a, &v, &b);
            u = (u << 1) + (a == 'w');
            v = (v << 1) + (b == 'w');
            es[u].push_back(v ^ 1);
            es[v].push_back(u ^ 1);
        }
        es[1].push_back(0);
        For (i, 0, (n << 1) - 1) if (!dfn[i]) Tarjan(i);
        For (i, 0, n - 1) if (co[i << 1] == co[i << 1 | 1]) ans = 0;
        if (!ans) puts("bad luck");
        else {
            For (i, 1, n - 1)
                printf("%d%c ", i, co[i << 1] < co[i << 1 | 1]? 'w': 'h');
            puts("");
        }
    }

    return 0;
}
