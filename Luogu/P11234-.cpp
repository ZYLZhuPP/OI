#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1 << 17 | 3;

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

int n, m, T, A[N], a[N], c[N], _2[N], X[4];
char s[N];
ll res, ans;

namespace Seg {
    ll o[N << 1]; int d[N << 1], pos[N << 1], val[N << 1];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    inline void build(int p, int l, int r) {
        if (l == r) return o[p] = l, void();
        M; build(goL); build(goR); o[p] = o[ls] + o[rs]; val[p] = val[ls] + 1;
    }
    inline void init(int p, int l, int r) {
        if (l == r) return pos[p] = l, void();
        M; init(goL); init(goR); pos[p] = a[pos[p << 1 | d[p]]]>=val[p]? pos[p << 1 | d[p]]: pos[p << 1 | !d[p]];
    }
    inline pair<int, bool > query(int p, int l, int r, int x, int k) {
        if (r <= x) {
            if (a[pos[p]] >= k) res += pos[p];
            return {a[pos[p]], 0};
        }
        if (l > x) {
            res += o[p];
            return {0, 1};
        }
        M;
        auto [u, b1] = d[p]? query(goR, x, max(k, val[p])): query(goL, x, max(k, val[p]));
        if (u < val[p]) {
            auto [v, b2] = d[p]? query(goL, x, k): query(goR, x, k);
            return b1? make_pair(u, b1): make_pair(v, b2);
        }
        return {u, b1};
    }
}
using namespace Seg;

int main() {
    For (i, 1, 17) For (j, (1 << (i - 1)) + 1, 1 << i) _2[j] = i;
    io >> n >> m;
    int K = _2[n], len = 1 << K;
    For (i, 1, n) io >> A[i];
    For (i, 1, m) io >> c[i];
    rFor (i, K - 1, 0) {
        scanf("%s", s);
        For (j, 0, (1 << i) - 1) d[1 << i | j] = s[j] ^ 48;
    }
    build(1, 1, len);
    io >> T;
    while (T--) {
        ans = 0;
        For (i, 0, 3) io >> X[i];
        For (i, 1, n) a[i] = A[i] ^ X[i % 4], cerr << a[i] << " ";
        init(1, 1, len);
        For (i, 1, m) res = 0, query(1 << (K - _2[c[i]]), 1, 1 << _2[c[i]], c[i], 0), ans ^= i * res;
        printf("%lld\n", ans);
    }

    return 0;
}
