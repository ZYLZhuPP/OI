#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e4 + 5, inf = 1e9;

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

int T, n, m, a[N];

namespace BIT {
    namespace Seg {
        int tot;
        struct Node {
            int l, r, sz;
            Node() { l = r = sz = 0; }
        } o[N * 400];
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
        inline void up(int p) { o[p].sz = o[ls].sz + o[rs].sz; }
        inline void upd(int &p, int l, int r, const int &x, const int &d) {
            if (l > x || r < x) return;
            if (!p) o[p = ++tot] = Node();
            if (l == r) return void(o[p].sz += d);
            M; upd(goL, x, d); upd(goR, x, d); up(p);
        }
    }
    using namespace Seg;
    int rt[N];
    vector<int > L, R;
#define lowbit(x) ((x) & -(x))
    inline void upd(int k, const int &x, const int &d) {
        for (; k <= n; k += lowbit(k)) upd(rt[k], 0, inf, x, d);
    }
    inline int solve(int l, int r, const int &k) {
        if (l == r) return l;
        int x = 0;
        for (auto &p : R) x += o[ls].sz;
        for (auto &p : L) x -= o[ls].sz;
        M;
        if (k <= x) {
            for (auto &p : L) p = ls;
            for (auto &p : R) p = ls;
            return solve(l, m, k);
        } else {
            for (auto &p : L) p = rs;
            for (auto &p : R) p = rs;
            return solve(m + 1, r, k - x);
        }
    }
    inline int query(int l, int r, const int &k) {
        L.resize(0); for (l--; l; l -= lowbit(l)) L.pb(rt[l]);
        R.resize(0); for (; r; r -= lowbit(r)) R.pb(rt[r]);
        return solve(0, inf, k);
    }
}
using namespace BIT;

int main() {
    io >> n >> m;
    For (i, 1, n) io >> a[i], upd(i, a[i], 1);
    while (m--) {
        char op;
        int l, r, k, x;
        cin >> op;
        if (op == 'Q') {
            io >> l >> r >> k;
            printf("%d\n", query(l, r, k));
        } else if (op == 'C') {
            io >> k >> x;
            upd(k, a[k], -1);
            upd(k, a[k] = x, 1);
        }
    }

    return 0;
}
