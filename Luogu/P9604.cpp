#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e3 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

int n, m, x, cnt[N], pos[N], w[N], s[N];
ll val[N][N], f[N][N], t[N][N];
array<ll, 3 > pt[N];

inline void sort(int k) {
    For (i, 1, n) pt[i] = {t[k][i], w[i], i};
    sort(pt + 1, pt + n + 1);
    For (i, 1, n) pos[i] = pt[i][2];
    For (i, 1, n) if (w[pos[i]] > x) val[k][++cnt[k]] = t[k][pos[i]];
}

void init(int L, int O, vector<ll > T, vector<int > W, int X, int M, vector<int > S) {
    memset(f, -1, sizeof f);
    n = O; m = M; x = X;
    For (i, 1, n) w[i] = W[i - 1], t[1][i] = T[i - 1];
    For (i, 1, m) s[i] = S[i - 1];
    For (i, 2, m) {
        sort(i - 1);
        For (j, 1, n) t[i][j] = t[i - 1][j] + 1ll * (s[i] - s[i - 1]) * w[j];
        ll mx = 0;
        For (j, 1, n) cmax(t[i][pos[j]], mx), mx = t[i][pos[j]];
    }
    sort(m);
}

inline ll query(int a, ll b) {
    if (a == m) return b;
    int p = lower_bound(val[a] + 1, val[a] + cnt[a] + 1, b) - val[a];
    if (val[a][p] == b && ~f[a][p]) return f[a][p];
    int l = a + 1, r = m, res = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (val[mid][p - 1] >= b + 1ll * x * (s[mid] - s[a])) r = mid - 1, res = mid;
        else l = mid + 1;
    }
    ll ans = ~res? query(res, val[res][p - 1]): b + 1ll * x * (s[m] - s[a]);
    if (val[a][p] == b) f[a][p] = ans;
    return ans;
}

ll arrival_time(ll Y) { return query(1, Y); }