#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5, lgN = 22;

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
	inline bool operator ~ () {return ~c;}
} io;

int n, x, c[N], ans, s[N], xo[N], _2[lgN], f[N << 1][lgN];

void init() {
    _2[0] = 1;
    for (int i = 1; i < lgN; ++i) _2[i] = _2[i - 1] << 1;
    for (int i = 1; i <= n; ++i) xo[i] = xo[i - 1] ^ (i * c[i]);
    for (int i = 1; i <= n; ++i) s[i] = s[i - 1] ^ c[i];
    for (int i = 0; 1 << i <= n; ++i) {
        for (int j = n - (1 << i); j >= 1; --j) 
            f[j][i] = f[j + _2[i + 1]][i] ^ s[min(j + _2[i + 1] - 1, n)] ^ s[j + _2[i]];
    }
}

int main() {
    io >> n;
    for (int i = 1; i <= n; ++i) {
        io >> x;
        c[x] ^= 1;
    }

    init();

    for (int i = 2; i <= n + 1; ++i) {
        ans = xo[i - 1];
        for (int j = 0; 1 << j < i; ++j) if (f[i][j]) ans ^= 1 << j;
        if (ans) printf("Alice ");
        else printf("Bob ");
    }

    return 0;
}
