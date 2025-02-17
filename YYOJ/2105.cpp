#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 1e3 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }
inline int ml(int x, int y) { return 1ll * x * y % Mo; }
inline void mul(int &x, int y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r=1; for(;b;b>>=1,mul(a,a))if(b&1)mul(r,a); return r; }

struct IO {
    int c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, m, q, op, r, c;

struct Treap {
    struct Node {
        int l, r, v, heap;
        Node(int v = 0): v(v) { l = r =  0; heap = rand(); }
        bool operator < (const Node &x) const { return heap < x.heap; }
    };
    vector<Node > o;
    int rt, tot, x, y;
    Treap() { rt = tot = 0; o.push_back(Node()); }

    void split(int p, int &u, int &v, int k) {
        if (!p) return void(u = v = 0);
        if (o[p].v < k) u = p, split(o[p].r, o[p].r, v, k);
        else v = p, split(o[p].l, u, o[p].l, k);
    }
    int merge(int u, int v) {
        if (!u || !v) return u + v;
        if (o[u] < o[v]) { o[u].r = merge(o[u].r, v); return u;}
        else { o[v].l = merge(u, o[v].l); return v; }
    }
    void upd(int k) {
        split(rt, rt, x, k); split(x, x, y, k + 1);
        if (x) rt = merge(rt, y);
        else {
            x = ++tot;
            o.push_back(Node(k));
            rt = merge(merge(rt, x), y);
        }
    }
    int suf(int k) {
        split(rt, rt, x, k);
        if (!x) return INT_MIN; else y = x;
        while (o[y].l) y = o[y].l;
        rt = merge(rt, x);
        return o[y].v;
    }
} tr[N];

int tot, a[N], b[N];
void solve() {
    a[0] = INT_MAX;
    a[tot = 1] = -1;
    int ans = 0;
    For (i, 1, n) {
        memset(b, -1, sizeof b);
        int x = -1;
        bool ok = 0;
        For (j, 1, tot) {
            int k = tr[i].suf(a[j]);
            if (k > a[j] && k < a[j - 1]) { a[tot = j] = k; ok = 1; break; }
            else if (k == a[j]) b[j] = tr[i].suf(a[j] + 1);
            else { x = j; break; }
        }
        if (!ok && x == -1) {
            int k = tr[i].suf(-1);
            if (k > -1 && k < a[tot]) { a[++tot] = k; ok = 1; }
        }
        if (!ok) rFor (j, tot, 1)
            if (b[j] > a[j] && b[j] < a[j - 1]) { a[tot = j] = b[j]; ok = 1; break; }
        //cout << tot << endl;

        if (!ok) return void(puts("-1"));
        else For (j, 1, tot) add(ans, qPow(2, a[j]));
    }
    printf("%d\n", ans);
}

int main() {
    io >> n >> m >> q;
    while (q--) {
        io >> op;
        if (op == 1) {
            io >> r >> c;
            tr[r].upd(m - c);
        } else solve();
    }

    return 0;
}
