#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 11, S = 1 << 9;

int n, K, ok[S];
ll f[N][N * N][S];

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

int main() {
    io >> n >> K;
    For (s, 0, (1 << n) - 1) if (!(s & (s << 1)) && !(s & (s >> 1))) ok[s] = 1;
    f[0][0][0] = 1;
    For (i, 0, n) {
        For (j, 0, K) For (s, 0, (1 << n) - 1) if (f[i][j][s]) {
            For (s_, 0, (1 << n) - 1) if (ok[s_] && (j + __builtin_popcount(s_) <= K) && !(s_ & s) && !(s_ & (s << 1)) && !(s_ & (s >> 1))) f[i + 1][j + __builtin_popcount(s_)][s_] += f[i][j][s];
        }
    }
    printf("%lld", f[n + 1][K][0]);

    return 0;
}
