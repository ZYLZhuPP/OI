#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5;

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
		x = 0; f = 1;
		while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
		while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
		x *= f; return *this;
	}
	inline bool operator ~ () const { return ~c; }
} io;

mt19937 rd(time(0));

template<class V = int>
class Treap {
    private:
    struct Node {
        const ull heap; V v; int l, r, sz;
        Node(): heap(rd()), v(V()) { l = r = sz = 0; }
        Node(V v, int l = 0, int r = 0): heap(rd()), v(v), l(l), r(r) { sz = 1; }
        bool operator < (const Node &x) const { return heap < x.heap; }
    };
    vector<Node > o;
    int rt, x, y;
#define ls o[p].l
#define rs o[p].r
#define goL ls, u, ls
#define goR rs, rs, v
    int up(int p) { o[p].sz = o[ls].sz + o[rs].sz + 1; return p; }
    void split_k(int p, int &u, int &v, const V &k) {
        if (!p) return void(u = v = 0);
        if (o[p].v < k) u = p, split_k(goR, k);
        else v = p, split_k(goL, k);
        up(p);
    }
    void split_k_(int p, int &u, int &v, const V &k) {
        if (!p) return void(u = v = 0);
        if (!(k < o[p].v)) u = p, split_k_(goR, k);
        else v = p, split_k_(goL, k);
        up(p);
    }
    void split_r(int p, int &u, int &v, const int &k) {
        if (!p) return void(u = v = 0);
        if (o[ls].sz + 1 <= k) u = p, split_r(goR, k - o[ls].sz - 1);
        else v = p, split_r(goL, k);
        up(p);
    }
    int merge(int u, int v) {
        if (!u || !v) return u | v;
        if (o[u] < o[v]) { o[u].r = merge(o[u].r, v); return up(u); }
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
    int rank(const V &v) {
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
    const V operator [] (const int &k) {
        split_r(rt, rt, x, k - 1); split_r(x, x, y, 1);
        rt = merge(rt, merge(x, y));
        return o[x].v;
    }
};

int n, m, rk[N], id[N], x, y, mn, mx;
char op[10];

int main() {
    Treap<> tr;
    io >> n >> m;
    For (i, 1, n) io >> x, tr.ins(rk[x] = m + i), id[rk[x]] = x;
    mn = m + 1, mx = m + n;
    while (m--) {
        scanf("%s%d", op, &x);
        if (op[0] == 'T') {
            tr.del_a_k(rk[x]);
            tr.ins(rk[x] = --mn);
            id[rk[x]] = x;
        } else if (op[0] == 'B') {
            tr.del_a_k(rk[x]);
            tr.ins(rk[x] = ++mx);
            id[rk[x]] = x;
        } else if (op[0] == 'I') {
            scanf("%d", &y);
            if (!y) continue;
            int u = tr.rank(rk[x]), v = u + y;
            y = id[tr[v]];
            swap(rk[x], rk[y]);
            id[rk[x]] = x; id[rk[y]] = y;
        } else if (op[0] == 'A') {
            printf("%d\n", tr.rank(rk[x]) - 1);
        } else if (op[0] == 'Q') {
            printf("%d\n", id[tr[x]]);
        }
    }

    return 0;
}
