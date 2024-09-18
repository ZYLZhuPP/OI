#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 7.5e5 + 5;

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

int n, Q, h[N], R[N], L[N], q[N], t, l, r;
ll f[N], g[N];

inline ll solve(int l, int r) {
//cout << l << " " << r << endl;
    if (r < l) return 0;
    if (r == R[l] - 1 && ~f[l]) return f[l];
    if (l == L[r] + 1 && ~g[r]) return g[r];
    
    vector<int > a;
    for (int i = l; i <= r; i = R[i]) a.pb(i);
    int n = a.size(), x = a[n - 1];
    ll sum = 1ll * h[x] * (r - x + 1), res = LLONG_MAX;
    rFor (i, n - 2, 0) {
//    cout << solve(a[i], a[i + 1] - 1) << endl;
        res = min(res, sum + 1ll * h[a[i]] * (a[i] - l) + solve(a[i], a[i + 1] - 1));
        sum += 1ll * h[a[i]] * (a[i + 1] - a[i]);
    }
    res = min(res, sum);
    
    vector<int > b;
    for (int i = r; i >= l; i = L[i]) b.pb(i);
    n = b.size(), x = b[n - 1];
    sum = 1ll * h[x] * (x - l + 1);
    rFor (i, n - 2, 0) {
//    cout << solve(a[i], a[i + 1] - 1) << endl;
        res = min(res, sum + 1ll * h[b[i]] * (r - b[i]) + solve(b[i + 1] + 1, b[i]));
        sum += 1ll * h[b[i]] * (b[i] - b[i + 1]);
    }
    res = min(res, sum);
    
    if (r == R[l] - 1) f[l] = res;
    if (l == L[r] + 1) g[r] = res;
    return res;
}

int main() {
    memset(f, -1, sizeof f); memset(g, -1, sizeof g);
    io >> n >> Q;
    For (i, 1, n) {
        io >> h[i];
        while (t && h[q[t]] < h[i]) R[q[t--]] = i;
        q[++t] = i;
    }
    while (t) R[q[t--]] = n + 1;
    rFor (i, n, 1) {
        while (t && h[q[t]] <= h[i]) L[q[t--]] = i;
        q[++t] = i;
    }
    while (Q--) {
        io >> l >> r; l++; r++;
        printf("%lld\n", solve(l, r));
    }

    return 0;
}
