#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 105;
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

int n;
array<int, 3 > a[N];
ll ans = 1e18;
mt19937 rnd(time(0));

namespace Basis {
    int o[20], b[20], c[20], B, C, S[20], A[20];
    inline void ins(int a, int x, int y) {
        int s = 0, _ = a;
        For (i, 0, 19) if (a >> i & 1) {
            if (!o[i]) {
                o[i] = a; b[i] = x; c[i] = y; S[i] = s | (1 << i); A[i] = _;
                B += x; C += y;
                return;
            }
            a ^= o[i]; s ^= S[i];
        }
        ll mn = 1ll * B * C; int id = -1;
        rFor (i, 19, 0) if (s >> i & 1 && cmin(mn, 1ll * (B - b[i] + x) * (C - c[i] + y))) id = i;
        if (~id) {
            vector<array<int, 3 > > op;
            For (i, 0, 19) if (i ^ id && o[i]) op.pb({A[i], b[i], c[i]});
            op.pb({_, x, y});
            B = C = 0;
            For (i, 0, 19) o[i] = 0;
            for (auto &[a, b, c] : op) ins(a, b, c);
        }
    }
}
using namespace Basis;

inline void solve() {
    B = C = 0;
    For (i, 0, 19) o[i] = 0;
    shuffle(a + 1, a + n + 1, rnd);
    For (i, 1, n) ins(a[i][0], a[i][1], a[i][2]);
    cmin(ans, 1ll * B * C);
}

int main() {
    io >> n;
    For (i, 1, n) For (j, 0, 2) io >> a[i][j];
    For (_, 1, 1e4) solve();
    printf("%lld", ans);

    return 0;
}
