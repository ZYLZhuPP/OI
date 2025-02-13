#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;

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

int n, m, x, s[N], ans = INT_MIN;
int q[N];

int main() {
    io >> n >> m;
    For (i, 1, n) io >> x, s[i] = s[i - 1] + x;

    int h = 1, t = 0;
    q[++t] = 0;
    For (i, 1, n) {
        while (h <= t && q[h] < i - m) h++;
        ans = max(ans, s[i] - s[q[h]]);
        while (h <= t && s[q[t]] >= s[i]) t--;
        q[++t] = i;
    }
    
    printf("%d", ans);

    return 0;
}
