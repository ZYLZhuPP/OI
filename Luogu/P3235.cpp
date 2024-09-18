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

int T, F, n, vis[N], SG[N];

int main() {
    io >> T >> F;
    For (i, F, N - 1) {
        for (int l = 2, r; l <= i; l = r + 1) {
            r = i / (i / l);
            For (m, l, min(l + 1, r)) {
                int x = 0;
                if (i % m & 1) x ^= SG[i / m + 1];
                if ((m - i % m) & 1) x ^= SG[i / m];
                vis[x] = i;
            }
        }
        For (j, 0, N - 1) if (vis[j] ^ i) { SG[i] = j; break; }
    }
    while (T--) {
        io >> n;
        int x = 0, ans = 0;
        For (i, 1, n) io >> x, ans ^= SG[x];
        printf(ans? "1 ": "0 ");
    }

    return 0;
}
