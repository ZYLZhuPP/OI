#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
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

int n, a[N], ans;

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    int p = -1, q = -1;
    For (i, 1, n + 1) {
        int x = a[i] - a[i - 1];
        if (x >= 0) {
            p = min(q, p + x);
            q += x;
        } else {
            p = max(min(q + x, p), -1);
            if (q >= a[i]) {
                ans++;
                q = p, p = -1;
            }
        }
    }
    printf("%d", ans);

    return 0;
}