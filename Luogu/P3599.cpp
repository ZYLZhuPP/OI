#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

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

int X, T, n, inv[N];

int main() {
    io >> X >> T;
    while (T--) {
        io >> n;
        if (X == 1) {
            if (n > 1 && n & 1) puts("0");
            else {
                printf("2");
                For (i, 1, n) printf(" %d", i&1? n - i + 1: i - 1);
                puts("");
            }
        } else if (X == 2) {
            if (n == 1) puts("2 1");
            else if (n == 2) puts("2 1 2");
            else if (n == 4) puts("2 1 3 2 4");
            else {
                bool flag = 1;
                For (i, 2, n - 1) if (n % i == 0) flag = 0;
                if (!flag) puts("0");
                else {
                    printf("2 1");
                    inv[1] = 1;
                    For (i, 2, n) inv[i] = 1ll * (n - n / i) * inv[n % i] % n, printf(" %d", 1 + inv[i - 1]);
                    puts("");
                }
            }
        }
    }

    return 0;
}
