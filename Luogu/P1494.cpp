#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;

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

int n, S, m, c[N], cnt[N];
ll ans, A[N], B[N];

struct OP {
    int x, y, t;
    bool operator < (const OP &a) const { return x/S^a.x/S? x/S<a.x/S: y<a.y; }
};
vector<OP > ops;

int main() {
    io >> n >> m;
    S = sqrt(n);
    For (i, 1, n) io >> c[i];
    int l, r;
    For (i, 1, m) io >> l >> r, ops.pb({l, r, i});
    sort(ops.begin(), ops.end());
    l = 1; r = 0;
    for (auto &[x, y, id]: ops) {
        while (l > x) ans += cnt[c[--l]]++;
        while (r < y) ans += cnt[c[++r]]++;
        while (l < x) ans -= --cnt[c[l++]];
        while (r > y) ans -= --cnt[c[r--]];
        A[id] = ans; B[id] = 1ll * (y - x) * (y - x + 1) / 2;
        if (!B[id]) B[id] = 1;
        ll g = __gcd(A[id], B[id]);
        A[id] /= g; B[id] /= g;
    }
    For (i, 1, m) printf("%lld/%lld\n", A[i], B[i]);

    return 0;
}