#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;

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

int T, n, s[N];
char a[N];
array<int, 2 > L[N], R[N];

int main() {
    io >> T;
    while (T--) {
        io >> n;
        scanf("%s", a + 1);
        int l = 0, r = 0, mx = 0, pos = 0;
        L[0] = {0, 0};
        For (i, 1, 2 * n) {
            s[i] = s[i - 1] + (a[i]=='('? 1: -1), L[i] = max(L[i - 1], {s[i], i});
            if (s[i] < 0) {
                if (!l) l = i;
                r = i;
            }
            if (s[i] > mx) mx = s[i], pos = i;
        }
        R[2 * n] = {0, 2 * n};
        rFor (i, 2 * n - 1, 0) R[i] = max(R[i + 1], {s[i], i});
        if (!l) puts("0");
        else if (mx <= L[l - 1][0] + R[r + 1][0]) {
            puts("1"); printf("%d %d\n", L[l - 1][1] + 1, R[r + 1][1]);
        } else {
            puts("2"); printf("1 %d\n", pos); printf("%d %d\n", pos + 1, 2 * n);
        }
    }

    return 0;
}
