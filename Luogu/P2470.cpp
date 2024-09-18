#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 55;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, f[N][N][2];
char s[N];

inline bool ok(int l, int r) {
    if ((r - l + 1) & 1) return 0;
    int mid = (l + r) >> 1;
    For (i, 1, r - mid) if (s[l + i - 1] ^ s[mid + i]) return 0;
    return 1;
}

int main() {
    memset(f, 31, sizeof f);
    scanf("%s", s + 1);
    n = strlen(s + 1);
    For (i, 1, n) f[i][i][0] = f[i][i][1] = 1;
    For (len, 2, n) {
        For (l, 1, n - len + 1) {
            int r = l + len - 1;
            For (k, l, r - 1) cmin(f[l][r][0], f[l][k][0] + r - k), cmin(f[l][r][1], min(f[l][k][0], f[l][k][1]) + min(f[k + 1][r][0], f[k + 1][r][1]) + 1);
            if (ok(l, r)) cmin(f[l][r][0], f[l][(l + r) >> 1][0] + 1);
        }
    }
    printf("%d", min(f[1][n][0], f[1][n][1]));

    return 0;
}
