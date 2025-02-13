#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
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
	inline bool operator ~ () { return ~c; }
} io;

int n, K;
ll x, s[N], f[N];
int q[N];

ll F(int i) { return f[i] - s[i + 1]; }

int main() {
    io >> n >> K;
    For (i, 1, n) io >> x, s[i] = s[i - 1] + x;

    int h = 1, t = 0;
    For (i, 0, n) {
        while (h <= t && q[h] < i - K - 1) h++;
        f[i] = i<=K? s[i]: F(q[h]) + s[i];
        while (h <= t && F(q[t]) <= F(i)) t--;
        q[++t] = i;
    }
    
    printf("%lld", f[n]);

    return 0;
}
