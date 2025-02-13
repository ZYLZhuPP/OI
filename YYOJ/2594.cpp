#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1.5e5 + 5;

struct IO {
	char c; int f;
#define gc() (getchar())
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
    ll o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x, int d) { for (; x < N; x += lowbit(x)) o[x] += d; }
    inline ll query(int x) { ll r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
}
using namespace BIT;

int n, m, q, B, a[N], b[N], cnt[N];
ll ans;
vector<int > pos[N], R;
vector<ll > s[N];

inline ll solve(int x, int l, int r) {
    int L = lower_bound(pos[x].begin(), pos[x].end(), l) - pos[x].begin();
    int R = upper_bound(pos[x].begin(), pos[x].end(), r) - pos[x].begin() - 1;
    if (L > R) return 0;
    int n = pos[x].size();
    L = (L + n - cnt[x] % n) % n; R = (R + n - cnt[x] % n) % n;
    return s[x][R + 1] - s[x][L] + (L>R? s[x][n]: 0);
}

int main() {
    io >> n >> m >> q; B = 2 * sqrt(n);
    For (i, 1, n) io >> b[i], pos[b[i]].pb(i);
    For (i, 1, n) io >> a[i];
    For (i, 1, m) {
        if ((int)pos[i].size() < B) for (auto &x : pos[i]) upd(x, a[x]);
        else {
            R.pb(i);
            s[i].pb(0);
            for (auto &x : pos[i]) s[i].pb(s[i].back() + a[x]);
        }
    }
    int op, l, r, x;
    while (q--) {
        io >> op;
        if (op == 1) {
            io >> l >> r;
            ans = query(r) - query(l - 1);
            for (auto &x : R) ans += solve(x, l, r);
            printf("%lld\n", ans);
        } else {
            io >> x;
            int n = pos[x].size();
            if (n < B) {
                For (i, 0, n - 1) b[pos[x][i]] = a[pos[x][(i + n - 1) % n]];
                for (auto &p : pos[x]) upd(p, b[p] - a[p]), a[p] = b[p];
            } else cnt[x]++;
        }
    }

    return 0;
}
