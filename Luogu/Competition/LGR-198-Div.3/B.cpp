#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5;

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
	inline bool operator ~ () { return ~c; }
} io;

int n, m, k, T, a[N][N];

int main() {
    io >> T;
    while (T--) {
        io >> n >> m >> k;
        For (i, 1, min(k, min(n, m))) a[i][i] = 1;
        k -= min(k, min(n, m));
        For (i, 1, n) {
            For (j, 1, m) {
                if (!a[i][j] && k) a[i][j] = 1, k--;
                if (a[i][j]) putchar('S'); else putchar('.');
                a[i][j] = 0;
            }
            puts("");
        }
    }

    return 0;
}
