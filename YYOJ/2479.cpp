#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e6 + 5, Mo = 1e9 + 7;
inline int qPow(int a, int b) { int r = 1; for (; b; a = 1ll * a * a % Mo, b >>= 1) if (b & 1) r = 1ll * r * a % Mo; return r; }

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

int n, ans, a[N];

int main() {
    io >> n;
    if (n == 1) return puts("1"), 0;
    a[1] = 1; For (i, 2, n) a[i] = 1ll * a[i - 1] * (2 * i - 1) % Mo;
    For (i, 1, n - 1) {
        int k = n - i;
        ans = (ans + 1ll * a[i] * k % Mo * (qPow(2 * i, k - 1) + qPow(2 * i - 1, k - 1))) % Mo;
    }
    printf("%lld", 1ll * ans * qPow(a[n], Mo - 2) % Mo);

    return 0;
}
