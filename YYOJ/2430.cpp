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

int n, K, a[N];
ll s[N], ans;
vector<int > q;

int main() {
    io >> n >> K;
    For (i, 1, n) io >> a[i], s[i] = s[i - 1] + a[i];
    For (i, 1, n) {
        q.pb(i);
        for (auto &x : q) a[x] = __gcd(a[x], a[i]);
        vector<int > p; int lst = 0;
        for (auto &x : q) if (a[x] > lst) p.pb(x), lst = a[x], cmax(ans, (i - x + 1 >= K) * (s[i] - s[x - 1]) * lst);
        swap(p, q);
    }
    printf("%lld", ans);

    return 0;
}
