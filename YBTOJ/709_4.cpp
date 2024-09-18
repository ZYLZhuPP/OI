#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e5 + 5, Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }

int n, m, q, u, v, op, d;

stack<int > st;
vector<int > G[N], T[N << 1];
int dfn[N], low[N], tim, tot;
void Tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    st.push(u);
    for (auto &v : G[u])
        if (!dfn[v]) {
            Tarjan(v), low[u] = min(low[u], low[v]);
            if (low[v] == dfn[u]) {
                T[++tot].pb(u); T[u].pb(tot);
                T[tot].pb(v); T[v].pb(tot);
                while (st.top() ^ v)
                    T[tot].pb(st.top()), T[st.top()].pb(tot), st.pop();
                st.pop();
            }
        } else low[u] = min(low[u], dfn[v]);
}

void init(int n) {
    tim = 0; tot = n;
    For (i, 0, n) G[i].resize(0);
    For (i, 0, n << 1) T[i].resize(0);
    memset(dfn, 0, sizeof dfn);
}

namespace ZL {
    const int N = 6e5 + 5;
    int fa[N],  siz[N], dep[N];
    int son[N], top[N], pos[N], id[N], tim;
    int light[N];
    void dfs0(int u, int pre) {
        fa[u] = pre; siz[u] = 1;
        dep[u] = dep[pre] + 1;
        for (auto &v : T[u]) if (v ^ pre) {
            dfs0(v, u);
            if (siz[v] > siz[son[u]]) son[u] = v;
            siz[u] += siz[v];
        }
    }
    void dfs1(int u, int Top) {
        top[u] = Top; pos[u] = ++tim; id[tim] = u;
        if (son[u]) dfs1(son[u], Top);
        for (auto &v : T[u]) if (v ^ fa[u] && v ^ son[u])
            dfs1(v, v);
    }
    namespace Seg {
        struct Node {
            int c[2], v[2], t[2];
            Node(int x = 0) { c[x] = 1; c[x ^ 1] = v[0] = v[1] = t[0] = t[1] = 0; }
        } o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
        void mark(int p, int i, int d) { add(o[p].v[i], o[p].c[i] * d); add(o[p].t[i], d); }
        void down(int p) { for (int i : {0, 1}) if (o[p].t[i]) mark(ls, i, o[p].t[i]), mark(rs, i, o[p].t[i]), o[p].t[i] = 0; }
        void build(int p, int l, int r) {
            if (l == r) return void(o[p] = Node(id[l] > n));
            M; build(goL); build(goR);
        }
        void upd(int p, int l, int r, int x, int y, int i, int d) {
            if (l > y || r < x) return;
            if (x <= l && r <= y) return mark(p, i, d);
            down(p); M; upd(goL, x, y, i, d); upd(goR, x, y, i, d);
        }
        int query(int p, int l, int r, int x, int i) {
            if (l > x || r < x) return 0;
            if (l == r) return o[p].v[i];
            down(p); M; return query(goL, x, i) + query(goR, x, i);
        }
    }
    void upd(int u, int v, int i, int d) {
        int fu = top[u], fv = top[v];
        while (fu ^ fv) {
            if (dep[fu] < dep[fv]) swap(u, v), swap(fu, fv);
            Seg::upd(1, 1, tot, pos[fu], pos[u], i, d);
            if (i && fu > n) add(light[fa[fu]], d);
            u = fa[fu], fu =top[u];
        }
        if (dep[u] > dep[v]) swap(u, v);
        Seg::upd(1, 1, tot, pos[u], pos[v], i, d);
        if (i && u == top[u] && u > n) add(light[fa[u]], d);
    }
    int query(int u, int i) { return Seg::query(1, 1, tot, pos[u], i); }
}
using namespace ZL;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> q;
    init(n);
    For (i, 1, m) cin >> u >> v, G[u].pb(v), G[v].pb(u);
    Tarjan(1);
    dfs0(1, 0); dfs1(1, 1);
    Seg::build(1, 1, tot);
    while (q--) {
        cin >> op;
        if (op == 0) {
            cin >> u >> v >> d;
            upd(u, v, 1, d);
            upd(u, v, 0, mo(-d)); upd(u, u, 0, d); upd(v, v, 0, d);
        } else {
            cin >> u;
            cout << mo(mo(query(u, 0) + light[u]) + mo(query(son[u], 1) + query(fa[u], 1))) << endl;
        }
    }

    return 0;
}
