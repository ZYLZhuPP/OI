#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
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

int T, seed;
ll n, ans, cnt[70];

inline ll Xor(ll x) { return x%4==1? 1: x%4==2? x + 1: x%4==3? 0: x; }
inline ll calc(ll x) { if (!(x & 1)) x--; return Xor(x >> 1) << 1 | !(x >> 1 & 1); }

int main() {
    io >> T;
    while (T--) {
        ans = 0;
        io >> n >> seed;
        if (seed == 1) {
            ans = calc(n);
            if (!(n & 1)) ans ^= n ^ 1;
        } else if (seed == 3) {
            if (n == 1) ans = 1;
            else if (n == 2) ans = 2;
            else if (n & 1) ans = calc(n) ^ n;
            else ans = calc(n) ^ n ^ (n - 2);
        } else {
            For (i, 0, 60) {
                if (1ll << i > n) break;
                cnt[i] = ((n - (1ll << i)) >> (i + 1)) + 1;
                if (cnt[i] & 1) {
                    ans ^= Xor(cnt[i] / 2) << (i + 2);
                    if (!(cnt[i] >> 1 & 1)) ans ^= 1ll << i;
                } else {
                    ans ^= Xor(cnt[i] / 2 - 1) << (i + 2);
                    if (cnt[i] >> 1 & 1) ans ^= 3ll << i;
                }
            }
            int s = cnt[0] & 1, res = 0;
            For (i, 1, 60) {
                if (1ll << i > n) break;
                res = (res + s * cnt[i]) & 1;
                s = (s + cnt[i]) & 1;
            }
            if (res) ans ^= 1;
        }
        printf("%lld\n", ans);
    }

    return 0;
}
