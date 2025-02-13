#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = l; i <= r; ++i)
typedef long long ll;
const int N = 1e5 + 5, M = 345;
const ll Mo = 998244353;

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
	inline bool operator ~ () {return ~c;}
} io;

int n, a[N], bl[M], br[M], cnt[M][N], m, S, s[N], Q;
ll l, r, ans, inv[N], f[M][M];

void init() {
    inv[0] = inv[1] = 1;
    For (i, 2, N - 1) inv[i] = (Mo - Mo / i) * inv[Mo % i] % Mo;

    For (i, 0, m) bl[i] = i * S, br[i] = (i + 1) * S - 1;
    bl[0] = 1; br[m] = n;
    For (i, 0, m) {
        memset(s, 0, sizeof(s));
        ll S = 1;
        For (j, i, m) {
            For (k, bl[j], br[j]) {
                ll x = ++s[a[k]];
                S = S * inv[x] % Mo * (x + 1) % Mo;
            }
            f[i][j] = S;
        }
    }
    
    For (i, 0, m) {
        For (j, bl[i], br[i]) cnt[i][a[j]]++;
        memcpy(cnt[i + 1], cnt[i], sizeof(cnt[i]));
    }
    memset(s, 0, sizeof(s));
}

ll get(int l, int r) {
    ll res = 1;
    For (i, l, r) {
        ll x = ++s[a[i]];
        res = res * inv[x] % Mo * (x + 1) % Mo;
    }
    For (i, l, r) s[a[i]] = 0;
    return res;
}

ll solve(int l, int r) {
    ll res = f[l / S + 1][r / S - 1];
    int L = l / S, R = r / S, rr = br[L], ll = bl[R];
    For (i, l, rr) {
        ll x = ++s[a[i]] + cnt[R - 1][a[i]] - cnt[L][a[i]];
        res = res * inv[x] % Mo * (x + 1) % Mo;
    }
    For (i, ll, r) {
        ll x = ++s[a[i]] + cnt[R - 1][a[i]] - cnt[L][a[i]];
        res = res * inv[x] % Mo * (x + 1) % Mo;
    }
    For (i, l, rr) s[a[i]] = 0;
    For (i, ll, r) s[a[i]] = 0;
    return res;
}

int main() {
    io >> n;
    S = sqrt(n); m = n / S;
    For (i, 1, n) io >> a[i];
    init();

    io >> Q;
    while (Q--) {
        io >> l >> r; l ^= ans, r ^= ans;
        if (l / S + 1 > r / S - 1) ans = get(l, r);
        else ans = solve(l, r);
        printf("%lld\n", ans);
    }
    return 0;
}
