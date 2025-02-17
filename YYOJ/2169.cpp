#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5, inf = 1e9;
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

int n, m, A[N], B[N], stA[N][20], stB[N][20], pos[N][20], stk[N], top, M;
ll s[N], ans[N], S, b[N];
vector<array<int, 3 > > qs[N];

namespace BIT {
    ll K[N], C[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(ll f[], int x, const ll &d) { for (; x <= M; x += lowbit(x)) f[x] += d; }
    inline ll query(ll f[], int x) { ll r = 0; for (; x; x -= lowbit(x)) r += f[x]; return r; }
}
using namespace BIT;

int main() {
    io >> n >> m;
    For (i, 1, n) io >> A[i], s[i + 1] = s[i] + A[i];
    For (i, 1, n) io >> B[i];
    B[n + 1] = inf;

    For (i, 1, n + 1) stA[i][0] = A[i], stB[i][0] = B[i], pos[i][0] = i;
    For (j, 1, 19) For (i, 1, n - (1 << j) + 2) {
        stA[i][j] = max(stA[i][j - 1], stA[i + (1 << (j - 1))][j - 1]);
        stB[i][j] = stB[i][j - 1]; pos[i][j] = pos[i][j - 1];
        if (cmin(stB[i][j], stB[i + (1 << (j - 1))][j - 1])) pos[i][j] = pos[i + (1 << (j - 1))][j - 1];
    }

    For (i, 1, m) {
        int l, r, x;
        io >> l >> r >> x; b[i] = x;
        int k = __lg(r - l);
        if (max(stA[l][k], stA[r-(1<<k)][k]) > x) { ans[i] = -1; continue; }
        int p = max(int(lower_bound(s + 1, s + r, s[r] - x) - s), l);
        k = __lg(r - p + 1);
        int q = stB[p][k]<stB[r-(1<<k)+1][k]? pos[p][k]: pos[r-(1<<k)+1][k];
        ans[i] = (s[r] - s[q]) * B[q];
        qs[l].pb({x, i, 1}); qs[q].pb({x, i, -1});
    }

    sort(b + 1, b + m + 1); M = unique(b + 1, b + m + 1) - b - 1;

    stk[0] = n + 1; 
    rFor (i, n, 1) {
        S += 1ll * A[i] * B[i];
        while (top && B[stk[top]] > B[i]) {
            int x = stk[top--], y = stk[top];
            int l = lower_bound(b + 1, b + M + 1, s[x] - s[i]) - b, r = upper_bound(b + 1, b + M + 1, s[y] - s[i]) - b;
            upd(K, l, B[i] - B[x]); upd(K, r, B[x] - B[i]);
            upd(C, l, (s[i] - s[x]) * (B[i] - B[x])); upd(C, r, (s[i] - s[x]) * (B[x] - B[i]));
            upd(C, r, (s[y] - s[x]) * (B[i] - B[x]));
        }
        stk[++top] = i;
        for (auto &[x, id, d] : qs[i]) x = lower_bound(b + 1, b + M + 1, x) - b, ans[id] += d * (S + query(K, x) * b[x] + query(C, x));
    }
    For (i, 1, m) printf("%lld\n", ans[i]);

    return 0;
}
