#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, a[N], s[N], ans;

int main() {
    io >> n;
    For (i, 1, n) io >> a[i], s[i] = s[i - 1] + a[i];
    For (i, 0, n - 1) for (int j = i; ~j;) j &= i, ans ^= s[i + 1] - s[i - j], j--;
    printf("%d", ans);

    return 0;
}
