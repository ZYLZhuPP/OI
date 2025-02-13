#include<bits/stdc++.h>
using namespace std; 

typedef long long ll;

const int N = 1e7 + 5;

struct IO {
	char c, f;
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

int n, lc[N], rc[N], q[N], t;
ll Mo, lm[N], rm[N], ans, a[N], mul[N];

namespace GenHelper {
	unsigned z1, z2, z3, z4, b;
	unsigned rand_() {
		b = ((z1 << 6) ^ z1) >> 13;
		z1 = ((z1 & 4294967294U) << 18) ^ b;
		b = ((z2 << 2) ^ z2) >> 27;
		z2 = ((z2 & 4294967288U) << 2) ^ b;
		b = ((z3 << 13) ^ z3) >> 21;
		z3 = ((z3 & 4294967280U) << 7) ^ b;
		b = ((z4 << 3) ^ z4) >> 12;
		z4 = ((z4 & 4294967168U) << 13) ^ b;
		return (z1 ^ z2 ^ z3 ^ z4);
	}
}

unsigned s;
int l, r;
void get (int n, unsigned s, int l, int r) {
	using namespace GenHelper;
	z1 = s;
	z2 = unsigned((~s) ^ 0x233333333U);
	z3 = unsigned(s ^ 0x1234598766U);
	z4 = (~s) + 51;
	for (int i = 1; i <= n; i ++) {
		int x = rand_() & 32767;
		int y = rand_() & 32767;
		a[i] = l + (x * 32768 + y) % (r - l + 1);
	}
}

void dfs(int u) {
    if (!u) return;
    dfs(lc[u]); dfs(rc[u]);
    ans = (ans + (rm[lc[u]] + 1) * (lm[rc[u]] + 1) % Mo * a[u] % Mo * a[u] % Mo) % Mo;
    mul[u] = mul[lc[u]] * mul[rc[u]] % Mo * a[u] % Mo;
    lm[u] = (lm[lc[u]] + mul[lc[u]] * a[u] % Mo * (lm[rc[u]] + 1) % Mo) % Mo;
    rm[u] = (rm[rc[u]] + mul[rc[u]] * a[u] % Mo * (rm[lc[u]] + 1) % Mo) % Mo;
}

int main() {
	io >> n >> s >> l >> r >> Mo;
	get(n, s, l, r);
	
	mul[0] = 1;
	
	for (int i = 1; i <= n; ++i) {
		while (t && a[q[t]] < a[i]) --t;
		lc[i] = q[t + 1]; rc[q[t]] = i;
		q[++t] = i; q[t + 1] = 0;
	}
	
	dfs(q[1]);
	
	printf("%lld", ans);
	
	return 0;
}

