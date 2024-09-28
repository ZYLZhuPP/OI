#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e5 + 5;
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

namespace BIT {
    ll o1[N], o2[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(ll o[], int x, ll v) { for (; x < N; x += lowbit(x)) cmin(o[x], v); }
    inline ll query(ll o[], int x) { ll r = o[0]; for (; x; x -= lowbit(x)) cmin(r, o[x]); return r; }
}
using namespace BIT;

int n, a[N], b[N], B, cnt[N], ed[N];
bool on[N];
ll ans, s[N], f[N];
set<int > se;

int main() {
    srand(time(0));
    memset(o1, 63, sizeof o1);
    memset(o2, 63, sizeof o2);
    io >> n;
    For (i, 1, n) io >> a[i], b[i] = a[i];
    sort(b + 1, b + n + 1); B = unique(b + 1, b + n + 1) - b - 1;
    For (i, 1, B) ed[i] = n + 1;
    For (i, 1, n) {
        int x = a[i] = lower_bound(b + 1, b + B + 1, a[i]) - b;
        if (!cnt[x]++) on[i] = 1;
        else if (cnt[x] == 2) ed[x] = i;
        s[i] = s[i - 1] + i;
    }
    For (i, 1, n) if (on[i]) {
        int x = a[i];
        auto it = se.upper_bound(b[x]);
        if (it != se.end()) cmin(f[i], *it - b[x] - (s[ed[x] - 1] - s[i - 1]));
        if (it != se.begin()) it = prev(it), cmin(f[i], b[x] - *it - (s[ed[x] - 1] - s[i - 1]));
        se.insert(b[x]);
    }
    rFor (i, n, 1) if (on[i]) {
        int x = a[i];
        cmin(f[i], b[x] - s[ed[x] - 1] + query(o1, x - 1));
        cmin(f[i], query(o2, B - x) - b[x] - s[ed[x] - 1]);
        upd(o1, x, s[i - 1] - b[x]);
        upd(o2, B - x + 1, s[i - 1] + b[x]);
    }
    For (i, 1, n) cmin(ans, f[i]);
    int x = 0;
    For (i, 1, n) x += on[i], ans += 1ll * x * i;
    printf("%lld", ans);

    return 0;
}
