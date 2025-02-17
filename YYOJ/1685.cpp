#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5;

struct IO {
    static const int BufS=1<<20;
    char ibuf[BufS], *iS, *iT, obuf[BufS], c;
    int top, f, num[66], t;
#define gc() ((iS==iT && (iT=(iS=ibuf)+fread(ibuf, 1, BufS, stdin)), iS==iT)? EOF: *iS++)
    #define pc(c) (obuf[top==BufS? fwrite(obuf, 1, BufS, stdout), !(top=1): top++]=c)
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline void flush() { fwrite(obuf, 1, top, stdout); }
    ~IO() { flush(); }
    template<class C>
    inline IO& operator << (C x) {
        if (!x) pc('0'); if (x < 0) pc('-'), x = -x;
        while (x) num[++t] = x % 10, x /= 10;
        while (t) pc(num[t--] ^ 48);
        return *this;
    }
    inline IO& operator << (char x) {
        pc(x); return *this;
    }
    inline bool operator ~ () const { return ~c; }
}io;

int n, Q, nn, w[N], a[N], u, v;
ll s[N], up[N], ans[N];
vector<int > es[N];
vector<ll > dw[N];
int tim, in[N], out[N];

namespace tr {
    struct Node {
        int l, r, s;
        Node(int l = 0, int r = 0, int s = 0): l(l), r(r), s(s) { }
    };
    Node o[N * 20]; int rt[N], tot;
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    void pushup(int p) { o[p].s = o[ls].s + o[rs].s; }
    void upd(int &p, int l, int r, int x) {
        o[++tot] = o[p]; p = tot;
        if (l == r) { o[p].s++; return; }
        M; x<=m? upd(goL, x): upd(goR, x);
        pushup(p);
    }
    int query(int p, int q, int l, int r, int x) {
        if (x < l) return 0;
        if (x >= r) return o[q].s - o[p].s;
        M; return query(o[p].l, o[q].l, l, m, x) + query(o[p].r, o[q].r, m + 1, r, x);
    }
    void add(int x, int y) { upd(rt[x] = rt[x - 1], 1, nn, y); }
    int query(int l, int r, int x) { return l>r? 0: query(rt[l - 1], rt[r], 1, nn, x); }
}

void init(int u, int pre) {
    in[u] = ++tim; tr::add(tim, w[u]);
    for (auto &v : es[u]) {
        if (v == pre) {
            dw[u].push_back(0);
            continue;
        }
        init(v, u);
        int res = tr::query(in[v], out[v], w[u] - 1);
        dw[u].push_back(res);
    }
    out[u] = tim;
}

void dfs1(int u, int pre) {
    int siz = es[u].size();
    For (i, 0, siz - 1) {
        int v = es[u][i];
        if (v == pre) continue;
        dfs1(v, u);
        dw[u][i] += s[v];
        s[u] += dw[u][i];
    }
}

void dfs2(int u, int pre, int x) {
    up[u] = u==1? 0: (up[pre] + s[pre] - dw[pre][x] + tr::query(1, in[u] - 1, w[u] - 1) + tr::query(out[u] + 1, n, w[u] - 1));
    int siz = es[u].size();
    For (i, 0, siz - 1) {
        int v = es[u][i];
        if (v == pre) continue;
        dfs2(v, u, i);
    }
    ans[u] = up[u] + s[u];
}

int main() {
    io >> n >> Q;
    For (i, 1, n) io >> w[i];
    memcpy(a, w, sizeof(w));
    sort(a + 1, a + n + 1);
    nn = unique(a + 1, a + n + 1) - a;
    For (i, 1, n) w[i] = lower_bound(a + 1, a + nn, w[i]) - a;
    
    For (i, 1, n - 1) {
        io >> u >> v;
        es[u].push_back(v);
        es[v].push_back(u);
    }
    init(1, 0);
    dfs1(1, 0);
    dfs2(1, 0, 0);
    
    For (i, 1, Q) {
        io >> u;
        io << ans[u] << '\n';
    }
    
    return 0;
}
