#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 4e4 + 5;
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
	inline bool operator ~ () { return ~c; }
} io;

int n, m, a[N], B, cnt[205][N], pos[205], f[N];

int main() {
    io >> n >> m;
    For (i, 1, n) io >> a[i];
    B = sqrt(n);
    memset(f, 31, sizeof f);
    f[0] = 0;
    For (i, 1, n) {
        For (j, 1, B) {
            cnt[j][a[i]]++;
            if (cnt[j][a[i]] == 1) {
                cnt[j][0]++;
                if (cnt[j][0] > j) {
                    while (--cnt[j][a[++pos[j]]]);
                    cnt[j][0]--;
                }
            }
            cmin(f[i], f[pos[j]] + j * j);
        }
    }
    printf("%d", f[n]);

    return 0;
}
