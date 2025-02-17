#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef unsigned long long ull;
typedef double lf;
const int N = 7e4 + 5;

struct IO{
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

lf mp[N];
namespace SGT {
    const lf alp = 0.75, inf = 1e9;
    int rt, tot, id[N], len;
    struct Node {
        int l, r, sz; lf v;
        Node() { l = r = sz = v = 0; }
        Node(lf v): v(v) { l = r = 0; sz = 1; }
    } o[N];
#define ls o[p].l
#define rs o[p].r
    inline void up(int p) { o[p].sz = o[ls].sz + o[rs].sz + 1; }
    inline void pia(int p) { if (!p) return; pia(ls); id[++len] = p; pia(rs); }
    inline void build(int &p, int l, int r, lf L = 0, lf R = inf) {
        if (r < l) return void(p = 0);
        int m = (l + r) >> 1; p = id[m];
        lf M = (L + R) / 2; o[p] = Node(mp[p] = M);
        build(ls, l, m - 1, L, M); build(rs, m + 1, r, M, R); up(p);
    }
    inline int ins(int &p, const int &k, lf L = 0, lf R = inf) {
        lf M = (L + R) / 2;
        if (!p) return p = ++tot, o[p] = Node(mp[p] = M), p;
        int res = o[ls].sz>=k? ins(ls, k, L, M): ins(rs, k - o[ls].sz - 1, M, R); up(p);
        if (max(o[ls].sz, o[rs].sz) > alp * o[p].sz) len = 0, pia(p), build(p, 1, len, L, R);
        return res;
    }
    inline int kth(int p, int k) {
        if (o[ls].sz >= k) return kth(ls, k);
        else { k -= o[ls].sz + 1; return k? kth(rs, k): p; }
    }
}

/*ull mp[N];
namespace seq { // for label
    inline int gen() {
        static unsigned int x = 2431898411;
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        return x;
    }
    const int S = 200000;
    int ls[S], rs[S], p[S], size[S], tot;
    inline void update(int id) { size[id] = size[ls[id]] + size[rs[id]] + 1; }
    inline void rls(int & rt){ int x = ls[rt]; ls[rt] = rs[x], update(rs[x] = rt), rt = x; }
    inline void rrs(int & rt){ int x = rs[rt]; rs[rt] = ls[x], update(ls[x] = rt), rt = x; }
    inline void build(int rt, ull L, ull R) {
        ull mid = mp[rt] = (L + R) >> 1;
        if(ls[rt]) build(ls[rt], L, mid);
        if(rs[rt]) build(rs[rt], mid, R);
    }
    inline void ins(int & rt, int rank, int idx, int fa, ull L = 0, ull R = 1ull << 60) {
        if(!rt) {
            p[++tot] = gen(), size[tot] = 1, mp[idx] = (L + R) >> 1, rt = tot;
        } else {
            ull mid = (L + R) >> 1;
            if(size[ls[rt]] >= rank) {
                ins(ls[rt], rank, idx, rt, L, mid);
                if(p[ls[rt]] < p[rt]) rls(rt);
            } else {
                ins(rs[rt], rank - size[ls[rt]] - 1, idx, rt, mid, R);
                if(p[rs[rt]] < p[rt]) rrs(rt);
            }
            update(rt);
        }
        if((p[rt] >= p[fa] || !fa) && rt == idx) build(rt, L, R);
    }
    inline int kth(int root, int k) {
        for(;;) {
            if(size[ls[root]] >= k) {
                root = ls[root];
            } else {
                if(k == size[ls[root]] + 1) return root;
                k -= size[ls[root]] + 1;
                root = rs[root];
            }
        }
    }
}*/

class Treap {
    private:
    struct Node {
        const int heap; int l, r, sz; int v;
        Node(): heap(rand()) { l = r = sz = v = 0; }
        Node(int v): heap(rand()), v(v) { l = r = 0; sz = 1; }
    };
    vector<Node > o;
    int rt, x, y;
#define ls o[p].l
#define rs o[p].r
#define goL ls, u, ls
#define goR rs, rs, v
    int up(int p) { o[p].sz = o[ls].sz + o[rs].sz + 1; return p; }
    void split_k(int p, int &u, int &v, const int &k) {
        if (!p) return void(u = v = 0);
        if (mp[o[p].v] < mp[k]) u = p, split_k(goR, k);
        else v = p, split_k(goL, k);
        up(p);
    }
    void split_k_(int p, int &u, int &v, const int &k) {
        if (!p) return void(u = v = 0);
        if (mp[o[p].v] <= mp[k]) u = p, split_k_(goR, k);
        else v = p, split_k_(goL, k);
        up(p);
    }
    int merge(int u, int v) {
        if (!u || !v) return u | v;
        if (o[u].heap < o[v].heap) { o[u].r = merge(o[u].r, v); return up(u); }
        else { o[v].l = merge(u, o[v].l); return up(v); }
    }
    public:
    int tot;
    Treap() { srand(time(0)); rt = tot = 0; o.pb(Node()); }
    void ins(const int &v) {
        y = ++tot, o.pb(Node(v));
        int *x = &rt;
        for (; *x && o[y].heap > o[*x].heap; ) {
            ++o[*x].sz;
            x = &(mp[v] < mp[o[*x].v] ? o[*x].l : o[*x].r);
        }
        split_k(*x, o[y].l, o[y].r, v);
        up(*x = y);
    }
    void del(const int &v) {
        int *x = &rt;
        for (; o[*x].v ^ v; ) {
            --o[*x].sz;
            x = &(mp[v] < mp[o[*x].v] ? o[*x].l : o[*x].r);
        }
        *x = merge(o[*x].l, o[*x].r);
    }
    int count(const int &l, const int &r) {
        split_k(rt, rt, x, l); split_k_(x, x, y, r);
        int res = o[x].sz;
        rt = merge(rt, merge(x, y));
        return res;
    }
} tr[N];

#define lowbit(x) (x & -x)
inline void ins(int x, const int &v) { for (x++; x < N; x += lowbit(x)) tr[x].ins(v); }
inline void del(int x, const int &v) { for (x++; x < N; x += lowbit(x)) tr[x].del(v); }
inline int query(const int &l, const int &r, int k) {
    int x = 0;
    rFor (i, 16, 0) if ((x | (1 << i)) < N) {
        int s = tr[x | (1 << i)].count(l, r);
        if (s < k) k -= s, x |= 1 << i;
    }
    return x;
}

int n, x, y, k, val[N], ans, q;
int root;

int main() {
    io >> n;
    For (i, 1, n) io >> val[i], SGT::id[i] = i;
    SGT::build(SGT::rt, 1, SGT::tot = n);
    For (i, 1, n) ins(val[i], i);
    io >> q;
    while (q--) {
        //For (i, 1, SGT::tot) cout << mp[i] << " "; puts("");
        using SGT::kth;
        using SGT::rt;
        char op[2];
        scanf("%s", op);
        if (op[0] == 'Q') {
            io >> x >> y >> k; x ^= ans; y ^= ans; k ^= ans;
            printf("%d\n", ans = query(kth(rt, x), kth(rt, y), k));
        } else if (op[0] == 'M') {
            io >> x >> y; x ^= ans; y ^= ans;
            k = kth(rt, x); //cout << k << endl;
            del(val[k], k);
            ins(val[k] = y, k);
        } else if (op[0] == 'I') {
            io >> x >> y; x ^= ans; y ^= ans;
            k = SGT::ins(rt, x - 1); //cout << k << endl;
            ins(val[k] = y, k);
        }
    }

    return 0;
}