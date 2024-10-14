#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e7 + 5, Mo = 998244353;
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }

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

int n, ans = 1;
bool a[N];

int main() {
    io >> n;
    For (i, 0, n) {
        if (i & 1) a[i] = a[i - 1] ^ 1;
        else a[i] = a[i >> 1];
        if (a[i]) mul(ans, i);
    }
    printf("%d", ans);

    return 0;
}
