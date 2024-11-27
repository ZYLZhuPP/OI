#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }

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

int n, a[N], pos, b[N], stk[N], top, mn = 2e9;
ll s[N], S;

int main() {
    io >> n;
    For (i, 1, n) {
        io >> a[i];
        S += a[i];
        if (cmin(mn, a[i])) pos = i;
    }
    For (i, 1, n - pos) b[i] = a[pos + i];
    For (i, 1, pos) b[i + n - pos] = a[i];
    rFor (i, n, 1) {
        while (top && b[i] < b[stk[top]]) {
            int x = stk[top--], y = stk[top];
            s[y - x] += b[x] - b[y];
            s[y - i] -= b[x] - b[y];
        }
        stk[++top] = i;
    }
    while (top > 1) {
        int x = stk[top--], y = stk[top];
        s[y - x] += b[x] - b[y];
        s[y] -= b[x] - b[y];
    }
    For (i, 1, n) s[i] += s[i - 1], printf("%lld\n", S -= s[i]);

    return 0;
}
