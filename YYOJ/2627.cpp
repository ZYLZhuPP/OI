#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 3e5 + 5;

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

int n, m, K, t, tot, a[N], b[N];

int main() {
    io >> n >> m >> K; t = n - K;
    For (i, 1, K) io >> b[i];
    For (i, 1, K) {
        rFor (j, m, b[i] + 1) if (t) a[++tot] = j, t--; else break;
        a[++tot] = b[i];
    }
    if (tot < n) puts("No");
    else {
        puts("Yes");
        For (i, 1, n) printf("%d ", a[i]);
    }

    return 0;
}
