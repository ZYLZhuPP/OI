#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (auto i = (l); i <= (r); ++i)
typedef unordered_map<int, int > unmap;
const int N = 3e5 + 5;

struct IO {
    static const int BufS = 1 << 20;
    char ibuf[BufS], *S, *T, c; int f;
#define gc() ((S==T && (T=(S=ibuf)+fread(ibuf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    char obuf[BufS]; int E, st[66], t;
#define pc(c) (obuf[E==BufS && (E-=fwrite(obuf, 1, BufS, stdout)), E++]=c)
    inline void flush() {fwrite(obuf, 1, E, stdout);}
    ~IO() {flush();}
    template<class C>
    inline IO& operator << (C x) {
        if (!x) pc('0'); if (x < 0) pc('-'), x = -x;
        while (x) st[++t] = x % 10, x /= 10;
        while (t) pc(st[t--] ^ 48);
        return *this;
    }
    inline IO& operator << (char x) {
        pc(x); return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

struct Cla {
    int v, id;
};
vector<Cla > ned[N];

struct Sol {
    int x, d, id;
};
vector<Sol > one[N], two[N];

vector<int > es[N];
int n, m, fa[N], f[N], dep[N], ans[N], lca[N], l[N], r[N];
bool vis[N];
unmap a, b;

int find(int u) {if (u ^ f[u]) return f[u] = find(f[u]); return u;}

void dfs(int u, int pre) {
    vis[u] = 1;
    fa[u] = pre;
    dep[u] = dep[pre] + 1;
    for (auto &x : ned[u]) {
        int v = x.v;
        if (vis[v]) lca[x.id] = find(v);
    }
    for (auto &v : es[u]) if (v ^ pre) {
        dfs(v, u);
    }
    f[u] = pre;
}

void solve(int u, int pre) {
    a[dep[u] + u]++; b[dep[u] - u]++;
    for (auto &x : one[u]) {
        ans[x.id] += x.d * a[x.x];
    }
    for (auto &x : two[u]) {
        ans[x.id] += x.d * b[x.x];
    }
    for (auto &v : es[u]) if (v ^ pre) {
        solve(v, u);
    }
    a[dep[u] + u]--; b[dep[u] - u]--;
}

int main() {
    io >> n >> m;
    For (i, 1, n - 1) {
        int u, v;
        io >> u >> v;
        es[u].push_back(v);
        es[v].push_back(u);
    } 
    For (i, 1, n) f[i] = i;
    For (i, 1, m) {
        io >> l[i] >> r[i];
        ned[l[i]].push_back({r[i], i});
        ned[r[i]].push_back({l[i], i});
    }
    
    dfs(1, 0);
    
    For (i, 1, m) {
        int u = l[i], v = r[i], c = lca[i];
        one[u].push_back({dep[u], 1, i});
        one[c].push_back({dep[u], -1, i});
        two[v].push_back({2 * dep[c] - dep[u], 1, i});
        two[fa[c]].push_back({2 * dep[c] - dep[u], -1, i});
    }
    
    solve(1, 0);
    
    For (i, 1, m) io << ans[i] << '\n';
    
    return 0;
}

