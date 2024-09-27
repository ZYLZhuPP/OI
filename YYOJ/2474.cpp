#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef vector<int > vec;
const int N = 75;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, m, K, w[N];
ll ans = 1e18;
map<vec, ll > f, g;

int main() {
    io >> n >> m; K = n / m;
    For (i, 1, n) io >> w[i];
    sort(w + 1, w + n + 1);
    f[vec(m + 1, 0)] = 0;
    For (i, 1, n) {
        swap(f, g); f.clear();
        for (auto [a, b] : g) {
            For (j, 1, m) if (a[j] < K) {
                if (a[j] > a[0] && w[i] == w[i - 1]) continue;
                vec c = a; ll d = b;
                if (!c[j]++) d -= w[i];
                if (c[j] == K) d += w[i];
                c[0] = 0; sort(c.begin(), c.end()); c[0] = a[j];
                if (f.count(c)) cmin(f[c], d);
                else f[c] = d;
            }
        }
    }
    for (auto [a, b] : f) cmin(ans, b);
    printf("%lld", ans);

    return 0;
}
