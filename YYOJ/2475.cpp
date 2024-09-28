#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;
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

namespace Seg {
    int o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void up(int p) { o[p] = min(o[ls], o[rs]); }
    inline void upd(int p, int l, int r, int x, int v) {
        if (l > x || r < x) return;
        if (l == r) return void(o[p] = v);
        M; upd(goL, x, v); upd(goR, x, v); up(p);
    }
    inline int query(int p, int l, int r, int x, int y) {
        if (l > y || r < x) return 1e9;
        if (x <= l && r <= y) return o[p];
        M; return min(query(goL, x, y), query(goR, x, y));
    }
}
using namespace Seg;

int n, m, w[N], p[N], f[N];
char s[N], t[N];
vector<int > pos[N];

int main() {
    io >> n >> m;
    scanf("%s", s + 1);
    For (i, 1, n) io >> w[i];
    while (m--) {
        scanf("%s", t + 1);
        int len = strlen(t + 1), j = 0;
        For (i, 2, len) {
            while (j && t[i] ^ t[j + 1]) j = p[j];
            if (t[i] == t[j + 1]) j++;
            p[i] = j;
        }
        j = 0;
        For (i, 1, n) {
            while (j && s[i] ^ t[j + 1]) j = p[j];
            if (s[i] == t[j + 1]) j++;
            if (j == len) pos[i - len + 1].pb(i), j = p[j];
        }
    }
    int x = n + 1;
    rFor (i, n, 1) {
        upd(1, 1, n + 1, i, w[i] + f[i + 1]);
        for (auto &j : pos[i]) cmin(x, j);
        f[i] = query(1, 1, n + 1, i, x);
    }
    printf("%d", f[1]);

    return 0;
}
