#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 1e7 + 5;
int Mo;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

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

int n, _2[N], r[N], sr[N], ans;

int main() {
	io >> n >> Mo;
	_2[0] = 1;
	For (i, 1, n) _2[i] = mo(_2[i - 1] << 1);
	rFor (i, n, 1) {
		if (2 * i > n) r[i] = _2[n - i];
		else r[i] = mo(sr[i + 1] - sr[2 * i]);
		sr[i] = mo(sr[i + 1] + r[i]);
	}
	For (i, 1, n) add(ans, ml(i, ml(_2[i / 2 + (i == n)], r[i])));
	printf("%d", ans);
	
	return 0;
} 
