#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5, M = 5e5 +5;

int n, m, cnt, k[N], id[N], u[M], v[M], in[N], e_in[N];
int head[N], ver[M], Next[M], num;
int low[N], dfn[N], tot, st[N], tp;
int sum[N], poi[N], dis[N], maxn[N];
int e_head[N], e_ver[M], e_next[M], e_num;

void add(int u, int v) {
    ver[++num] = v;
    Next[num] = head[u];
    head[u] = num;
}

void e_add(int u, int v) {
    e_ver[++e_num] = v;
    e_next[e_num] = e_head[u];
    e_head[u] = e_num;
}

void tarjan(int u) {
    in[u] = 1;
    low[u] = dfn[u] = ++tot;
    st[++tp] = u;
    for (int i = head[u]; i; i = Next[i]) {
        int v = ver[i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        cnt++;
        while (st[tp + 1] != u) {
            int z = st[tp--];
            in[z] = 0;
            id[z] = cnt;
            sum[cnt] += k[z];
            poi[cnt] = max(poi[cnt], k[z]);
        }
    }
}

void topo() {
    queue<int> q;
    while (!q.empty()) {
        q.pop();
    }
    for (int i = 1; i <= cnt; i++) {
        dis[i] = sum[i];
        maxn[i] = poi[i];
        if (!e_in[i]) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = e_head[u]; i; i = e_next[i]) {
            int v = e_ver[i];
            if (dis[u] + sum[v] > dis[v]) {
                dis[v] = dis[u] + sum[v];
                maxn[v] = max(poi[v], maxn[u]);
            } else if (dis[u] + sum[v] == dis[v]) {
                maxn[v] = max(maxn[v], maxn[u]);
            }
            if (--e_in[v] == 0) {
                q.push(v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> k[i];
    for (int i = 1; i <= m; i++) cin >> u[i] >> v[i], add(u[i], v[i]);
    for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= m; i++) {
        if (id[u[i]] != id[v[i]]) {
            e_in[id[v[i]]]++;
            e_add(id[u[i]], id[v[i]]);
        }
    }
    topo();
    int nn = 0, mm = 0;
    for (int i = 1; i <= cnt; i++) {
        if (dis[i] > nn) {
            nn = dis[i];
            mm = maxn[i];
        } else if (dis[i] == nn) {
            mm = max(mm, maxn[i]);
        }
    }
    printf("%d %d", nn, mm);
    return 0;
}
