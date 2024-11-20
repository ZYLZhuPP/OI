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

int n, ans, a[N], vis[N];

int main() {
    io >> n; ans = n;
    For (i, 1, n) io >> a[i];
    For (i, 1, n) if (!vis[i] && a[i] ^ i) {
        ans--;
        for (int x = a[i]; !vis[x]; x = a[x]) vis[x] = 1;
    }
    printf("%d", ans);

    return 0;
}
