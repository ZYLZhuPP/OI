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

int n;
ll f[105], s[105];

void init(int n) {
    for (int i = 1; i <= n; ++i) s[i] = s[i - 1] + f[i];
}

ll H(int n) {
    init(n);
    ll res = 0;
    int l = 1;
    while (l <= n) {
        int r = n / (n / l);
        res += (s[r] - s[l - 1]) * (n / l);
        l = r + 1;
    }
    return res;
}

int main() {
    io >> n;
    for (int i = 1; i <= n; ++i) io >> f[i];

    printf("%lld", H(n));

    return 0;
}
