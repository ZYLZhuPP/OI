#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;

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

int n, m, a[N];
vector<int > pos[N];

namespace Seg {
    struct Node {
        int l, r, L, R, s, len;
        Node() { l = r = -1; L = R = s = len = 0; }
        Node operator + (const Node &a) const {
            Node res; res.l = l; res.r = a.r; res.len = len + a.len;
            res.s = s + a.s; res.L = L; res.R = a.R;
            if (r + a.l == 1) {
                if (R & 1 && a.L & 1) res.s++;
                if (L == len) res.L = L + a.L;
                if (a.R == a.len) res.R = a.R + R;
            }
            return res;
        }
    } o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p] = o[ls] + o[rs]; }
    inline void build(int p, int l, int r) {
        if (l == r) { o[p].l = o[p].r = 0; o[p].L = o[p].R = o[p].len = 1; return; }
        M; build(goL); build(goR); up(p);
    }
    inline void upd(int p, int l, int r, int x, int v) {
        if (l == r) {
            if (~v) o[p].l = o[p].r = o[p].L = o[p].R = o[p].len = 1, o[p].s = 0;
            else o[p] = Node();
            return;
        }
        M; x<=m? upd(goL, x, v): upd(goR, x, v); up(p);
    }
    inline Node query(int p, int l, int r, int x, int y) {
        if (x > y) return Node();
        if (x <= l && r <= y) return o[p];
        M; return y<=m? query(goL, x, y): x>m? query(goR, x, y): (query(goL, x, y) + query(goR, x, y));
    }
}
using namespace Seg;

int main() {
    io >> n >> m;
    For (i, 1, n) io >> a[i], pos[a[i]].pb(i);
    build(1, 1, n);
    For (i, 1, m) {
        if (pos[i].empty()) { printf("-1 "); continue; }
        int t = pos[i].size();
        for (auto &x : pos[i]) upd(1, 1, n, x, -1);
        printf("%d ", n - t + query(1, 1, n, pos[i][0] + 1, pos[i][t - 1] - 1).s + (query(1, 1, n, pos[i][t - 1] + 1, n) + query(1, 1, n, 1, pos[i][0] - 1)).s);
        for (auto &x : pos[i]) upd(1, 1, n, x, 1);
    }

    return 0;
}
