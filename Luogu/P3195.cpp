#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e4 + 5;

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

int n, q[N];
ll L, s[N], f[N];

ll dx(int i, int j) { return s[i] - s[j]; }
ll dy(int i, int j) { return f[i] - f[j] + s[i] * s[i] - s[j] * s[j]; }
ll F(int i, int j) { return f[j] + (s[i] - s[j] - L) * (s[i] - s[j] - L); }

int main() {
    io >> n >> L; L++;
    For (i, 1, n) io >> s[i], s[i] += s[i - 1] + 1;
    
    int l = 1, r = 0;
    q[++r] = 0;
    For (i, 1, n) {
        ll k = 2ll * (s[i] - L);
        while (l < r && dy(q[l + 1], q[l]) < dx(q[l + 1], q[l]) * k) l++;
        f[i] = F(i, q[l]);
        while (l < r && dy(i, q[r]) * dx(q[r], q[r - 1]) < dy(q[r], q[r - 1]) * dx(i, q[r])) r--;
        q[++r] = i;
    }
    printf("%lld", f[n]);

    return 0;
}