#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5, Mo = 998244353, inv2 = 499122177;

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

int n, ans;
array<int, 2 > a[N];

namespace Seg {
    struct Node {
        int l, r, v;
        Node(int l = 1, int r = 1, int v = 1): l(l), r(r), v(v) { };
        inline Node operator + (const Node &a) const { return {(a.l + 1ll * l * a.v) % Mo, (r + 1ll * a.r * v) % Mo, 1ll * v * a.v % Mo}; }
    } o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p] = o[ls] + o[rs]; }
    inline void build(int p, int l, int r) {
        o[p] = {r - l + 1, r - l + 1, 1};
        if (l == r) return;
        M; build(goL); build(goR);
    }
    inline void upd(int p, int l, int r, int x, const int &v) {
        if (l == r) return o[p] = {v, v, v}, void();
        M; x<=m? upd(goL, x, v): upd(goR, x, v); up(p);
    }
    inline Node query(int p, int l, int r, int x, int y) {
        if (x <= l && r <= y) return o[p];
        M; return y<=m? query(goL, x, y): x>m? query(goR, x, y): query(goL, x, y) + query(goR, x, y);
    }
}
using namespace Seg;

int main() {
    freopen("ddl.in", "r", stdin);
    freopen("ddl.out", "w", stdout);
    io >> n;
    For (i, 1, n) io >> a[i][0], a[i][1] = i;
    sort(a + 1, a + n + 1);
    build(1, 1, n);
    rFor (i, n, 1) {
        int l = query(1, 1, n, 1, a[i][1]).l, r = query(1, 1, n, a[i][1], n).r;
        ans = (ans + 1ll * l * r % Mo * inv2 % Mo * a[i][0]) % Mo;
        upd(1, 1, n, a[i][1], inv2);
    }
    printf("%d", ans);

    fclose(stdin); fclose(stdout);
    return 0;
}
