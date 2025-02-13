#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef long long ll;
const int N = 3e6 + 5;

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
} io;

ll ans;
int n, a[N], l[N], r[N], st[N], t;

int main() {
	io >> n;
	For (i, 1, n) {
		r[i] = n + 1;
		io >> a[i];
	}
	For (i, 1, n) {
		while (t && a[st[t]] <= a[i]) t--;
		if (t) l[i] = st[t];
		st[++t] = i;
	}
	t = 0;
	rFor (i, n, 1) {
		while (t && a[st[t]] >= a[i]) t--;
		if (t) r[i] = st[t];
		st[++t] = i;
	}
	
	For (i, 1, n) 
		ans += 1ll * (n - i + 1) * i - 1ll * (r[i] - i) * (i - l[i]);
	
	printf("%lld", ans);
	
	return 0;
} 
