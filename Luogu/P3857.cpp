#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef long long ll;

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

int n, m, ans = 1;

struct Basis {
    static const int B = 60;
    ll o[B]; bool zero;
    Basis() { memset(o, 0, sizeof o); zero = 0; }
    bool ins(ll x) {
        rFor (i, B - 1, 0) if (x >> i & 1) {
            if (!o[i]) return o[i] = x, 1;
            else x ^= o[i];
        }
        return zero = 1, 0;
    }
} B;

int main() {
    io >> n >> m;
    For (i, 1, m) {
        char st[n + 1];
        scanf("%s", st);
        ll x = 0;
        For (j, 0, n - 1) x = x << 1 | (st[j] == 'O');
        if (B.ins(x)) ans = ans * 2 % 2008;
    }
    printf("%d", ans);

    return 0;
}
