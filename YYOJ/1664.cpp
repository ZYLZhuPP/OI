#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5, Mo = 1e9 + 7;
inline int mo(int &x) { return x -= x>=Mo? Mo: 0; }
inline void add(int &x, const int &y) { mo(x += y); }

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
	inline IO& operator >> (char &x) {
		while ((c = gc()) < 33 && ~c);
		x = c; return *this;
	}
	inline bool operator ~() {return ~c;}
} io;

int n, a[N], f[N], s[N];

int main() {
	io >> n;
	For (i, 1, n) io >> a[i];
	s[a[1]] = 1;
	For (i, 1, n) {
		f[i] = s[a[i]];
		if (a[i + 1] ^ a[i]) add(s[a[i + 1]], f[i]);
	}
	
	printf("%d", f[n]);
	
	return 0;
} 
