#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2505, M = 1e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

struct P {
    int x, y, X, Y;
    P operator & (P &a) const { return {max(x, a.x), max(y, a.y), min(X, a.X), min(Y, a.Y)}; }
} a[4];

int n, m, K, T, cnt[N][N];

namespace BIT {
    int o[M];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, const int &d) { for (; x < M; x += lowbit(x)) o[x] += d; }
    inline int query(int x) { int r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
}

vector<int > A;
struct Seg {
    int o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void upd(int p, int l, int r, int x, const int &d) {
        o[p] += d;
        if (l == r) return;
        M; x<=m? upd(goL, x, d): upd(goR, x, d);
    }
    inline void del(int p, int l, int r, int x, int y) {
        if (!o[p] || l > y || r < x) return;
        if (l == r) return A.pb(l);
        M; del(goL, x, y); del(goR, x, y);
    }
} o[N];

int main() {
    io >> n >> K; n = n - K + 1;
    io >> m;
    For (i, 1, m) {
        int o, x, y;
        io >> o;
        For (j, 0, o - 1) io >> x >> y, a[j] = {max(1, x - K + 1), max(1, y - K + 1), x, y};
        For (s, 1, (1 << o) - 1) {
            P p = {1, 1, n, n};
            int d = -1;
            For (j, 0, o - 1) if (s >> j & 1) p = p & a[j], d = -d;
            auto [x, y, X, Y] = p;
            if (x <= X && y <= Y) cnt[x][y] += d, cnt[X + 1][Y + 1] += d, cnt[x][Y + 1] -= d, cnt[X + 1][y] -= d;
        }
    }
    For (i, 1, n) For (j, 1, n) {
        cnt[i][j] += cnt[i][j - 1] + cnt[i - 1][j] - cnt[i - 1][j - 1];
        if (cnt[i][j]) o[i].upd(1, 1, n, j, 1), BIT::upd(m - cnt[i][j] + 1, 1);
    }
    io >> T;
    while (T--) {
        int op, x, y, v;
        io >> op;
        if (op == 1) {
            io >> x >> y;
            int X = min(n, x), Y = min(n, y);
            x = max(1, x - K + 1); y = max(1, y - K + 1);
            For (i, x, X) {
                A.resize(0); o[i].del(1, 1, n, y, Y);
                for (auto &z : A) o[i].upd(1, 1, n, z, -1), BIT::upd(m - cnt[i][z] + 1, -1);
            }
        } else {
            io >> v; cmin(v, m + 1);
            printf("%.5lf\n", 1.0 * BIT::query(m - v + 1) / n / n);
        }
    }

    return 0;
}