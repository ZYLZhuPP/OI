#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

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

int n, cnt[N], ans;

int main() {
    io >> n;
    int x;
    For (i, 1, n) io >> x, cnt[x]++;
    For (i, 1, 1e5) ans = ans + cnt[i] - min(ans, cnt[i]);
    printf("%d", ans);

    return 0;
}
