#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;

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

namespace BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, int d) { for (; x < N; x += lowbit(x)) o[x] += d; }
    inline int query(int x) { int r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
}
using namespace BIT;

int n, ans1, ans2;
ll K, a[N], b[N], c[N];
vector<array<int, 2 > > A, B, C;

inline ll solve1(int k) {
    memset(o, 0, sizeof o);
    ll res = 0;
    int n = A.size(), m = B.size();
    For (i, 0, n - 1) a[i] = A[i][0] + 1ll * A[i][1] * k, c[i + 1] = a[i];
    For (i, 0, m - 1) b[i] = B[i][0] + 1ll * B[i][1] * k, c[n + i + 1] = b[i];
    sort(c + 1, c + n + m + 1); int tot = unique(c + 1, c + n + m + 1) - c - 1;
    m--;
    rFor (i, n - 1, 0) {
        while (~m && A[i][0] < B[m][0]) upd(lower_bound(c + 1, c + tot + 1, b[m]) - c, 1), m--;
        res += query(lower_bound(c + 1, c + tot + 1, a[i]) - c);
    }
    return res;
}

inline ll solve2(vector<array<int, 2 > > A, int k) {
    memset(o, 0, sizeof o);
    ll res = 0;
    int n = A.size();
    For (i, 0, n - 1) a[i] = A[i][0] + 1ll * A[i][1] * k, c[i + 1] = a[i];
    sort(c + 1, c + n + 1); int tot = unique(c + 1, c + n + 1) - c - 1;
    rFor (i, n - 1, 0) {
        int x = lower_bound(c + 1, c + tot + 1, a[i]) - c;
        res += query(x);
        upd(x, 1);
    }
    return res;
}

int main() {
    io >> n >> K;
    int x, v;
    For (i, 1, n) io >> x >> v, v>0? A.pb({x, v}): (B.pb({x, v}), C.pb({-x, -v}));
    sort(A.begin(), A.end()); sort(B.begin(), B.end()); sort(C.begin(), C.end());
    int l = 1, r = 2e9; ans1 = -1;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (solve1(m) >= K) ans1 = m, r = m - 1;
        else l = m + 1;
    }
    l = 1, r = 2e9; ans2 = -1;
    while (l <= r) {
        int m = (l + r) >> 1;
        if (solve2(A, m) + solve2(C, m) >= K) ans2 = m, r = m - 1;
        else l = m + 1;
    }
    printf("%d\n%d", ans1, ans2);

    return 0;
}
