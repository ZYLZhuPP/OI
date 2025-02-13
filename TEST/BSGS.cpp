#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
int Mo;
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }

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

int a, b, ans;

inline int BSGS(int a, int b) {
    if (Mo == 1) return 0;
    b %= Mo; if (!a) return !b? 0: -1; else if (b == 1) return 0;
    a %= Mo; if (!a) return !b? 1: -1;
    unordered_map<int, int > mp;
    int B = ceil(sqrt(Mo)), x = 1;
    For (i, 1, B) mul(x, a), mp[ml(b, x)] = i;
    int y = 1;
    For (i, 1, B) { mul(y, x); if (mp[y]) return i * B - mp[y]; }
    return -1;
}

int main() {
    io >> Mo >> a >> b;
    ans = BSGS(a, b);
    if (~ans) printf("%d", ans);
    else puts("no solution");

    return 0;
}
