#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5, p = 1e4 + 7, q = 1e9 + 7;

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

int n, m, cnt, ans[N], ok[p], y;
ll a[103], b[103], aa, bb;

bool f(int p, int M, ll t[]) {
    ll x = t[n];
    rFor (i, n - 1, 0) x = (x * p + t[i]) % M;
    return !x;
}

int main() {
    io >> n >> m;
    For (i, 0, n) {
        aa = bb = 0;
        char c; int f = 0;
        while (!isdigit(c = gc()) && ~c) f |= !(c ^ 45);
        while (isdigit(c)) aa = ((aa << 3) + (aa << 1) + (c ^ 48)) % p, bb = ((bb << 3) + (bb << 1) + (c ^ 48)) % q, c = gc();
        a[i] = f? p - aa: aa;
        b[i] = f? q - bb: bb;
    }
    For (i, 0, p - 1) ok[i] = f(i, p, a);
    For (i, 1, m) if (ok[i % p] && f(i, q, b)) ans[++cnt] = i;
    printf("%d\n", cnt);
    For (i, 1, cnt) printf("%d\n", ans[i]);
}