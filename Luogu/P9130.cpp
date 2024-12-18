#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5, Mo = 1e9 + 7, inv2 = 5e8 + 4;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }

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

namespace Seg {
    struct Node {
        int l, r, s, R; ll x, y;
        Node() { l = r = s = R = x = y = 0; }
    } o[N << 6];
    int rt, tot;
#define ls o[p].l
#define rs o[p].r
#define M ll m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
#define I p, l, r
    inline int F(ll l, ll r) { return 1ll * ((l + r) % Mo) * ((r - l + 1) % Mo) % Mo * inv2 % Mo; }
    inline int get(int p, ll l, ll r, ll x) {
        if (l == r) return x||o[p].x? l % Mo: 0;
        M, y = m - l + 1 - o[ls].x;
        return x<=y? mo(get(goL, x) + o[p].R): mo(F(l, m) + get(goR, x - y + o[ls].y));
    }
    inline void up(int p, ll l, ll r) {
        M;
        o[p].x = o[ls].x + min(r - m, o[ls].y + o[rs].x);
        o[p].y = o[rs].y + max(o[ls].y + o[rs].x - (r - m), 0ll);
        o[p].s = mo(o[ls].s + (o[p].R = get(goR, o[ls].y)));
    }
    inline void upd(int &p, ll l, ll r, ll x, int y) {
        if (!p) p = ++tot;
        if (l == r) {
            o[p] = Node();
            if (y) o[p].s = l % Mo, o[p].x = 1, o[p].y = y - 1;
            return;
        }
        M; x<=m? upd(goL, x, y): upd(goR, x, y); up(I);
    }
}
using namespace Seg;

int T;

int main() {
    io >> T;
    ll x; int y;
    while (T--) {
        io >> x >> y;
        upd(rt, 1, 2e14, x, y);
        printf("%d\n", o[rt].s);
    }

    return 0;
}
