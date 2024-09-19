#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 3e5 + 5;

int n, m, v, a[N], lg2[N], mn[N][20], mx[N][20];
ll s[N], ans[N];
vector<array<int, 3 > > q[N];

namespace IO {
    const int P = (1ll << 31) - 1;
    int N, M, V, A, B;
    void GetSeed(int &n, int &m, int &v) {
        scanf("%d%d%d%d%d", &N, &M, &V, &A, &B);
        n = N, m = M, v = V;
    }
    inline int GetInt() {
        A = ((A ^ B) + (B >> 16) + (B << 16)) & P;
        B = ((A ^ B) + (A >> 16) + (A << 16)) & P;
        return (A ^ B) % V;
    }
    inline int GetPos() {
        A = ((A ^ B) + (B >> 16) + (B << 16)) & P;
        B = ((A ^ B) + (A >> 16) + (A << 16)) & P;
        return (A ^ B) % N + 1;
    }
    inline void GetSeg(int &l, int &r) {
        l = GetPos(), r = GetPos();
        if (l > r) std::swap(l, r);
    }
}

namespace BIT {
    struct P {
        ll s; int c;
        P operator + (const P &a) const { return P{s + a.s, c + a.c}; }
    } o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, const P &d) { for (x++; x < N; x += lowbit(x)) o[x] = o[x] + d; }
    inline P query(int x) { P r{0, 0}; for (x++; x; x -= lowbit(x)) r = r + o[x]; return r; }
}
using namespace BIT;

inline int Min(int x, int y) { return a[x]<a[y]? x: y; }
inline int Max(int x, int y) { return a[y]>a[x]? y: x; }

inline void init() {
    lg2[1] = 0; For (i, 2, n) lg2[i] = lg2[i >> 1] + 1;
    For (i, 1, n) mn[i][0] = mx[i][0] = i;
    For (j, 1, 19) For (i, 1, n - (1 << j) + 1) mn[i][j] = Min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]), mx[i][j] = Max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
}

inline int Gmin(int l, int r) { if (l > r) return v; int k = lg2[r - l + 1]; return Min(mn[l][k], mn[r - (1 << k) + 1][k]); }
inline int Gmax(int l, int r) { if (l > r) return -1; int k = lg2[r - l + 1]; return Max(mx[l][k], mx[r - (1 << k) + 1][k]); }

inline void solve(int l, int r, int lmx, int rmn, int id) {
    if (l > r) return;
    int x = Gmax(l, r);
    if (a[x] <= lmx) {
        ans[id] += 1ll * (r - l + 1) * rmn - (s[r] - s[l - 1]);
        q[r].pb({lmx + rmn, 1, id}); q[l - 1].pb({lmx + rmn, -1, id});
        return;
    }
    ans[id] += min(a[x] - max(lmx, a[Gmax(l, x - 1)]), rmn - a[x]);
    solve(l, x - 1, lmx, rmn, id); solve(x + 1, r, a[x], rmn, id);
}

inline void Solve(int l, int r, int lmx, int id) {
    if (l > r) return;
    int x = Gmin(l, r); ans[id] += ~lmx? a[x] - lmx: 0;
    Solve(x + 1, r, max(lmx, a[Gmax(l, x)]), id);
    solve(l, x - 1, lmx, a[x], id);
}

int main()
{
    IO::GetSeed(n, m, v);
    For (i, 1, n) a[i] = IO::GetInt(), s[i] = s[i - 1] + a[i];
    init();
    For (i, 1, m) {
        int l, r; IO::GetSeg(l, r);
        Solve(l, r, -1, i);
    }
    For (i, 1, n) {
        upd(a[i], {a[i], 1});
        for (auto &[x, k, id] : q[i]) {
            auto [s, c] = query(x / 2);
            ans[id] += k * (2 * s - 1ll * c * x);
        }
    }
    For (i, 1, m) printf("%lld\n", ans[i]);

    return 0;
}
