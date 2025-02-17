#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int n, K, L, m;
ll ans;
map<int, array<int, 2 > > mp;
array<int, 2 > q[N];

int main() {
    io >> n >> K >> L;
    int l, t, r;
    For (i, 1, n) {
        io >> l >> t >> r;
        mp[l][0]++; mp[r + 1][0]--;
        if (l + t < r + 1) mp[l + t][1]++, mp[r + 1][1]--;
    }
    int lst = -1, a = 0, b = 0;
    for (auto &[x, d] : mp) {
        if (~lst) q[++m] = {x - lst, a>=K? b: 0};
        lst = x, a += d[0], b += d[1];
    }
    ll s = 0; r = 0;
    For (i, 1, m) {
        while (r < m && q[r + 1][0] <= L) L -= q[++r][0], s += 1ll * q[r][0] * q[r][1];
        cmax(ans, s + (r<m? 1ll * L * q[r + 1][1]: 0));
        if (r >= i) L += q[i][0], s -= 1ll * q[i][0] * q[i][1]; else r = i;
    }
    s = 0; l = m + 1;
    rFor (i, m, 1) {
        while (l > 1 && q[l - 1][0] <= L) L -= q[--l][0], s += 1ll * q[l][0] * q[l][1];
        cmax(ans, s + (l>1? 1ll * L * q[l - 1][1]: 0));
        if (l <= i) L += q[i][0], s -= 1ll * q[i][0] * q[i][1]; else l = i;
    }
    printf("%lld", ans);

    return 0;
}
