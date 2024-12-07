#include<bits/stdc++.h>
using namespace std;

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
	inline bool operator ~() {return ~c;}
} io;

ll n, k, a[N], b[N], c[N];

int cnt(ll x) {
	int l = 1, r = n, res = 0;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (c[mid] <= x) res = mid, l = mid + 1;
		else r = mid - 1;
	}
	return res;
}

ll get(ll s) {
	ll res = 0;
	For (i, 1, n) {
		ll x = (s - a[i]) / b[i];
		res += cnt(x);
	} 
	return res;
}

int main() {
	io >> n;
	For (i, 1, n) io >> a[i];
	For (i, 1, n) io >> b[i];
	For (i, 1, n) io >> c[i];
	sort(c + 1, c + n + 1);
	io >> k;
	
	ll l = 0, r = 1e18 + 1e9, ans = r;
	while (l <= r) {
		ll mid = (l + r) >> 1;
		if (get(mid) >= k) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	
	printf("%lld", ans);
	
	return 0;	
} 
