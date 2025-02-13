#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e4 + 5, M = 1e4 + 5;

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

int T, n, m, a[N], b[N + M], B, l[M], r[M], k[M], x[M];
char op[M][2];

namespace BIT {
    namespace Seg {
        int tot;
        struct Node {
            int l, r, sz;
            Node() { l = r = sz = 0; }
        } o[N * 50];
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
        inline int copy(int p) { o[++tot] = o[p]; return tot; }
        inline void upd(int &p, int l, int r, const int &x, const int &d) {
            if (l > x || r < x) return;
            p = copy(p); o[p].sz += d;
            if (l == r) return;
            M; upd(goL, x, d); upd(goR, x, d);
        }
    }
    using namespace Seg;
    int rt[N], root[N];
    vector<int > L, R;
#define lowbit(x) ((x) & -(x))
    inline void upd(int k, const int &x, const int &d) {
        for (; k <= n; k += lowbit(k)) upd(rt[k], 1, B, x, d);
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
        l--;
        L.resize(0); L.pb(root[l]); for (; l; l -= lowbit(l)) L.pb(rt[l]);
        R.resize(0); R.pb(root[r]); for (; r; r -= lowbit(r)) R.pb(rt[r]);
        return solve(1, B, k);
    }
}
using namespace BIT;

int main() {
    io >> T;
    while (T--) {
        tot = B = 0;
        memset(rt, 0, sizeof rt);
        memset(root, 0, sizeof root);
        io >> n >> m;
        For (i, 1, n) io >> a[i], b[++B] = a[i];
        For (i, 1, m) {
            scanf("%s", op[i]);
            if (op[i][0] == 'Q') io >> l[i] >> r[i] >> k[i];
            else io >> k[i] >> x[i], b[++B] = x[i];
        }
        sort(b + 1, b + B + 1); B = unique(b + 1, b + B + 1) - b - 1;
        For (i, 1, n) a[i] = lower_bound(b + 1, b + B + 1, a[i]) - b, upd(root[i] = root[i - 1], 1, B, a[i], 1);
        For (i, 1, m) {
            if (op[i][0] == 'Q') {
                printf("%d\n", b[query(l[i], r[i], k[i])]);
            } else {
                x[i] = lower_bound(b + 1, b + B + 1, x[i]) - b;
                upd(k[i], a[k[i]], -1);
                upd(k[i], a[k[i]] = x[i], 1);
            }
        }
    }

    return 0;
}