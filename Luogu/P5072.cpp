#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;
int Mo;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

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

int n, m, B, _2[350], _2B[350], tot[N], a[N], val[350], t, cnt[N], ans[N];
ll s[350];

struct OP {
    int l, r, p, id;
    bool operator < (const OP &a) const { return l/B^a.l/B? l<a.l: r<a.r; }
} qs[N];

inline void init_pow() {
    _2[0] = 1; For (i, 1, B) _2[i] = mo(_2[i - 1] << 1);
    _2B[0] = 1; For (i, 1, B + 2) _2B[i] = ml(_2B[i - 1], _2[B]);
}

inline int pow2(int x) { return ml(_2B[x / B], _2[x % B]); }

inline int solve(int n) {
    int res = 0;
    init_pow();
    For (i, 1, B) add(res, ml(mo(pow2(n) - pow2(n - i)), mo(s[i])));
    For (i, 1, t) add(res, ml(mo(pow2(n) - pow2(n - cnt[val[i]])), val[i]));
    return res;
}

inline void upd(int x, int d) {
    if (tot[x] <= B) s[cnt[x]] -= x, cnt[x] += d, s[cnt[x]] += x;
    else cnt[x] += d;
}

int main() {
    io >> n >> m;
    For (i, 1, n) io >> a[i], tot[a[i]]++;
    B = sqrt(n);
    For (i, 1, 1e5) if (tot[i] > B) val[++t] = i;
    int l, r, p;
    For (i, 1, m) io >> l >> r >> p, qs[i] = {l, r, p, i};
    sort(qs + 1, qs + m + 1);
    l = 1, r = 0;
    For (i, 1, m) {
        auto [x, y, p, id] = qs[i]; Mo = p;
        while (l > x) upd(a[--l], 1);
        while (r < y) upd(a[++r], 1);
        while (l < x) upd(a[l++], -1);
        while (r > y) upd(a[r--], -1);
        ans[id] = solve(y - x + 1);
    }
    For (i, 1, m) printf("%d\n", ans[i]);

    return 0;
}
