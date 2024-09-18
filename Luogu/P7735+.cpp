#include<bits/stdc++.h>
using namespace std;

#define _ (int)(1e5 + 5)
#define lc k << 1
#define rc k << 1 | 1
#define lcon lc, l, mid
#define rcon rc, mid + 1, r
#define Mid int mid = ((l + r) >> 1)
#define Init int k, int l, int r
#define FR for(int i = head[u],v = e[i].to;i;i = e[i].next,v = e[i].to)
#define cl(a,b) memset(a, b, sizeof a)

int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){ if(ch=='-') f=-1;ch=getchar(); }
    while(ch>='0'&&ch<='9'){ x=x*10+ch-'0',ch=getchar(); }
    return x*f;
}

struct edge {
    int next, to;
};
struct node {
    int lco, rco, anu;
    node() { lco = INT_MAX, rco = -INT_MAX, anu = 0; }
};

int cnt, T, n, m, color;
int fa[_], de[_], si[_], so[_], se[_], to[_], re[_], tf[_ << 2], head[_];
node tree[_ << 2];
edge e[_ << 1];

void add(int f, int t) {
    e[++cnt] = edge{ head[f], t };
    head[f] = cnt;
}

void dfs1(int u, int f) {
    fa[u] = f;
    si[u] = 1;
    de[u] = de[f] + 1;
    FR{
        if (v == f) continue;
        dfs1(v, u);
        si[u] += si[v];
        if (si[v] > si[so[u]]) so[u] = v;
    }
}
void dfs2(int u, int tof) {
    to[u] = tof;
    se[u] = ++se[0];
    re[se[0]] = u;
    if (!so[u]) return;
    dfs2(so[u], tof);
    FR{
        if (v == fa[u] || v == so[u]) continue;
        dfs2(v, v);
    }
}

node pushup(node a, node b) {
    if (a.lco == INT_MAX && a.rco == -INT_MAX && !a.anu) return b;
    if (b.lco == INT_MAX && b.rco == -INT_MAX && !b.anu) return a;
    node ans;
    ans.lco = a.lco, ans.rco = b.rco;
    ans.anu = a.anu + b.anu + (a.rco == b.lco);
    return ans;
}
void build(Init) {
    tf[k] = -INT_MAX;
    if (l == r) return (void)(tree[k] = node());
    Mid;
    build(lcon), build(rcon);
    tree[k] = pushup(tree[lc], tree[rc]);
}

void cfu(Init, int v) {
    tf[k] = v;
    tree[k].lco = tree[k].rco = v;
    tree[k].anu = (r - l);
}
void pushdown(Init) {
    Mid;
    if (tf[k] == -INT_MAX) return;
    cfu(lcon, tf[k]), cfu(rcon, tf[k]);
    tf[k] = -INT_MAX;
}
void modify(Init, int x, int y, int v) {
    if (x <= l && r <= y) return cfu(k, l, r, v);
    Mid;
    pushdown(k, l, r);
    if (x <= mid) modify(lcon, x, y, v);
    if (y > mid) modify(rcon, x, y, v);
    tree[k] = pushup(tree[lc], tree[rc]);
}

node query(Init, int x, int y) {
    if (x <= l && r <= y) return tree[k];
    Mid; node ans;
    pushdown(k, l, r);
    if (x <= mid) ans = query(lcon, x, y);
    if (y > mid) ans = pushup(ans, query(rcon, x, y));
    return ans;
}

void treef(int x, int y, int v) {
    int fx = to[x], fy = to[y];
    while (fx != fy) {
        if (de[fx] < de[fy]) swap(x, y), swap(fx, fy);
        modify(1, 1, se[0], se[fx], se[x], v);
        x = fa[fx], fx = to[x];
    }
    if (de[x] > de[y]) swap(x, y);
    modify(1, 1, se[0], se[x], se[y], v);
}

void swap(node& a, node& b) { node p; p = a, a = b, b = p; }
int treeq(int x, int y) {
    int fx = to[x], fy = to[y], flag = 0;
    node ans1, ans2;
    while (fx != fy) {
        if (de[fx] < de[fy]) swap(x, y), swap(fx, fy), swap(ans1, ans2);
        ans1 = pushup(query(1, 1, se[0], se[fx], se[x]), ans1);
        x = fa[fx], fx = to[x];
    }
    if (de[x] > de[y]) swap(x, y), swap(ans1, ans2);
    ans2 = pushup(query(1, 1, se[0], se[x], se[y]), ans2);
    return ans1.anu + ans2.anu + (ans1.lco == ans2.lco && ans1.lco != INT_MAX);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    T=read();
    while (T--) {
        n=read(),m=read();
        cl(de, 0), cl(fa, 0), cl(si, 0), cl(se, 0), cl(re, 0), cl(to, 0), cl(so, 0), cl(head, 0);
        for (int i = 1; i <= cnt; i++) e[i].next = e[i].to = 0;
        color = cnt = 0;
        for (int i = 1, u, v; i < n; i++) u=read(),v=read() , add(u, v), add(v, u);
        dfs1(1, 0), dfs2(1, 1);
        build(1, 1, se[0]);
        for (int i = 1, opt, x, y; i <= m; i++) {
            opt=read(),x=read(),y=read();
            if (opt == 1) treef(x, y, ++color);
            if (opt == 2) cout << treeq(x, y) << '\n';
        }
    }
    return 0;
}
