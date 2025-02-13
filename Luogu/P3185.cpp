#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 25;

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

int T, n, ans, a[N], SG[N], vis[N * N];

inline void solve() {
    int cnt = 0;
    rFor (i, n, 1) if (a[i]) rFor (j, i - 1, 1) rFor (k, j, 1) if (!(ans ^ SG[i] ^ SG[j] ^ SG[k])) {
        if (!cnt) printf("%d %d %d\n", n - i, n - j, n - k);
        cnt++;
    }
    printf("%d\n", cnt);
}

int main() {
    For (i, 2, N - 1) {
        For (j, 1, i - 1) For (k, 1, j) vis[SG[j] ^ SG[k]] = i;
        For (j, 0, N * N - 1) if (vis[j] ^ i) { SG[i] = j; break; }
    }
    io >> T;
    while (T--) {
        ans = 0;
        io >> n;
        rFor (i, n, 1) io >> a[i];
        For (i, 1, n) if (a[i] & 1) ans ^= SG[i];
        if (!ans) puts("-1 -1 -1\n0");
        else solve();
    }

    return 0;
}
