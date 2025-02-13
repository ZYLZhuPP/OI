#include<bits/stdc++.h>
using namespace std;

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
	inline bool operator ~ () {return ~c;}
} io;

int R;
ll R_2, ans;

inline int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a % b);
}

int main() {
    io >> R; R_2 = 1ll * R * R;
    int I = sqrt(R / 2.0), J;
    for (int i = 1; i <= I; ++i) {
        J = sqrt(R - i * i);
        for (int j = i + 1; j <= J; j += 2) if (gcd(i, j) == 1) {
            ans += (R / (i * i + j * j)) << 3;
        }
    }
    ans = -ans;
    for (int i = 1; i < R; ++i) ans += (int)sqrt(R_2 - 1ll * i * i) << 2;

    printf("%lld", ans);

    return 0;
}
