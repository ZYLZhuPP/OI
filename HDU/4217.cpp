#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e5 + 5;
typedef long long ll;

struct IO {
    char c; int f;
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

template<class V = int>
class Treap {
    private:
    struct Node {
        int l, r, sz; V v; int heap;
        Node(): v(V()), heap(rand()) { l = r = sz = 0; }
        Node(V v): v(v), heap(rand()) { l = r = 0; sz = 1; }
    };
    vector<Node > o;
    int rt, x, y;
#define ls o[p].l
#define rs o[p].r
#define goL ls, u, o[v].l
#define goR rs, o[u].r, v
    int up(int p) { o[p].sz = o[ls].sz + o[rs].sz + 1; return p; }
    void split_k(int p, int &u, int &v, const V &k) {
        if (!p) return void(u = v = 0);
        if (o[p].v < k) u = p, split_k(goR, k), up(u);
        else v = p, split_k(goL, k), up(v);
    }
    void split_k_(int p, int &u, int &v, const V &k) {
        if (!p) return void(u = v = 0);
        if (!(k < o[p].v)) u = p, split_k_(goR, k), up(u);
        else v = p, split_k_(goL, k), up(v);
    }
    void split_r(int p, int &u, int &v, const int &k) {
        if (!p) return void(u = v = 0);
        if (o[ls].sz + 1 <= k) u = p, split_r(goR, k - o[ls].sz - 1), up(u);
        else v = p, split_r(goL, k), up(v);
    }
    int merge(int u, int v) {
        if (!u || !v) return u | v;
        if (o[u].heap < o[v].heap) { o[u].r = merge(o[u].r, v); return up(u); }
        else { o[v].l = merge(u, o[v].l); return up(v); }
    }
    public:
    int tot;
    Treap() { rt = tot = 0; o.pb(Node()); }
    int size() const { return o[rt].sz; }
    void ins(const V &v) {
        split_k(rt, rt, y, v);
        x = ++tot, o.pb(Node(v));
        rt = merge(rt, merge(x, y));
    }
    void del_all_k(const V &v) {
        split_k(rt, rt, x, v); split_k_(x, x, y, v);
        rt = merge(rt, y);
    }
    void del_a_k(const V &v) {
        split_k(rt, rt, x, v); split_k_(x, x, y, v);
        x = merge(o[x].l, o[x].r);
        rt = merge(rt, merge(x, y));
    }
    void del_r(const int &l, const int &r) {
        split_r(rt, rt, x, l - 1); split_r(x, x, y, r - l + 1);
        rt = merge(rt, y);
    }
    void del_r(const int &k) { del_r(k, k); }
    int count(const V &l, const V &r) {
        split_k(rt, rt, x, l); split_k_(x, x, y, r);
        int res = o[x].sz;
        rt = merge(rt, merge(x, y));
        return res;
    }
    int count(const V &v) { return count(v, v); }
    int rnk(const V &v) {
        split_k(rt, x, y, v);
        int res = o[x].sz + 1;
        rt = merge(x, y);
        return res;
    }
    V pre(const V &v) {
        split_k(rt, x, y, v);
        int p = x; while (rs) p = rs;
        rt = merge(x, y);
        return o[p].v;
    }
    V suf(const V &v) {
        split_k_(rt, x, y, v);
        int p = y; while (ls) p = ls;
        rt = merge(x, y);
        return o[p].v;
    }
    V kth(const int &k) {
        split_r(rt, rt, x, k - 1); split_r(x, x, y, 1);
        rt = merge(rt, merge(x, y));
        return o[x].v;
    }
};

int T, n, m;
ll ans;

int main() {
    io >> T;
    For (o, 1, T) {
        ans = 0;
        Treap<> tr;
        io >> n >> m;
        For (i, 1, n) tr.ins(i);
        int k;
        while (m--) io >> k, ans += tr.kth(k), tr.del_r(k);
        printf("Case %d: %lld\n", o, ans);
    }

    return 0;
}
