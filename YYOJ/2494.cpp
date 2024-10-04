#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;

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

int n, m, q, a[N], l[N], r[N], L[N][20], R[N][20], rt[N];
int op[N], k[N], qL[N], qR[N], x[N];
vector<array<int, 2 > > qs[N];

namespace MX {
    int o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p] = max(o[ls], o[rs]); }
    inline void upd(int p, int l, int r, int x, int v) {
        if (l > x || r < x) return;
        if (l == r) return void(o[p] = v);
        M; upd(goL, x, v); upd(goR, x, v); up(p);
    }
    inline int query(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return 0;
        if (x <= l && r <= y) return o[p];
        M; return max(query(goL, x, y), query(goR, x, y));
    }
}

namespace Seg {
    int o[N << 2];
    inline void mark(int p, int v) { o[p] = v; }
    inline void down(int p) { if (o[p]) mark(ls, o[p]), mark(rs, o[p]), o[p] = 0; }
    inline void upd(int p, int l, int r, int x, int y, int v) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return mark(p, v);
        down(p); M; upd(goL, x, y, v); upd(goR, x, y, v); 
    }
    inline int query(int p, int l, int r, int x) {
        if (o[p]) return o[p];
        if (l == r) return 0;
        M; return x<=m? query(goL, x): query(goR, x);
    }
}

inline int getL(int x, int y) { rFor (i, 19, 0) if (L[x][i] >= y) x = L[x][i]; return l[x]; }
inline int getR(int x, int y) { rFor (i, 19, 0) if (R[x][i] >= y) x = R[x][i]; return r[x]; }

int main() {
    io >> n >> m;
    For (i, 1, n) io >> a[i], MX::upd(1, 1, n, i, a[i]);
    For (i, 1, m) io >> l[i] >> r[i];
    io >> q;
    For (i, 1, q) {
        io >> op[i];
        if (op[i] == 1) io >> k[i] >> x[i];
        else io >> qL[i] >> qR[i] >> k[i], qs[qR[i]].pb({k[i], i});
    }
    For (i, 1, m) {
        L[i][0] = Seg::query(1, 1, n, l[i]);
        R[i][0] = Seg::query(1, 1, n, r[i]);
        Seg::upd(1, 1, n, l[i], r[i], i);
        for (auto &[k, id] : qs[i]) x[id] = Seg::query(1, 1, n, k);
    }
    For (j, 1, 19) For (i, 1, m) L[i][j] = L[L[i][j - 1]][j - 1], R[i][j] = R[R[i][j - 1]][j - 1];
    For (i, 1, q) {
        if (op[i] == 1) MX::upd(1, 1, n, k[i], a[k[i]] = x[i]);
        else {
            if (!x[i] || x[i] < qL[i]) printf("%d\n", a[k[i]]);
            else printf("%d\n", MX::query(1, 1, n, getL(x[i], qL[i]), getR(x[i], qL[i])));
        }
    }

    return 0;
}
