#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); i++)
#define rFor(i, r, l) for (int i = (r); i >= (l); i--)
#define pb push_back
typedef long long ll;
const int N = 1e5 + 5, _N = 355;
inline void cmax(ll &x, const ll y) { x = y>x? y: x; }

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

int n, q, O, S, B;
int a[N], b[N], bl[_N], br[_N], be[N], cnt[N];
ll Ans[N], ans;

struct OP {
    int x, y, id;
    bool operator < (const OP &a) const { return y < a.y; }
};
vector<OP > ops[_N];

void init() {
    sort(b + 1, b + n + 1); O = unique(b + 1, b + n + 1) - b - 1;
    For (i, 1, n) a[i] = lower_bound(b + 1, b + O + 1, a[i]) - b;
    S = sqrt(n);
    B = n / S; if (B * S < n) B++;
    For (i, 1, B) bl[i] = br[i - 1] + 1, br[i] = i * S;
    br[B] = n;
    For (i, 1, B) For (j, bl[i], br[i]) be[j] = i;
}

int main() {
    io >> n >> q;
    For (i, 1, n) io >> a[i], b[i] = a[i];
    init();
    int l, r;
    For (i, 1, q) {
        io >> l >> r;
        if (be[l] == be[r]) {
            For (j, l, r) cmax(Ans[i], 1ll * (++cnt[a[j]]) * b[a[j]]);
            For (j, l, r) cnt[a[j]]--;
        } else ops[be[l]].pb({l, r, i});
    }
    For (L, 1, B - 1) {
        sort(ops[L].begin(), ops[L].end());
        r = br[L];
        ans = 0;
        for (auto &[x, y, id] : ops[L]) {
            while (r < y) r++, cmax(ans, 1ll * (++cnt[a[r]]) * b[a[r]]);
            Ans[id] = ans;
            For (j, x, br[L]) cmax(Ans[id], 1ll * (++cnt[a[j]]) * b[a[j]]);
            For (j, x, br[L]) cnt[a[j]]--;
        }
        For (j, br[L] + 1, r) cnt[a[j]]--;
    }
    For (i, 1, q) printf("%lld\n", Ans[i]);

    return 0;
}