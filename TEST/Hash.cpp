#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef unsigned long long ull;
typedef pair<ull, ull > P;
typedef __int128 lll;
const int N = 1e6 + 5, S = 3e3 + 5;

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
	inline bool operator ~ () { return ~c; }
} io;

int n, ans;
char s[S];
unordered_map<ull, set<ull > > mp;

namespace Hash {
    const ull base = 131, Mo = 1e17 + 1921;
    ull h1[S], h2[S], _1[S], _2[S];
    inline void init() {
        _1[0] = _2[0] = 1;
        For (i, 1, S - 1) _1[i] = _1[i - 1] * base, _2[i] = (_2[i - 1] * base) % Mo;
    }
    inline void init(char s[]) {
        init();
        int n = strlen(s + 1);
        For (i, 1, n) {
            int c = s[i];
            h1[i] = h1[i - 1] * base + c;
            h2[i] = (h2[i - 1] * base + c) % Mo;
        }
    }
    inline P ha(int l, int r) {
        return P(h1[r] - h1[l - 1] * _1[r - l + 1], (h2[r] - (lll)h2[l - 1] * _2[r - l + 1] % Mo + Mo) % Mo);
    }
    inline P ha(char s[]) {
        int n = strlen(s + 1);
        ull x = 0, y = 0;
        For (i, 1, n) {
            int c = s[i];
            x = x * base + c;
            y = (y * base + c) % Mo;
        }
        return P(x, y);
    }
}
using namespace Hash;

int main() {
    io >> n;
    For (i, 1, n) {
        scanf("%s", s + 1);
        init(s);
        int l, r;
        io >> l >> r;
        auto [x, y] = ha(l, r);
        if (!mp[x].count(y)) ans++, mp[x].insert(y);
    }
    printf("%d", ans);

    return 0;
}
