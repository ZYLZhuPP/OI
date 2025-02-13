#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
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

int n, K, a[N], mi[N], ma[N];
int q[N];

int main() {
    io >> n >> K;
    For (i, 1, n) io >> a[i];

    int h = 1, t = 0;
    For (i, 1, n) {
        while (h <= t && q[h] <= i - K) h++;
        while (h <= t && a[q[t]] >= a[i]) t--;
        q[++t] = i;
        mi[i] = a[q[h]];
    }

    h = 1, t = 0;
    For (i, 1, n) {
        while (h <= t && q[h] <= i - K) h++;
        while (h <= t && a[q[t]] <= a[i]) t--;
        q[++t] = i;
        ma[i] = a[q[h]];
    }

    For (i, K, n) printf("%d%c", mi[i], i == n? '\n': ' ');
    For (i, K, n) printf("%d%c", ma[i], i == n? '\n': ' ');

    return 0;
}
