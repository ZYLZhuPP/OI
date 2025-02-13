#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
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
	inline bool operator ~ () const { return ~c; }
} io;

int n, a[N], b[N];

int main() {
    io >> n;
    For (i, 1, n) io >> a[i], b[a[i]]++;
    rFor (i, N - 1, 1) for (int j = i << 1; j < N; j += i) b[j] += b[i];
    For (i, 1, n) printf("%d\n", b[a[i]] - 1);

    return 0;
}
