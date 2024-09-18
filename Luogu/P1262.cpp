#include <bits/stdc++.h>
using namespace std;
int n, p, m;
int head[100010], from[200010], to[200010], nxt[200010], tot;
void add(int u, int v) {
    to[++tot] = v, from[tot] = u;
    nxt[tot] = head[u];
    head[u] = tot;
}
int dfn[100010], low[100010], idx;
int st[100010], top, ins[100010];
int scc[100010], scc_cnt;
int sz[100010];
int id[100010], cnt;
void dfs(int x) {
    dfn[x] = ++idx, low[x] = dfn[x];
    st[++top] = x, ins[x] = 1;
    for (int i = head[x]; i; i = nxt[i]) {
        if (!dfn[to[i]]) dfs(to[i]), low[x] = min(low[x], low[to[i]]);
        else if (ins[to[i]]) low[x] = min(low[x], dfn[to[i]]);
    }
    if (dfn[x] == low[x]) {
        scc_cnt++;
        while (st[top] != x) {
            scc[st[top]] = scc_cnt;
            id[++cnt] = st[top];
            ins[st[top]] = 0, top--;
            sz[scc_cnt]++;
        }
        scc[x] = scc_cnt;
        id[++cnt] = x;
        ins[x] = 0, top--;
        sz[scc_cnt]++;
    }
}
int din[100010];
int cost[100010];
bool can[100010];
int scc_cost[100010], scc_id[100010];
#define say 1
int main() {
    cin >> n >> p;
    for (int j = 1; j <= p; j++) {
        int i;
        cin >> i;
        cin >> cost[i];
        can[i] = say;
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
    }
    for (int i = 1; i <= n; i++) if (!dfn[i]) dfs(i);
    memset(scc_cost, 0x3f, sizeof scc_cost);
    for (int i = n; i >= 1; i--) {
        if (can[i] == say) scc_cost[scc[i]] = min(scc_cost[scc[i]], cost[i]);
        scc_id[scc[i]] = i;
    }
    for (int j = n; j >= 1; j--) {
        int u = id[j];
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (scc[u] == scc[v]) continue;
            if (din[scc[u]]>0 || scc_cost[scc[u]] < 0x3f3f3f3f) din[scc[v]]++;
        }
    }
    int id = 2e9, ans = 0;
    bool flag = 0;
    for (int i = scc_cnt; i >= 1; i--) {
        if (din[i]) continue;
        if (scc_cost[i] >= 0x3f3f3f3f) {
            flag = 1;
            id = min(id, scc_id[i]);
        }
        ans += scc_cost[i];
    }
    if (flag) cout << "NO\n" << id;
    else cout << "YES\n" << ans;
    return 0;
}

