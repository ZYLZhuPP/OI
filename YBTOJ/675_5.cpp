#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef long long ll;
const int N = 1e6 + 5;

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

int n, x[N << 1], y[N << 1], q[N];
ll s[N << 1];
bool ans[N];

int main() {
    io >> n;
    For (i, 1, n) io >> x[i] >> y[i], x[i + n] = x[i], y[i + n] = y[i];
    For (i, 1, 2 * n) s[i] = s[i - 1] + x[i] - y[i];

    int h = 1, t = 0;
    For (i, 1, 2 * n) {
        while (h <= t && q[h] <= i - n) h++;
        while (h <= t && s[q[t]] >= s[i]) t--;
        q[++t] = i;
        if (i >= n && s[q[h]] - s[i - n] >= 0) ans[i - n + 1] = 1;
    }
    y[0] = y[n];
    rFor (i, 2 * n, 1) s[i] = s[i + 1] + x[i] - y[i - 1];
    h = 1, t = 0;
    rFor (i, 2 * n, 1) {
        while (h <= t && q[h] >= i + n) h++;
        while (h <= t && s[q[t]] >= s[i]) t--;
        q[++t] = i;
        if (i <= n + 1 && s[q[h]] - s[i + n] >= 0) ans[i - 1] = 1;
    }

    For (i, 1, n) puts(ans[i]? "TAK": "NIE");


    return 0;
}
