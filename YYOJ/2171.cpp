#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5;

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

struct Sth {
    int v, w;
    bool operator < (const Sth &a) const { return w < a.w; }
} a[N];

struct Seg {
    struct Node {
        int sz; ll s;
        Node() { sz = s = 0; }
    } o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p].s = o[ls].s + o[rs].s; o[p].sz = o[ls].sz + o[rs].sz; }
    inline void upd(int p, int l, int r, int x, const int &d) {
        if (l > x || r < x) return;
        if (l == r) return o[p].sz += d, o[p].s += d * l, void();
        M; upd(goL, x, d); upd(goR, x, d); up(p);
    }
    inline ll query(int p, int l, int r, int k) {
        if (!k) return 0;
        if (l == r) return 1ll * k * l;
        M; return k<o[ls].sz? query(goL, k): (o[ls].s + query(goR, k - o[ls].sz));
    }
} L, R;

int n, T, f[N];
ll m;

int main() {
    memset(f, -1, sizeof f);
    io >> n >> m >> T;
    For (i, 1, n) io >> a[i].w >> a[i].v;
    sort(a + 1, a + n + 1);
    For (i, 1, n) L.upd(1, 0, 1e6, a[i].v, 1);
    int ans = 0;
    rFor (i, n, 1) {
        L.upd(1, 0, 1e6, a[i].v, -1);
        while (min(n - i, i - 1) >= ans && L.query(1, 0, 1e6, ans) + a[i].v + R.query(1, 0, 1e6, ans) <= m) f[ans << 1 | 1] = a[i].w, ans++;
        R.upd(1, 0, 1e6, a[i].v, 1);
    }
    while (T--) {
        int x;
        io >> x;
        printf("%d\n", f[x]);
    }

    return 0;
}
