#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 3e5 + 5;

int n, m, rt[N], a[N], frm[N], dep[N], fa[N], die[N], cnt[N];
ll x, v[N], hp[N];
vector<int > es[N];

namespace LT {
    struct Node {
        int l, r, d, id;
        ll v, ad, mu;
        Node() { l = r = v = d = ad = id = 0; mu = 1; }
    } o[N];
    int tot;
#define ls o[u].l
#define rs o[u].r
    void up(int u) { if (o[ls].d < o[rs].d) swap(ls, rs); o[u].d = o[rs].d + 1; }
    void mark(int u, ll ad, ll mu) { (o[u].v *= mu) += ad; o[u].mu *= mu; o[u].ad *= mu; o[u].ad += ad; }
    void down(int u) { if (o[u].ad || o[u].mu ^ 1) mark(ls, o[u].ad, o[u].mu), mark(rs, o[u].ad, o[u].mu), o[u].ad = 0, o[u].mu = 1; }
    int merge(int u, int v) {
        if (!u || !v) return u | v;
        if (o[v].v < o[u].v) swap(u, v);
        down(u); rs = merge(rs, v); up(u);
        return u;
    }
    void ins(int &u, ll x, int id) {
        int v = ++tot; o[v].v = x; o[v].id = id;
        u = merge(u, v);
    }
    void pop(int &u) {
        down(u); u = merge(ls, rs);
    }
}
using namespace LT;

void dfs(int u) {
    dep[u] = dep[fa[u]] + 1;
    for (auto &v : es[u]) dfs(v);
    while (rt[u] && o[rt[u]].v < hp[u]) {
        int i = o[rt[u]].id;
        cnt[i] = dep[frm[i]] - dep[u]; die[u]++;
        pop(rt[u]);
    }
    if (u ^ 1) {
        if (!a[u]) mark(rt[u], v[u], 1);
        else mark(rt[u], 0, v[u]);
        rt[fa[u]] = merge(rt[fa[u]], rt[u]);
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    For (i, 1, n) cin >> hp[i];
    For (i, 2, n) cin >> fa[i] >> a[i] >> v[i], es[fa[i]].push_back(i);
    For (i, 1, m) {
        cin >> x >> frm[i];
        ins(rt[frm[i]], x, i);
    }
    dfs(1);
    while (rt[1]) {
        int i = o[rt[1]].id;
        cnt[i] = dep[frm[i]];
        pop(rt[1]);
    }
    For (i, 1, n) cout << die[i] << endl;
    For (i, 1, m) cout << cnt[i] << endl;

    return 0;
}
