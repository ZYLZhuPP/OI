#include"swap.h"
#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 3e5 + 5;

struct Edge { int u, v, w; bool operator < (const Edge &a) const { return w < a.w; } } es[N];
vector<int > T[N], pt[N];

int pa[N];
int find(int x) { return x^pa[x]? pa[x] = find(pa[x]): x; }

int cir[N], st[N], ed[N], dep[N], rt[N], fa[N][20], nn;

void dfs(int u, int pre) {
    if (~pre) rt[u] = rt[pre], dep[u] = dep[pre] + 1;
    else rt[u] = u, dep[u] = 1;
    fa[u][0] = pre; For (i, 1, 19) fa[u][i] = ~fa[u][i - 1]? fa[fa[u][i - 1]][i - 1]: -1;
    for (auto &v : T[u]) dfs(v, u);
}

void init(int n, int m, vector<int > U, vector<int > V, vector<int > W) {
    nn = n;
    For (i, 0, m - 1) es[i] = (Edge){U[i], V[i], W[i]};
    sort(es, es + m);
    For (i, 0, n - 1) pa[i] = st[i] = ed[i] = i, pt[i].pb(i);
    For (i, 0, m - 1) {
        int u = es[i].u, v = es[i].v;
        int fu = find(u), fv = find(v);
        if (pt[fu].size() < pt[fv].size()) swap(fu, fv), swap(u, v);
        if (fu == fv) {
            if (!cir[fu]) {
                cir[fu] = 1;
                for (auto &u : pt[fu]) T[n + i].pb(u);
                rt[fu] = n + i;
            }
        } else {
            if (cir[fu] || cir[fv]) {
                if (cir[fu]) T[n + i].pb(rt[fu]);
                else for (auto &u : pt[fu]) T[n + i].pb(u);
                if (cir[fv]) T[n + i].pb(rt[fv]);
                else for (auto &u : pt[fv]) T[n + i].pb(u);
                pa[fv] = fu; cir[fu] = 1; rt[fu] = n + i;
            } else {
                if ((u==st[fu]||u==ed[fu])&&(v==st[fv]||v==ed[fv])) {
                    st[fu] = u^st[fu]^ed[fu]; ed[fu] = v^st[fv]^ed[fv];
                    for (auto &u : pt[fv]) pt[fu].pb(u);
                    pa[fv] = fu;
                } else {
                    cir[fu] = 1;
                    for (auto &u : pt[fu]) T[n + i].pb(u);
                    for (auto &u : pt[fv]) T[n + i].pb(u);
                    pa[fv] = fu; rt[fu] = n + i;
                }
            }
        }
    }
    rFor (u, n + m - 1, 0) if (!dep[u]) dfs(u, -1);
}

int getMinimumFuelCapacity(int u, int v) {
    if (rt[u] ^ rt[v]) return -1;
    if (dep[u] < dep[v]) swap(u, v);
    rFor (i, 19, 0) if (~fa[u][i] && dep[fa[u][i]] >= dep[v]) u = fa[u][i];
    rFor (i, 19, 0) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
    return es[fa[u][0] - nn].w;
}
